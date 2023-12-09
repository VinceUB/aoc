#!/usr/bin/env python3

class Sequence: #Making a class was totes overengineering
    def __init__(self, seq: list):
        self.seq = seq;

    def differences(self):
        out = [];
        for i in range(len(self.seq)-1):
            out.append(self.seq[i+1] - self.seq[i]);
        return self.__class__(out);

    def extrapolate(self) -> int:
        if all(num==0 for num in self.seq):
            return 0;

        return self.seq[-1] + self.differences().extrapolate();

from sys import stdin

def main(argc: int, argv: list) -> int:
    total = 0
    for line in stdin:
        total += Sequence([int(v) for v in line.split(' ')]).extrapolate();

    print(total);

if __name__=='__main__':
    main(3, ['/usr/bin/wine', '/mnt/dos/Program Files/Python/Python38/python3.exe', '/root/Documents/aoc/2023/09/part1.py'])

