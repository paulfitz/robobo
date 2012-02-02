#!/usr/bin/perl -w

use strict;

my $unit = "world";
my $parent = "world";
my $unit_chain = "world";
my $nesting = 0;

my %units;
my %parents;
my %unit_chains;
my %applied;
my %configured;

$configured{"world"} = 1;
$applied{"world"} = 1;

print "from kino import *\n";

while (<>) {
    chomp($_);
    $_ =~ s/^\s+//;
    if ($_ =~ /{/) {
	$units{$nesting} = $unit;
	$parents{$nesting} = $parent;
	$unit_chains{$nesting} = $unit_chain;
	$parent = $unit;
	$nesting++;
    } elsif ($_ =~ /}/) {
	$nesting--;
	if (!$configured{$unit}) {
	    print "unit_$unit.configured()\n";
	    $configured{$unit} = 1;
	}
	if (!$applied{$unit}) {
	    print "unit_$unit.complete()\n";
	    $applied{$unit} = 1;
	}
	$unit = $units{$nesting};
	$parent = $parents{$nesting};
	$unit_chain = $unit_chains{$nesting};
    } elsif ($_ =~ /^((?:ROOT)|(?:JOINT)|(?:END))\s+(\w+)/) {
	if (!$configured{$unit}) {
	    print "unit_$unit.configured()\n";
	    $configured{$unit} = 1;
	}
	my $end = ($1 eq "END");
	my $root = ($1 eq "ROOT");
	$unit = $2;
	$unit_chain = "$unit_chain->$1";
	if ($root) {
	    print "unit_$unit = create_root(\"$unit\")\n";
	} else {
	    print "unit_$unit = create_joint(\"$unit\",unit_$parent)\n";
	}
	if ($end) {
	    print "unit_$unit.set_terminal()\n";
	}
    } elsif ($_ =~ /^MESH/) {
	print "# Ignored mesh for $unit\n";
    } elsif ($_ =~ /^BASE\s*(\w.*\w)/) {
	my @lst = split(/\s+/,$1);
	print "unit_$unit.set_base([" . join(',',@lst) . "])\n";
    } elsif ($_ =~ /^RPY_XYZ\s*(\w.*\w)/) {
	my @lst = split(/\s+/,$1);
	print "unit_$unit.set_rpy_xyz([" . join(',',@lst) . "])\n";
    } elsif ($_ =~ /^DH\s*(\w.*\w)/) {
	my @lst = split(/\s+/,$1);
	print "unit_$unit.set_dh([" . join(',',@lst) . "])\n";
    } elsif ($_ =~ /^(\w+)/) {
	print "# DO NOT KNOW WHAT TO DO WITH $_\n";
    } else {
	print "# $_\n";
    }
}

if (!$configured{$unit}) {
    print "unit_$unit.configured()\n";
    $configured{$unit} = 1;
}
if (!$applied{$unit}) {
    print "unit_$unit.complete()\n";
    $applied{$unit} = 1;
}


