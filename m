#!/usr/bin/env perl

use warnings;
use strict;

use File::Path qw(make_path remove_tree);

## definitions;

make_path '.build';

my %tasks;

my ($task, $target) = @ARGV;
$task = $task || "build";
$target = $target || "test";

sub task {
    my ($name, $handler) = @_;
    $tasks{$name} = $handler;
}

sub depends {
    for(@_) {
        print "Running task \e[1m<<$_>>\e[0m\n";
        $tasks{$_}();
    }
}

sub then {
    depends(@_)
}

sub block {
    for(@_) {
        exit 0 if $task eq $_;
    }
}

## variables;

my %mtimes;

sub compile {
    my ($filename) = @_;
    my $time = (stat($filename))[9];
    if (not exists($mtimes{$filename}) or $time != $mtimes{$filename}) {
        $mtimes{$filename} = $time;
        print "Compiling [\e[32;1m$filename\e[39;0m]\n";
        system "clang++ -stdlib=libc++ -Iinclude -std=c++1z -Wall -c $filename -o obj/$filename.o";
    }
}

sub library {
	my ($libname) = @_;

	print "Building library [\e[32;1m$libname\e[39;0m]\n";
	system "ar rc lib/lib$libname.a obj/src/$libname.*.o"
}

## tasks;

task "BEFORE", sub {
    
    if (-e ".build/mtime") {
        open(my $fh, "<", ".build/mtime");
        while (<$fh>) {
            chomp;
            my ($key, $value) = split /=/;
            $mtimes{$key} = $value if $key && $value;
        }
        close $fh
    }
    
};

task "AFTER", sub {
    
    block "clean", "commit";
    open(my $fh, ">", ".build/mtime");
    while(my ($key, $value) = each %mtimes) {
        print $fh "$key=$value\n" if $key && $value;
    }
    close $fh
};

task "clean", sub {
    for(qw(bin obj .build lib)) {
        remove_tree $_;
    }
};

task "env", sub {
    make_path 'bin';
    make_path 'obj/src';
    make_path 'lib';
    make_path 'obj/test';
};

task "build", sub {
    
    depends "env";
    opendir(my $dh, "src") or die;
    
    while(my $file = readdir $dh) {
        if($file =~ /.*\.cpp/) {
            compile "src/$file"
        }
    }
    closedir $dh;
    system "ar rc lib/libcanvas.a obj/src/*.o";
};

task "lib", sub {
	
	depends "build";
	
	library "ropto";
};

task "test", sub {
    
    depends "build";
    
    opendir(my $dh, "test") or die;
    
    while(my $file = readdir $dh) {
        if($file =~ /.*\.cpp/) {
            compile "test/$file";
        }
    }
    closedir $dh;
    system "clang++ lib/libcanvas.a obj/test/*.o -o bin/$target";
    
    then "run"
};

task "run", sub {
    system "./bin/$target";
};

task "commit", sub {

    depends "clean";
    
    depends "test";
    then "clean";
    
    system "git commit -p";
    system "git push -u origin master";
};

## execution;

$tasks{"BEFORE"}() if $tasks{"BEFORE"};

if (my $proc = $tasks{$task}) {
    print "Running task \e[1m<<$task>>\e[0m\n";
    &$proc();
    print "......\e[1m[DONE]\e[0m\n"
} else {
    print "\e[41;1mNo such task <<$task>>\e[49;0m\n";
}

$tasks{"AFTER"}() if $tasks{"AFTER"};
