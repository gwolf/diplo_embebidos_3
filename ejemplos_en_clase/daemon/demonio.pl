#!/usr/bin/perl

use strict;
use warnings;

use POSIX qw(setsid);
use Getopt::Long;
use Sys::Syslog;

my $daemon_pid = undef;
my $daemon = undef;
my $conf_file = undef;

GetOptions( "pid"  => \$daemon_pid, "conf" => \$conf_file, "daemon" => \$daemon);

$daemon_pid='/var/run/daemon.pid' if(!defined $daemon_pid);
$conf_file = "/etc/daemon.conf" if(!defined($conf_file));

# Daemonize
if (defined($daemon)) {
	chdir '/'                 or die "Can't chdir to /: $!";
	umask 0;
	open STDIN, '/dev/null'   or die "Can't read /dev/null: $!";
	open STDOUT, '>/dev/null' or die "Can't write to /dev/null: $!";
	open STDERR, '>/dev/null' or die "Can't write to /dev/null: $!";
	my $pid = undef;
	defined($pid = fork)   or die "Can't fork: $!";
	exit if $pid;
	setsid                    or die "Can't start a new session: $!";
	defined($pid = fork)   or die "Can't fork: $!";
	exit if $pid;
}

# Open syslog
openlog("demonio", "ndelay,pid", "local0");

# record PID
if (open PID, ">", "$daemon_pid") {
	print PID $$;
	close(PID);
} else {
	if (defined($daemon)) {
		syslog("LOG_CRIT","can't open $daemon_pid");
	} else {
		die "can't open $daemon_pid";
	}
	exit 1;
}

# Initialize variables
my $continue = 1;
my $counter = 0;
my $reconfig = 0;
my $message = "Hello...";

# Signal handlers
$SIG{TERM} = sub { $continue = 0 };
$SIG{USR1} = sub { $counter = 0 };
$SIG{HUP} = sub { $reconfig = 1 };

# Drop privileges
if($< == 0) {
	if (defined($daemon)) {
		syslog("LOG_INFO","Change UID to 166");
	} 
	$<=166;
} else {
	syslog("LOG_INFO","Daemon running as UID $<");
}

# Main loop
while($continue) {
	if($reconfig) {
		reload_config();
		$reconfig = 0;
	}
	sleep(1);
	if (defined($daemon)) {
		syslog("info","$counter $message ");
	} else {
		print "$counter $message \n";
	}
	$counter++;
}

# Cleanup
syslog("LOG_INFO","Daemon ending...");
closelog();
open PID, ">", "$daemon_pid";
print PID '';
close(PID);
exit 0;

# Subrutines 
sub reload_config  { 
	
	syslog("LOG_INFO","Reloading configuration");

	unless ( -e $conf_file ) {
		syslog("warning","Configuration file $conf_file does not exist ");
		return;
	}
	
	unless ( -r $conf_file) {
		syslog("warning","Configuration file $conf_file is not readable by UID $< ");
		return;
	}

	syslog("LOG_INFO","resding configuration file $conf_file ");
	open CONF_FILE, "<", "$conf_file";
	while (<CONF_FILE>) {
		if (/^MESSAGE=(.*)/) {
			$message=$1;
			syslog("LOG_INFO","Changed hello message to $message");
		}
	}

}


