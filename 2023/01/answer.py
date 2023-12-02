#!/usr/bin/env python3

from sys import stdin

total = 0;

for line in stdin:
    number = "";
    for char in line:
        if char.isdigit():
            if not number:
                number = char;
            else:
                number = '' + number[0] + char;
    if len(number) == 1:
        number = '' + number[0] + number[0]
    total += int(number);
    print(f"+{number}={total}");

print(total);
