#!/usr/bin/perl
use 5.20.0;
use warnings FATAL => 'all';

my $nn = shift;


for my $ii (1 .. $nn) {
    my $vol = rand() / 5;
    my $val = 100 * rand();
    say "$ii\t$vol\t$val";
}
