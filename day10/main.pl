#!/usr/bin/perl

use 5.010;
use strict;
use warnings;

sub parse_line {
    my $line = $_[0];

    chomp($line);
    my @words = split / /, $line;

    return ($words[0], scalar @words > 1 ? int($words[1]) : undef);
}

my $file = 'input.txt';
open my $info, $file or die "Could not open $file: $!";

my $x = 1;
my $strength = 0;
my $cycles = 0;

while(my $line = <$info>) {
    my ($command, $argument) = parse_line($line);
    
    # The amount of cycles this command takes
    my $count = $command eq 'addx' ? 2 : 1;

    for (my $i = 1 ; $i <= $count; $i++) {
        $cycles++;
        if (($cycles - 20) % 40 eq 0) {
            $strength += $cycles * $x;
        }
    }

    if ($command eq 'addx') {
        $x += $argument;
    }
}

close $info;

say $strength;
