# first file is crates.list, second file is template

FNR==NR {
  # store crates list
  n=split ($0,item,"-")
  version[FNR""] = item[n]
  name[FNR""] = item[1]
  for (j=2; j < n; j++)
     name[FNR""] = name[FNR""] "-" item[j]
  ll++
  next
}

function CR_NAME(ndx) {
   if (ndx < 10)
      prefix = "0" ndx "_"
   else
      prefix = ndx "_"
   sl = length(name[ndx""])
   return prefix substr(toupper(name[ndx""]), 1, 14)
}

function tabs(txt) {
   if (length(txt) < 7)
      return "\t\t"
   else
      return "\t"
}

function CR_DEFINITIONS() {
   for (j=1; j <= ll; j++)
      print "DEF[" CR_NAME(j) "]=" tabs(name[j""]) version[j""]
}

function DOWNLOAD_GROUPS() {
   workline = "DOWNLOAD_GROUPS=\tmain"
   maxcr = 9;
   if (ll < maxcr)
      maxcr = ll
   for (j = 1; j <= maxcr; j++)
      workline = workline " cr0" j
   print workline
   if (ll > 9) {
      cur = 10
      do {
         workline = "\t\t\t"
         maxcr = cur + 9
         if (ll < maxcr)
            maxcr = ll
         for (j = cur; j <= maxcr; j++) {
            if (j == cur)
               workline = workline "cr" j
            else
               workline = workline " cr" j
         }
         print workline
         cur = cur + 10
      }
      while (maxcr < ll)
   }
}

function DF_INDEX() {
   workline= "DF_INDEX=\t\t"
   maxcr = 10
   dfiles = ll + 1
   if (dfiles < maxcr)
      maxcr = dfiles
   for (j = 1; j <= maxcr; j++) {
      if (j > 1)
         workline = workline " "
      workline = workline j
   }
   print workline
   if (dfiles > 10) {
      cur = 11
      do {
         workline = "\t\t\t"
         maxcr = cur + 9
         if (dfiles < maxcr)
            maxcr = dfiles
         for (j = cur; j <= maxcr; j++) {
            if (j > cur)
               workline = workline " "
            workline = workline j
         }
         print workline
         cur = cur + 10
      }
      while (maxcr < dfiles)
   }
}

function crid (id) {
   if (id < 10)
      return "cr0" id
   else
      return "cr" id
}

function CR_SITES () {
   for (j=1; j <= ll; j++) {
      print "SITES[" crid(j) "]=\t\tCRATES/" name[j""] ":" version[j""]
   }
}

function CR_DISTFILES() {
   for (j=1; j <= ll; j++) {
      print "DISTFILE[" (j+1) "]=\t\tgenerated:" crid(j)
   }
}

{
   # process template (file 2)
   if ($0 == "%%CR_DEFINITIONS%%")
      CR_DEFINITIONS()
   else if ($0 == "%%DOWNLOAD_GROUPS%%")
      DOWNLOAD_GROUPS()
   else if ($0 == "%%CR_SITES%%")
      CR_SITES()
   else if ($0 == "%%CR_DISTFILES%%")
      CR_DISTFILES()
   else if ($0 == "%%DF_INDEX%%")
      DF_INDEX()
   else
      print $0
}
