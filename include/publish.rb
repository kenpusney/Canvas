#!/usr/bin/env ruby

visited = []

cont = []

file = ARGV[0]

cont << file

def visit(file, visited, cont)
    return if (visited.include? file)
    visited << file
    File.open(file) do |f|
        f.readlines.each do |s|
            if s.strip =~ /#include\s*"(.*)"/
                depends = $1;
                if  !(visited.include? depends)
                    cont << File.dirname(f) + "/" + depends
                end
            end
        end
    end
end

while not cont.empty?
    visit(cont.shift, visited, cont)
end

File.open("#{file}.public.hpp", 'w').write visited.map {|file|
    File.open(file).read
}.map { |s|
    s.gsub(/#include\s*"(.*)"[\r\n]+/, "")
}.reduce(:concat)