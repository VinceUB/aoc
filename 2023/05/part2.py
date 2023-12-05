#!/usr/bin/env python3

from part1 import *
from sys import stdin

if __name__ == '__main__':
    seeds = []
    current_section = Section("none")
    for line in stdin:
        if line.startswith('seeds: '):
            seeds_kindaraw = [int(s) for s in line.split(': ')[1].split(' ')]

            for i in range(0, len(seeds_kindaraw), 2):
                print(f"Adding seed {seeds_kindaraw[i]} of length {seeds_kindaraw[i+1]}");
                seeds += range(seeds_kindaraw[i], seeds_kindaraw[i]+seeds_kindaraw[i+1])
        
        elif line.endswith('map:\n'):
            current_section = Section(line.split(' ')[0])
            print(f"New section: {current_section.name}")
    
        elif line == '\n':
            for i in range(len(seeds)):
                seeds[i] = current_section.apply(int(seeds[i]))
            #print(f"Seeds: [{' '.join([str(seed) for seed in seeds])}]")

        else:
            current_section.add_map(Map(line))

    for i in range(len(seeds)):
        seeds[i] = current_section.apply(int(seeds[i]))
    #print(f"Seeds: [{' '.join([str(seed) for seed in seeds])}]")
    
    lowest = 1_000_000_000_000

    for seed in seeds:
        if seed < lowest:
            lowest = seed

    print(f"Lowest location: {lowest}")
