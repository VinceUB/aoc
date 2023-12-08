#!/usr/bin/env python3

class Element:
    all = {}; #Apparently this makes it static?? Caught me out on the previous days

    def __init__(self, name, l: str, r: str):
        self.name = name;
        self.l = l;
        self.r = r;

        self.all[name] = self;

    def __repr__(self):
        return f"Element({self.name}, {self.l}, {self.r})"

    def goto(self, instructions: str, to: str):
        i = 0;
        
        current = self;
        while current.name != to:
            print(f"{current} -> {instructions[i%(len(instructions)-1)]}")
            if instructions[i%(len(instructions)-1)] == 'R':
                current = self.all[current.r];
            else:
                current = self.all[current.l];

            i += 1;

        return i;


from sys import stdin

def main(argc: int, argv: list):
    instructions = stdin.readline();
    stdin.readline();

    for line in stdin:
        Element(line.split(' = ')[0], line.split('(')[1].split(',')[0], line.split(', ')[1].split(')')[0]); #I should've just used regex

    print(f"Answer: {Element.all['AAA'].goto(instructions, 'ZZZ')}");

if __name__ == "__main__":
    main(1, "/root/aoc/2023/08/part1.py");
