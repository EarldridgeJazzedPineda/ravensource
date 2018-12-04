--- cpan/ExtUtils-MakeMaker/lib/ExtUtils/MM_Any.pm.orig	2018-11-01 22:07:28 UTC
+++ cpan/ExtUtils-MakeMaker/lib/ExtUtils/MM_Any.pm
@@ -2031,13 +2031,14 @@ sub init_INSTALL_from_PREFIX {
           ('$(PREFIX)') x 3;
     }
     else {
+        $self->{PREFIX}   ||= $iprefix;
         $self->{PERLPREFIX}   ||= $iprefix;
         $self->{SITEPREFIX}   ||= $sprefix;
         $self->{VENDORPREFIX} ||= $vprefix;
 
         # Lots of MM extension authors like to use $(PREFIX) so we
         # put something sensible in there no matter what.
-        $self->{PREFIX} = '$('.uc $self->{INSTALLDIRS}.'PREFIX)';
+        #$self->{PREFIX} = '$('.uc $self->{INSTALLDIRS}.'PREFIX)';
     }
 
     my $arch    = $Config{archname};
