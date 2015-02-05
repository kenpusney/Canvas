#!/usr/bin/env perl

use warnings;
use strict;


opendir(my $dh, "src") or die;

while(my $file = readdir $dh) {
    if($file =~ /.*\.cpp/) {
        print "Compiling [src/$file]\n";
        `clang++ -stdlib=libc++ -std=c++1y -Wall -pg -g2 -c src/$file -o obj/$file.o`; 
    }
}

closedir $dh;

`clang++ obj/*.o -o bin/target`
