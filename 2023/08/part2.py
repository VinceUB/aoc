#!/usr/bin/env python3

class Element:
    all = {}; #Apparently this makes it static?? Caught me out on the previous days

    def __init__(self, name, l: str, r: str):
        self.name = name;
        self.l = l;
        self.r = r;

        self.all[name] = self;
    
    def next(self, direction: str):
        if direction=='R':
            return self.all[self.r];
        else:
            return self.all[self.l];

    def __repr__(self):
        return f"Element({self.name}, {self.l}, {self.r})"
    
    @classmethod
    def gofrom(Self, froms: list, instructions: str):
        i = 0;
        
        while True:
            direction = instructions[i%(len(instructions))];
            
            #print(f"{froms} -> {direction}");

            for j in range(len(froms)):
                froms[j] = froms[j].next(direction)
            

            all_Zs = True
            
            for e in froms:
                if not e.name.endswith('Z'):
                    all_Zs = False
                    break;
            
            if all_Zs:
                break;
            
            if i % 1000 == 0:
                print(i);

            i += 1;

        return i+1;


from sys import stdin

def main(argc: int, argv: list):
    instructions = stdin.readline().strip();
    print(instructions);
    stdin.readline();

    As = [];

    for line in stdin:
        e = Element(line.split(' = ')[0], line.split('(')[1].split(',')[0], line.split(', ')[1].split(')')[0]); #I should've just used regex
        if e.name.endswith('A'):
            As.append(e);

    print(f"Answer: {Element.gofrom(As, instructions)}");

if __name__ == "__main__":
    main(1, "/root/aoc/2023/08/part1.py");
