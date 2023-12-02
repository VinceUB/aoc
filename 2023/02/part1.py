#!/usr/bin/env python3

from sys import stdin
from common import Game

total = 0

for line in stdin:
    game = Game(line.strip())
    if game.validate():
        total += game.identifier

print(total)

