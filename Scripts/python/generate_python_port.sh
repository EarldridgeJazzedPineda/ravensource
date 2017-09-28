#!/bin/sh
#
# This script takes a Python Package Index name as an argument and
# then creates/overwrites the source port after querying the website
# and downloading the latest tarball for querying setup.py
#

[ -n "${DEBUG_MK_SCRIPTS}" -o -n "${DEBUG_MK_SCRIPTS_MAKESUM}" ] && set -x

usage() {
   echo "Usage: $0 PyPI-name [version]"
   echo "If the second argument exists, it is considered the version"
   echo "to use rather than querying for the latest"
   exit 1
}

if [ $# -lt 1 ]; then
   usage;
fi

EXEPERL=/usr/local/bin/perl
#PATH=${PATH}:/raven/bin
VERSION=unset
MD5SUM=unset
tarball=unset
buckdir=unset
summary=unset
homepage=unset
PYPINAME=${1}
DISTNAME=${1}
JSONFILE=/tmp/pypi-${PYPINAME}
NEWPORT=/tmp/python-${PYPINAME}
SPEC=${NEWPORT}/specification
distfiles="/var/ravenports/distfiles"
PYPISITE=https://files.pythonhosted.org/packages/source/
PYPISIT2=https://pypi.python.org/packages/source/
PYPITWO=$(echo ${PYPINAME} | awk '{ print substr ($1, 1, 1) "/" $1 }')
#VARIANTS=
#FIRST_SNAKE=
setup=unset
raw_deps=unset
raven_req2=unset
raven_req3a=unset
raven_req3b=unset
pathtoexec=$(realpath $0)
thisdir=$(dirname ${pathtoexec})
DEADLIST=${thisdir}/dead-homepage.list

LANG=en_US.UTF-8
LC_ALL=en_US.UTF-8
export LANG LC_ALL

if [ $# -gt 1 ]; then
VERSION=$2
fi

# return "ok" or "dead".
# "dead" means the port has been manually marked for a dead homepage
homepage_status()
{
   awk -vportname="${1}" '{ if (portname == $1) { found = 1 }} \
END { print (found) ? "dead" : "ok"}' ${DEADLIST}
}

acquire_tarball_and_version() {
   local www url summd5

   www="https://pypi.python.org/pypi/${PYPINAME}/json"
   fetch -o ${JSONFILE} ${www}
   if [ $? -ne 0 ]; then
      echo "'${PYPINAME}' doesn't seem to be a valid package name"
      exit 1;
   fi
   if [ "${VERSION}" == "unset" ]; then
      VERSION=$(awk -F'"' '/"version":/ { print $4 }' ${JSONFILE})
   fi
   MD5SUM=$(awk -v version=${VERSION} -v seek="md5_digest" -f ${thisdir}/md5.awk ${JSONFILE})
   tarball=$(awk -v version=${VERSION} -v seek="filename" -f ${thisdir}/md5.awk ${JSONFILE})
   summary=$(${EXEPERL} extract_summary.pl ${JSONFILE})
   homepage=$(${EXEPERL} extract_homepage.pl ${JSONFILE})

   if [ -z "${MD5SUM}" -o -z "${tarball}" ]; then
      echo "No file or md5 sum for version ${VERSION} available"
      exit 1;
   fi

   if [ -f "${distfiles}/${tarball}" ]; then
      summd5=$(md5 -q "${distfiles}/${tarball}")
      if [ "${summd5}" == "${MD5SUM}" ]; then
         echo "${tarball} already fetched and digest-verified"
         return;
      fi
   fi

   url="${PYPISITE}${PYPITWO}/${tarball}"
   fetch -o ${distfiles} ${url}
   if [ $? -ne 0 ]; then
      echo "Failed to fetch ${tarball}"
      exit 1
   fi
}

exec_setup() {
  python_program=$1
  arguments=$2
  (cd /tmp/expand/${DISTNAME}-${VERSION}/ && ${python_program} -W ignore setup.py ${arguments})
}

determine_variants() {
   local vrt
   exec_setup python2.7 --name > /dev/null
   if [ $? -eq 0 ]; then
      vrt="py27"
      [ -z "${FIRST_SNAKE}" ] && FIRST_SNAKE=python2.7
   fi
   exec_setup python3.5 --name > /dev/null
   if [ $? -eq 0 ]; then
      vrt="${vrt} py35"
      [ -z "${FIRST_SNAKE}" ] && FIRST_SNAKE=python3.5
   fi
   exec_setup python3.6 --name > /dev/null
   if [ $? -eq 0 ]; then
      vrt="${vrt} py36"
      [ -z "${FIRST_SNAKE}" ] && FIRST_SNAKE=python3.6
   fi
   for v in ${vrt}; do
      if [ -z "${VARIANTS}" ]; then
         VARIANTS=${v};
      else
         VARIANTS="${VARIANTS} ${v}";
      fi
   done
}

get_description() {
   if [ -n "${summary}" ]; then
      echo ${summary}
   else
      exec_setup ${FIRST_SNAKE} --description
   fi
}

get_url() {
   if [ -n "${homepage}" ]; then
      echo ${homepage}
   else
      exec_setup ${FIRST_SNAKE} --url
   fi
}

get_filtered_url() {
   local hpstat=${1}
   if [ "${hpstat}" = "ok" ]; then
      url=$(get_url)
      case ${url} in
         http://github.com/* | http://pypi.python.org/* | http://bitbucket.org/* | \
         http://certifi.io/* | http://docs.openstack.org/* )
            echo ${url} | sed -e "s/^http:/https:/"
            ;;
         *) echo ${url} ;;
      esac
   else
      echo "none";
   fi
}

get_available_options() {
   echo ${VARIANTS} | awk '{ print toupper($0) }'
}

dump_descriptions() {
   local v sdesc
   sdesc=$(get_description | awk '{\
 raw=$0; \
 if (substr(raw, 1, 2) == "A ") raw=substr(raw, 3); \
 if (substr(raw, 1, 3) == "An ") raw=substr(raw, 4); \
 final=toupper(substr(raw, 1, 1)) substr(raw, 2); \
 print substr (final, 1, 42) }')
   for v in ${VARIANTS}; do
      echo "SDESC[${v}]=		${sdesc} (PY ${v#py})"
   done
}

dump_subpackages() {
   local v
   for v in ${VARIANTS}; do
      echo "SPKGS[${v}]=		single"
   done
}

dump_vopts() {
   local v
   for v in ${VARIANTS}; do
      echo ${VARIANTS} | awk -v variant=${v} '{\
  printf ("VOPTS[%s]=		", variant); \
  for (x=1; x<=NF; x++) { \
    printf ("%s%s=%s",\
      x == 1 ? "" : " ",\
      toupper($x),\
      $x == variant ? "ON" : "OFF"\
    )\
  };\
  printf ("\n");
}'
   done
}

create_description() {
   mkdir -p ${NEWPORT}/descriptions
   local desc1
   # can't use head, it causes python to emit close failure message
   exec_setup ${FIRST_SNAKE} --long-description | awk 'NR <= 100' \
   	> ${NEWPORT}/descriptions/desc.single
   desc1=$(/usr/bin/head -1 ${NEWPORT}/descriptions/desc.single)
   if [ "${desc1}" = "UNKNOWN" ]; then
      get_description | awk 'NR <= 100' > ${NEWPORT}/descriptions/desc.single
   fi
}

dump_variable() {
   local varname data
   varname=$1
   data=$2
   echo ${data} | awk -v varname=${varname} '\
{\
  if (NF) { printf ("%s=		", varname); }\
  for (x=1; x<=NF; x++) {\
    gsub(/\*/, " ", $x);\
    printf ("%s%s\n", x==1?"":"			", $x);\
  }\
}'
}

handle_licenses() {
   local licname licfile rawlicense
   local arr_license arr_file arr_name
   rawlicense=$(exec_setup ${FIRST_SNAKE} --license)
   case "${rawlicense}" in
      "Apache License, Version 2.0") all_lic="Apache*2.0" ;;
      *) all_lic=$(echo ${rawlicense} | awk -F ', ' '{ for (x=1;x<=NF;x++) { gsub (/ /, "*", $x); print $x }}') ;;
   esac
   for lic in ${all_lic}; do
   case "${lic}" in
      BSD*) 
        specified=$(awk "/${PYPINAME} / { print \$2 }" ${thisdir}/pypi_bsd_licenses.txt)
        case "${specified}" in
          2) licname="BSD2CLAUSE" ;;
          3) licname="BSD3CLAUSE" ;;
          4) licname="BSD4CLAUSE" ;;
          *) licname="BSDGROUP"   ;;
        esac
        ;;
      *)
        case "${lic}" in
          MIT) licname="${lic}" ;;
          ISC | ISCL)      licname=ISCL ;;
          "public*domain") licname=PUBDOM ;;
          "Python")        licname=PSFL ;;
          "2-Clause*BSD")  licname="BSD2CLAUSE" ;;
          "GPL*3"*)        licname="GPLv3" ;;
          "Apache*2.0")    licname="APACHE20" ;;
          "") ;;
          *) licname="CUSTOM1" ;;
        esac
        ;;
   esac
   for chkfile in LICENSE LICENSE.txt COPYING COPYING3 COPYING.txt LICENSE.rst; do
      if [ -z "${licfile}" ]; then
         if [ -f "/tmp/expand/${DISTNAME}-${VERSION}/${chkfile}" ]; then
            licfile=${chkfile}
         fi
      fi
   done
   if [ -n "${lic}" ]; then
      if [ -n "${licfile}" ]; then
         arr_license="${arr_license} ${licname}:single"
         arr_file="${arr_file} ${licname}:{{WRKSRC}}/${licfile}"
         if [ "${licname}" == "CUSTOM1" ]; then
            arr_name="${arr_name} ${licname}:\"${lic}\""
         fi
      else
         echo "# No license file found for ${lic} license" 
      fi
   else
      echo "# No license specified"
   fi
   done

   dump_variable "LICENSE" "${arr_license}"
   dump_variable "LICENSE_FILE" "${arr_file}"
   dump_variable "LICENSE_NAME" "${arr_name}"
   echo $all_lic | \
   awk '{ if (NF) { printf ("LICENSE_SCHEME=		%s\n", \
        NF>1 ? "multi" : "solo")}}'
}

set_keywords() {
   local topics keywords
   topics=$(exec_setup ${FIRST_SNAKE} --classifiers | grep "^Topic :")
   keywords=python
   if [ -n "`echo ${topics} | grep ':: Utilities'`" ]; then
      keywords="${keywords} devel"
   elif [ -n "`echo ${topics} | grep ':: Software Devel'`" ]; then
      keywords="${keywords} devel"
   fi
   if [ -n "`echo ${topics} | grep ':: Text Processing'`" ]; then
      keywords="${keywords} textproc"
   fi
   if [ -n "`echo ${topics} | grep ':: Multimedia :: Graphics'`" ]; then
      keywords="${keywords} graphics"
   fi
   if [ -n "`echo ${topics} | grep ':: System :: Systems Administration'`" ]; then
      keywords="${keywords} sysutils"
   fi
   echo $keywords
}

write_buildrun() {
   local mockfile=/tmp/expand/${DISTNAME}-${VERSION}/obtain-req.py
   local mockfile2=/tmp/expand/${DISTNAME}-${VERSION}/obtain-req2.py
   local setup=/tmp/expand/${DISTNAME}-${VERSION}/setup.py
   raven_req2=/tmp/expand/${DISTNAME}-${VERSION}/raven-req2.list
   raven_req3a=/tmp/expand/${DISTNAME}-${VERSION}/raven-req3a.list
   raven_req3b=/tmp/expand/${DISTNAME}-${VERSION}/raven-req3b.list
   cat <<EOF > ${mockfile}
import unittest.mock
import setuptools

with unittest.mock.patch.object(setuptools, 'setup') as mock_setup:
    import setup

if mock_setup.call_args is not None:
   args, kwargs = mock_setup.call_args
   print ('\n'.join(kwargs.get('install_requires', [])))
   print ('\n'.join(kwargs.get('setup_requires', [])))
EOF
   sed -e 's|unittest.||' ${mockfile} > ${mockfile2}

   check_name=$(grep -q "^if __name__ == '__main__'" ${setup})
   if [ $? -eq 0 ]; then
      mv ${setup} ${setup}.bak2
      awk '/if __name__ == .__main__.*:/ { active = 1; next } \
      { if (active) { \
          if (substr($0,1,4) == "    ") {print substr($0,5); next}; \
          if (substr($0,1,1) == "\t") {print substr($0,2); next}; \
        }; \
        active = 0; print; \
      }' ${setup}.bak2 > ${setup}
   fi
   check_dist=$(grep -q "from distutils.core import setup" ${setup})
   if [ $? -eq 0 ]; then
      sed -i'.bak' 's/from distutils.core/from setuptools/' ${setup}
   fi

   (cd /tmp/expand/${DISTNAME}-${VERSION}/ && python2.7 obtain-req2.py | sed '/^$/d') \
    > ${raven_req2}
   if [ $? -ne 0 ]; then
      echo "### Python script to obtain dependencies failed! ###";
      cat ${raven_req2}
   fi

   (cd /tmp/expand/${DISTNAME}-${VERSION}/ && python3.5 obtain-req.py | sed '/^$/d') \
    > ${raven_req3a}
   if [ $? -ne 0 ]; then
      echo "### Python script to obtain dependencies failed! ###";
      cat ${raven_req3a}
   fi

   (cd /tmp/expand/${DISTNAME}-${VERSION}/ && python3.6 obtain-req.py | sed '/^$/d') \
    > ${raven_req3b}
   if [ $? -ne 0 ]; then
      echo "### Python script to obtain dependencies failed! ###";
      cat ${raven_req3b}
   fi
    grep "if __name__ == '__main__'" /tmp/expand/*/setup.py
}

dump_dependencies_as_comments() {
   echo "# install_requires extracted from setup.py (using python 2.7)"
   awk '{ if (length ($1) > 0) print "# " $1 }' ${raven_req2}
}

dump_buildrun_options() {
   local v
   local reqfile
   for v in ${VARIANTS}; do
      case "${v}" in
       py35) reqfile=${raven_req3a} ;;
       py36) reqfile=${raven_req3b} ;;
        *)   reqfile=${raven_req2} ;;
      esac
      awk -F ">" -v variant=${v} '\
function strip_dep(dep) {\
       gsub (" ","", dep); \
       if (index (dep, "==")) \
       return "python-" substr (dep, 1, index (dep, "==") - 1);\
  else if (index (dep, "!=")) \
       return "python-" substr (dep, 1, index (dep, "!=") - 1);\
  else if (index (dep, "<")) \
       return "python-" substr (dep, 1, index (dep, "<") - 1);\
  else \
       return "python-" dep;\
}\
function filter(dep) {\
   if (dep == "python-babel") return "python-Babel";
   else return dep;
}\
BEGIN {\
  virgin = 1; \
  printf ("\n[%s].USES_ON=				python:%s\n", \
     toupper(variant), variant);\
}\
{\
   if (length ($1) > 0) {\
     if (virgin) \
        printf ("[%s].BUILDRUN_DEPENDS_ON=		", toupper(variant));\
     package=filter(strip_dep($1));\
     if (package in seen == 0) { \
        printf ("%s%s:single:%s\n",\
           virgin ? "" : "					",\
           package,\
           variant);\
     };\
     seen[package]=1;\
     virgin = 0;\
   };\
}' ${reqfile}
   done
}

set_buckdir() {
	local raw=$(/raven/bin/ravenadm locate python-${PYPINAME})
	local bucket=$(echo ${raw} | awk -F '/' \
	   '{ for (x=1;x<=NF;x++) if (substr($x,1,7) == "bucket_") print $x}')
	buckdir="${thisdir}/../../${bucket}/python-${PYPINAME}"
}

replace_port() {
	# 1. Create bucket directory
	# 2. copy over:
	#    specification
	#    descriptions/desc.single
	#    distinfo
	# Any other materials like files/*, patches/*, etc. remain
	mkdir -p ${buckdir}/descriptions
	mv ${SPEC} ${buckdir}
	mv ${NEWPORT}/descriptions/desc.single ${buckdir}/descriptions
	mv ${NEWPORT}/distinfo ${buckdir}
	rmdir ${NEWPORT}/descriptions
	rmdir ${NEWPORT}
	/raven/bin/ravenadm dev buildsheet ${buckdir} save
}

generate_port() {
   local manualbit
   if [ -f "${buckdir}/specification.manual" ]; then
      manualbit=$(cat ${buckdir}/specification.manual)
   fi
   rm -rf ${NEWPORT} /tmp/expand
   mkdir -p ${NEWPORT} /tmp/expand
   (cd /tmp/expand && tar -xf ${distfiles}/${tarball})
   setup=/tmp/expand/${DISTNAME}-${VERSION}/setup.py
   if [ ! -f "${setup}" ]; then
      DISTNAME=$(echo ${PYPINAME} | sed -e "s|_|-|g")
      setup=/tmp/expand/${DISTNAME}-${VERSION}/setup.py
   fi
   if [ ! -f "${setup}" ]; then
      echo "Setup script '${setup}' is not present";
      exit 1;
   fi
   local hp_status=$(homepage_status ${PYPINAME})
   determine_variants
   create_description
   write_buildrun

   cat <<EOF > ${SPEC}
DEF[PORTVERSION]=	${VERSION}
# ------------------------------------------------------------------------

NAMEBASE=		python-${PYPINAME}
VERSION=		\${PORTVERSION}
KEYWORDS=		$(set_keywords)
VARIANTS=		${VARIANTS}
$(dump_descriptions)
HOMEPAGE=		$(get_filtered_url ${hp_status})
CONTACT=		Python_Automaton[python@ironwolf.systems]

DOWNLOAD_GROUPS=	main
SITES[main]=		PYPI/${PYPITWO}
DISTFILE[1]=		${tarball}:main

$(dump_subpackages)

OPTIONS_AVAILABLE=	$(get_available_options)
OPTIONS_STANDARD=	none
$(dump_vopts)

$(handle_licenses)

GENERATED=		yes

$(dump_dependencies_as_comments)

DISTNAME=		${DISTNAME}-\${PORTVERSION}
$(dump_buildrun_options)
${manualbit}
EOF

   (cd ${NEWPORT} && /raven/bin/ravenadm dev distinfo)
   
}

acquire_tarball_and_version
set_buckdir
generate_port
replace_port

rm -f ${JSONFILE}
