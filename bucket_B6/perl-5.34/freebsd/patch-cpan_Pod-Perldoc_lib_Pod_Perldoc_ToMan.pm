- Handle MANWIDTH=tty
- Reset $? before opening mandoc so that the outputter works.

--- cpan/Pod-Perldoc/lib/Pod/Perldoc/ToMan.pm.orig	2020-06-14 23:01:25 UTC
+++ cpan/Pod-Perldoc/lib/Pod/Perldoc/ToMan.pm
@@ -108,6 +108,8 @@ sub _get_columns_from_manwidth {
 
 	return 0 unless defined $ENV{MANWIDTH};
 
+	if ($ENV{MANWIDTH} eq 'tty') { return 0; }
+
 	unless( $ENV{MANWIDTH} =~ m/\A\d+\z/ ) {
 		$self->warn( "Ignoring non-numeric MANWIDTH ($ENV{MANWIDTH})\n" );
 		return 0;
@@ -310,6 +312,9 @@ sub _filter_through_nroff {
 	require IPC::Open3;
 	require IO::Handle;
 
+	# Reset this???
+	$?=0;
+
 	my $pid = IPC::Open3::open3(
 		my $writer,
 		my $reader,
