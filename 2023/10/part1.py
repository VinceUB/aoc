#!/usr/bin/env python3.10
from sys import stdin
from common import *

def main():
    field = Field.from_file(stdin);

    directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

    for d in directions:
        try:
            i = 1
            whence = field.animal
            x = d[0] + field.animal[0]
            y = d[1] + field.animal[1]
            while True:
                #print(f"{field.distance_map()}\n\n")

                backup = (x, y)
                if field.get(x, y).distance > i:
                    field.get(x, y).distance = i;
                (x, y) = field.get(x, y).next(whence);
                whence = backup
                i+=1
        except MovementException as e:
            print(f"On delta {d}, got: {e}")
            continue

    maximum = 0
    for column in field.grid:
        for point in column:
           if point.distance != CONST_INFINITY and point.distance > maximum:
               maximum = point.distance

    print(field.distance_map())
    print(f"Max distance is {maximum}")



if __name__ == "__main__":
    main()