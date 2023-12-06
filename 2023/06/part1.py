#!/usr/bin/env python3 

def distance(charge_time, max_time):
    speed = charge_time #In millimetres/millisecond

    return speed * (max_time-charge_time)

def number_of_ways_to_beat_the_race(time, record):
    number = 0

    for t in range(time+1):
        if distance(t, time) > record:
            number += 1

    return number

times = []
distances = []

from sys import stdin

lines = stdin.readlines()

times     += [int(t) for t in lines[0].split(': ')[1].split()]
distances += [int(t) for t in lines[1].split(': ')[1].split()]

total = 1

for i in range(len(times)):
    total *= number_of_ways_to_beat_the_race(times[i], distances[i])

print(f"{total}")
