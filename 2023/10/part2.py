#!/usr/bin/env python3.10
from sys import stdin
from common import *

def main():
    field = Field.from_file(stdin)

    field.create_loop()

    '''inside_loop = False;
    is_in_loop = True if field.get(0, 0).loop==Pipe.LOOP else False
    for y in range(field.height()):
        for x in range(field.width()):
            print(field.inside_outside_map())
            if field.get(x, y).loop==Pipe.LOOP:
                if not is_in_loop:
                    is_in_loop = True
                else:
                    try:
                        field.get(x, y).next((x-1, y))
                    except MovementException:
                        inside_loop = not inside_loop
            else:
                field.get(x, y).loop = Pipe.INSIDE if inside_loop else Pipe.OUTSIDE
                is_in_loop = False'''

    

    print(field.inside_outside_map())



if __name__ == "__main__":
    main()