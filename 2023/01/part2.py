#!/usr/bin/env python3

digits = [  'one',   'two', 'three',
           'four',  'five',   'six',
          'seven', 'eight',  'nine']

def get_number(line: str) -> int:
    first_digit = 0 #Input does not contain zeros
    last_digit = 0

    def add_digit(dig: int):
        nonlocal first_digit, last_digit
        if first_digit==0:
            first_digit = dig
        else:
            last_digit = dig

    for i in range(len(line)):
        if line[i].isdigit():
            add_digit(int(line[i]))
        else:
            if   line[i:i+3] in digits:
                add_digit(digits.index(line[i:i+3])+1)
            elif line[i:i+4] in digits:
                add_digit(digits.index(line[i:i+4])+1)
            elif line[i:i+5] in digits:
                add_digit(digits.index(line[i:i+5])+1)

    if last_digit==0:
        last_digit = first_digit

    return int(str(first_digit)+str(last_digit))

from sys import stdin

total = 0
for line in stdin:
    total += get_number(line)

print(total)
