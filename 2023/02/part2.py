#!/usr/bin/env python3

from common import Game, Handful
from sys import stdin

total = 0

for line in stdin:
    game = Game(line.strip())

    total += game.minimum_set().power()

print(total)
