#!/usr/bin/env python3

max_reds   = 12
max_greens = 13
max_blues  = 14


class Game:
    handfuls: list = []
    identifier: int = 0 #I don't know if `id` is reserved, but it's highlighted in vim so I don't trust it

    def __init__(self, line):
        segments = line.split(": ")

        #Segment 0 contains the game id
        self.identifier = int(segments[0].split(' ')[1]);

        #Segment 1 contains a list of all handfuls
        self.handfuls = []
        for handful in segments[1].split('; '):
            self.handfuls.append( Handful(handful) )
    
    def validate(self):
        for h in self.handfuls:
            if not h.validate():
                return False
        return True

class Handful:
    red = 0
    green = 0
    blue = 0

    def __init__(self, hand: str):
        balls_split_by_colour = hand.split(", ")
        for balls in balls_split_by_colour:
            if balls.endswith("red"):
                self.red += int(balls.split(" ")[0])
            elif balls.endswith("green"):
                self.green += int(balls.split(" ")[0])
            elif balls.endswith("blue"):
                self.blue += int(balls.split(" ")[0])


    def validate(self):
        return max_reds >= self.red and max_greens >= self.green and max_blues >= self.blue


from sys import stdin

total = 0

for line in stdin:
    game = Game(line.strip())
    if game.validate():
        total += game.identifier

print(total)

#Man, I should've just written this in C and used scanf:(
