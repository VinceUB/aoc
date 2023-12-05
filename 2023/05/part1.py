#!/usr/bin/env python3

# !!!!IMPORTANT!!!! For this to work, you've gotta append an extra newline at the end of your input
# I have no clue why


class Map:
    dest_start = 0
    source_start = 0
    range_length = 0

    def __init__(self, inp: str):
        self.dest_start   = int(inp.split(' ')[0])
        self.source_start = int(inp.split(' ')[1])
        self.range_length = int(inp.split(' ')[2])

    def apply(self, num: int) -> (bool, int):
        if self.source_start <= num < self.source_start+self.range_length:
            print(f"\tConverts {num} to {self.dest_start+(num-self.source_start)} because it is between {self.source_start} and {self.source_start+self.range_length}")
            return (True, self.dest_start + (num-self.source_start))
        else:
            return (False, num)

class Section:
    name = "" #For debug (if needed) (Update: it was needed)
    maps = []

    def __init__(self, name: str):
        self.name = name.strip()
        self.maps = []

    def add_map(self, m: Map):
        self.maps.append(m)

    def apply(self, num: int) -> int:
        for m in self.maps:
            new = m.apply(num)
            if new[0]: #aka, if the filter applied
                return new[1]
        return num

from sys import stdin

if __name__ == '__main__':
    seeds = []
    current_section = Section("none")
    for line in stdin:
        if line.startswith('seeds: '):
            seeds = [int(s) for s in line.split(': ')[1].split(' ')]
        
        elif line.endswith('map:\n'):
            current_section = Section(line.split(' ')[0])
            print(f"New section: {current_section.name}")
    
        elif line == '\n':
            for i in range(len(seeds)):
                seeds[i] = current_section.apply(int(seeds[i]))
            print(f"Seeds: [{' '.join([str(seed) for seed in seeds])}]")

        else:
            current_section.add_map(Map(line))

    lowest = 1_000_000_000_000

    for seed in seeds:
        if seed < lowest:
            lowest = seed

    print(f"Lowest location: {lowest}")
