#!/usr/bin/perl
use 5.20.0;
use warnings FATAL => 'all';
use autodie;
use Data::Dumper;

my $file = shift || die;

my $items = [];

open my $data, "<", $file;
while (<$data>) {
    chomp;
    my ($ii, $vol, $val) = split /\t/;
    push @$items, {ii => $ii, vol => $vol, val => $val};
}
close $data;

sub score {
    my ($xs) = @_;
    my $yy = 0;
    for my $item (@$xs) {
        $yy += $item->{val};
    }
    return $yy;
}

sub legal {
    my ($xs) = @_;
    my $total = 0;
    for my $item (@$xs) {
        $total += $item->{vol};
    }
    return $total >= 1.0;
}

sub head {
    my ($xs) = @_;
    return $xs->[0];
}

sub tail {
    my ($xs) = @_;
    say "tail of: " . Dumper($xs);
    my $ys = [];
    for my $ii (1..((scalar @$xs)-1)) {
        say $ii;
        push @$ys, $xs->[$ii];
    }
    say "is: " . Dumper($ys);
    return $ys;
}

sub copy {
    my ($xs) = @_;
    my $ys = [];
    for my $ii (0..((scalar @$xs)-1)) {
        push @$ys, $xs->[$ii];
    }
    return $ys;
}

sub powerset {
    my ($items) = @_;
    say Dumper($items);
    if (scalar @$items == 0) {
        return [];
    }
    
    my $hd = head($items);
    my $tl = tail($items);
    say Dumper({hd => $hd, tl => $tl});

    my $tail_pset = powerset($tl);

    my $ys = [];
    for my $list (@$tail_pset) {
        push @$ys, copy($list);
        push @$list, $hd;
        push @$ys, $list;
    }

    return $ys;
}

sub solve {
    my ($items) = @_;
    my $lists = powerset($items);
    my $best_score = 0;
    my $best_list  = [];

    for my $list (@$lists) {
        say Dumper($list);
        if (legal($list)) {
            if (score($list) > $best_score) {
                $best_list = $list;
            }
        }
    }
    
    return $best_list;
}

print Dumper(solve($items));


