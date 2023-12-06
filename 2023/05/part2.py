#!/usr/bin/env python3

class NumberRange:
    start = 0
    end = 0

    def __init__(self, start: int, end: int):
        self.start = start
        self.end = end

    def __str__(self):
        return f"{self.start}-{self.end}"
    
    def is_valid(self) -> bool:
        return self.start<=self.end
    
    def union(self, nr) -> list:
        if   (nr.start <= self.start and self.end <= nr.end): #nr contains self
            return [ nr ]
        elif (self.start <= nr.start and self.end <= nr.end): 
            return [ NumberRange(self.start, nr.end) ]
        elif (nr.start <= self.start and nr.end <= self.end):
            return [ NumberRange(nr.start, self.end) ]
        elif (self.start <= nr.start and nr.end <= self.end):
            return [ self ]
        else: # No overlap
            return [ self, nr ]
    
    # TODO: DEAL WITH CASES WHERE |-| |_|
    def intersect(self, nr) -> list:
        if   (nr.start <= self.start and self.end <= nr.end): #nr contains self
            return [ self ]
        elif (self.start <= nr.start and self.end <= nr.end): 
            return [ NumberRange(nr.start, self.end) ]
        elif (nr.start <= self.start and nr.end <= self.end):
            return [ NumberRange(self.start, nr.end) ]
        elif (self.start <= nr.start and nr.end <= self.end):
            return [ nr ]
        else: # No overlap
            return [ ]

    def not_then_intersect(self, nr) -> list: # equivalent of (!self) & nr
        if   (nr.start <= self.start and self.end <= nr.end): #nr contains self
            return [ NumberRange(nr.start, self.start-1), NumberRange(self.end+1, nr.end) ]
        elif (self.start <= nr.start and self.end <= nr.end): 
            return [ NumberRange(self.end+1, nr.end) ]
        elif (nr.start <= self.start and nr.end <= self.end):
            return [ NumberRange(nr.start, self.start-1) ]
        elif (self.start <= nr.start and nr.end <= self.end):
            return [ ]
        else: # No overlap
            return [ nr ]


class Map:
    dest_start = 0
    source_start = 0
    range_length = 0
    
    def __init__(self, d: int, s: int, r: int):
        self.dest_start = d
        self.source_start = s
        self.range_length = r

    @classmethod
    def parse(Self, inp: str):
        self = Self(
                int(inp.split(' ')[0]),
                int(inp.split(' ')[1]),
                int(inp.split(' ')[2]))

        return self

    def __str__(self):
        return f"{self.dest_start} {self.source_start} {self.range_length}"

    def dest_last(self) -> int:
        return self.dest_start+self.range_length-1

    def source_last(self) -> int:
        return self.source_start + self.range_length - 1

    def reverse_apply(self, nums: NumberRange) -> NumberRange:
        source = NumberRange(0, 0)
        if nums.start<self.dest_start:
            source.start = self.dest_start
        else:
            source.start = nums.start

        if nums.end>self.dest_last():
            source.end = self.dest_last()
        else:
            source.end = nums.end

        distance = self.dest_start-self.source_start

        source.start -= distance
        source.end -= distance
        return source

    def apply(self, source: NumberRange) -> tuple:
        (accept, rejects) = self.apply_no_translate(source)

        return (self.translate(accept), rejects)

    def apply_no_translate(self, source: NumberRange) -> tuple: #(NumberRange accepted, NumberRange[] rejected)
        '''dest = NumberRange(0, 0)
        rejects = []
        if source.start < self.source_start:
            rejects.append(NumberRange(source.start, self.source_start-1))
            dest.start = self.source_start
        else:
            dest.start = source.start;

        if source.end > self.source_last():
            rejects.append(NumberRange(self.source_last()+1, source.end))
            dest.end = self.source_last()
        else:
            dest.end = source.end;'''
        me_as_number_range = NumberRange(self.source_start, self.source_last())
        
        accept = ''
        accepts = me_as_number_range.intersect(source)
        if len(accepts) == 0:
            accept = NumberRange(0, -1)
        else:
            accept = accepts[0]
            
        return (accept, 
                src_as_number_range.not_then_intersect(source))

    def translate(self, source: NumberRange) -> NumberRange:
        dest = source
        
        distance = self.dest_start-self.source_start

        dest.start += distance
        dest.end += distance
        
        return dest

    def possible_outputs(self) -> NumberRange:
        return NumberRange(self.dest_start, self.dest_start+self.range_length-1)

class Section:
    name = ""
    maps = []

    def __init__(self, name: str):
        self.name = name.strip()
        self.maps = []

    def add_map(self, m: Map):
        self.maps.append(m)

    def reverse_apply(self, nums: NumberRange) -> list: #returns a list of valid numberranges
        output_nums = []
        for m in self.maps:
            output = m.reverse_apply(nums)
            if output.is_valid():
                output_nums.append(output)

        return output_nums

    def apply(self, source: NumberRange) -> tuple: #(accepts, rejects)
        accepts = []
        rejects = []
        for m in self.maps:
            (m_accept, m_rejects) = m.apply(source)
            if m_accept.is_valid():
                accepts.append(m_accept)
            rejects += m_rejects

        return (accepts, rejects)
    
    def apply_no_translate(self, source: NumberRange) -> tuple: #(accepts, rejects)
        accepts = []
        rejects = []
        for m in self.maps:
            (m_accept, m_rejects) = m.apply_no_translate(source)
            if m_accept.is_valid():
                accepts.append(m_accept)
            rejects += m_rejects

        return (accepts, rejects)

            


def parse(file) -> tuple: #returns (seeds, list of sections)
    seeds = []
    sections = []
    for line in file:
        if line.startswith("seeds: "):
            seeds_string_exploded = [int(s) for s in line.split(': ')[1].split(' ')]
            for i in range(0, len(seeds_string_exploded), 2):
                seeds.append(NumberRange(seeds_string_exploded[i], seeds_string_exploded[i]+seeds_string_exploded[i+1]-1))

        elif line.endswith("map:\n"):
            sections.append(Section(line.split(' ')[0]))
        elif line=='\n':
            ...
        else:
            sections[-1].add_map(Map.parse(line))

    return (seeds, sections)

def nr_list_str(nr):
    return ' '.join([str(n) for n in nr]);

if __name__ == '__main__':
    from sys import stdin
    
    (seeds, sections) = parse(stdin)
    print("Parsed seed and sections")

    '''numbers = [m.possible_outputs() for m in sections[-1].maps]

    for section in reversed(sections):
        new_list = []
        for number_range in numbers:
            new_list += section.reverse_apply(number_range)
        numbers = new_list;

    # At this point, we should only have the numbers left that can be sourced to a seed
    
    print(f"Result: {' '.join([str(n) for n in numbers])}")'''

    source = seeds

    for section in sections:
        print(f"Applying section {section.name}. Source has length {len(source)}")
        all_accepts = []
        all_rejects = []
        for number_range in source:
            (accepts, rejects) = section.apply_no_translate(number_range)
            print(f"\tApplied map from {number_range} to get accepts {nr_list_str(accepts)} and rejects {nr_list_str(rejects)}")
            all_accepts += accepts
            all_rejects += rejects
        
        dest = []

        all_rejects_that_dont_intersect_with_any_accepts = []

        for reject in all_rejects:
            for accept in all_accepts:
                all_rejects_that_dont_intersect_with_any_accepts += accept.not_then_intersect(reject);
        for reject in all_rejects_that_dont_intersect_with_any_accepts:
            if reject.is_valid():
                dest.append(reject)
        
        all_transposed_accepts = []

        for accept in all_accepts:
            all_transposed_accepts.append(section.apply(accept)[0][0]) #All foreign characters should've been stripped, so it just needs to be transposed

        dest += all_transposed_accepts
        
        print(f"\tDest: {nr_list_str(dest)}")
        
        source = dest
    
    minimum = 1_000_000_000_000
    for nr in source:
        if nr.start<minimum:
            minimum = nr.start

    print(f"Minimum is {minimum}")
