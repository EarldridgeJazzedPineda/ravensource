#!/bin/sh
#
# The purpose of this script is to catch FPC_EQUIVALENT values of "N/A"
# that are not on a whitelist.  This usually means they were forgotten
# to be defined.

location=/usr/raven
tmpfile=/tmp/fpc.notlist
PROG='{if ($3 == "N/A") print}'
awk "${PROG}" ${location}/Mk/Misc/fpc_equivalents > ${tmpfile}

echo "List of ports with undefined FPC_EQUIVALENT values:"
while read ravenport version fpc_port; do
   case "${ravenport}" in
	libbsd) ;; 		# linux only
	libusb) ;; 		# linux only
	shadow) ;;		# linux only
	musl-fts) ;;		# linux only
	libbsd4sol);;		# solaris only

	ravenports) ;;		# unique to ravenports
	libdl) ;;		# unique to ravenports
	ravensys-root) ;;	# unique to ravenports
	ravensys-toolchain) ;;	# unique to ravenports
	ravensys-uname) ;;	# unique to ravenports
	ravensys-selector) ;;	# unique to ravenports
	bmake-mk-files) ;;	# unique to ravenports
	ravenadm) ;;		# unique to ravenports

	xz) ;;			# deleted from FPC
	zlib) ;;		# deleted from FPC
	aflex*) ;;		# deleted from FPC

	fetch) ;;		# From DragonFly
	makewhatis) ;;		# From DragonFly
	mtree) ;;		# From DragonFly
	rpcgen) ;;		# From DragonFly
	sha256) ;;		# From DragonFly
	bsd-patch) ;;		# From DragonFly/FreeBSD
	bsd-which) ;;		# From DragonFly/FreeBSD

	libedit) ;;		# Different version scheme from FPC
	gnat-util) ;;		# Different version scheme from FPC
	gcc[678]) ;;		# Different version scheme from FPC
	gprbuild) ;;		# Different version scheme from FPC
	apr1|apr-util) ;;	# Different version scheme from FPC
	libunwind) ;;		# ditto
	unrar) ;;		# ditto
	autoconf213) ;;		# ditto
	cwm) ;;			# ditto
	fonts-gentium-basic) ;;	# ditto

	aspell-el) ;;		# requires EPOCH, 0.08 > 0.50 actually
	hunspell-pt_BR) ;;	# Freebsd combines BR/PT, but raven splits them up
	openjade) ;;            # FreeBSD uses dev version, ravenports has release
	python-*) ;;            # manual python port
	ncurses) ;;		# FreeBSD uses dev version now

	libexecinfo) ;;		# Different source from FPC

	qt5-qtbase) ;;		# FreeBSD splits these packages into sep one
	qt5-qttools) ;;		#
	qt5-qtdeclarative) ;;	#
	
	usb-modeswitch-data) ;;	# combined with sysutils/usb_modeswitch
	rustless-firefox) ;;	# currently like www/firefox-esr, but RP is frozen

	libadalang) ;;		# Rest are ports that FPC doesn't have yet
	libtickit) ;;
	libmpack) ;;
	lua-mpack) ;;
	quex) ;;
	slider) ;;
	firebird30) ;;
	php56-intl) ;;
	fuse3) ;;
	aspell-mg | aspell-hus) ;;
	gnatcross*) ;;
	edelib) ;;
	openpam) ;;
	AdaYaml) ;;
	libuuid) ;;
	spidermonkey) ;;		# check occasionally
	*) echo "${ravenport} ${version}"
   esac
done < ${tmpfile}

rm -f ${tmpfile}
