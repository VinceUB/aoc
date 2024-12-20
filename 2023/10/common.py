CONST_INFINITY = 100_000_000

class MovementException(Exception):
    pass

class Pipe:
    ANIMAL = 'S'

    INSIDE = 1
    LOOP = 0
    OUTSIDE = -1
    def __init__(self, x, y, char):
        self.x = x
        self.y = y
        self.type = char;...;...;...;...;...;...;...;...;...;...;
        self.distance = CONST_INFINITY if char!=self.ANIMAL else 0
        self.loop = None if char!=self.ANIMAL else self.LOOP #a.k.a. self.loop=char==self.ANIMAL

    def next(self, whence) -> (int, int):
        delta = (self.x-whence[0], self.y-whence[1])

        match self.type:
            case '|':
                if delta[0] == 0:
                    return (self.x, self.y+delta[1])
                else:
                    raise MovementException(f"Hit pipe ({self.x}, {self.y}) on the side from {whence}")
            case '-':
                if delta[1] == 0:
                    return (self.x+delta[0], self.y)
                else:
                    raise MovementException(f"Hit pipe ({self.x}, {self.y}) on the side from {whence}")
            case 'L':
                if delta == (-1, 0):
                    return (self.x, self.y-1)
                elif delta == (0, 1):
                    return (self.x+1, self.y)
                else:
                    raise MovementException(f"Hit pipe ({self.x}, {self.y}) on the side from {whence}")
            case 'J':
                if delta == (1, 0):
                    return (self.x, self.y-1)
                elif delta == (0, 1):
                    return (self.x-1, self.y);
                else:
                    raise MovementException(f"Hit pipe ({self.x}, {self.y}) on the side from {whence}")
            case '7':
                if delta == (1, 0):
                    return (self.x, self.y+1)
                elif delta == (0, -1):
                    return (self.x-1, self.y)
                else:
                    raise MovementException(f"Hit pipe ({self.x}, {self.y}) on the side from {whence}")
            case 'F':
                if delta == (-1, 0):
                    return (self.x, self.y+1)
                elif delta == (0, -1):
                    return (self.x+1, self.y)
                else:
                    raise MovementException(f"Hit pipe ({self.x}, {self.y}) on the side from {whence}")
            case '.':
                raise MovementException(f"You are on the ground. {(self.x, self.y)}.")
            case self.ANIMAL:
                raise MovementException(f"You're back to the animal. {(self.x, self.y)}.")
            case _ as c:
                raise Exception(f"Could not recognise character '{c}'.")


class Field:
    def __init__(self):
        self.grid = []
        self.animal = None

    def height(self):
        if len(self.grid)<=0:
            return 0
        else:
            return len(self.grid[0])

    def width(self):
        return len(self.grid)

    def get(self, x, y) -> Pipe:
        if x < 0 or y < 0 or x >= self.width() or y >= self.height():
            return Pipe(-1, -1, '.')
        return self.grid[x][y]

    def set(self, x, y, char):
        if char == Pipe.ANIMAL:
            if self.animal is None:
                self.animal = (x, y)
            else:
                raise Exception(f"Tried to add animal at ({x}, {y}), but there can only be one (currently at {self.animal})!")

        if self.width() <= x:
            self.grid.extend([] for _ in range(x-self.width()+1));

        if len(self.grid[x]) <= y:
            self.grid[x].extend('.' * (y-len(self.grid[x])+1))


        self.grid[x][y] = Pipe(x, y, char)

    def distance_map(self) -> str:
        number_length = 4

        me = ''

        for y in range(self.height()):
            for x in range(self.width()):
                if self.get(x, y).distance == CONST_INFINITY:
                    me += '.'*number_length + ' '
                else:
                    me += f"{self.get(x, y).distance:{number_length}} "
            me += '\n'

        return me

    def inside_outside_map(self) -> str:
        me = ''

        for y in range(self.height()):
            for x in range(self.width()):
                match self.get(x, y).loop:
                    case None:
                        me += '?'
                    case Pipe.INSIDE:
                        me += 'I'
                    case Pipe.LOOP:
                        me += self.get(x, y).type
                    case Pipe.OUTSIDE:
                        me += 'O'
            me += '\n'

        return me

    def create_loop(self):
        directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        for d in directions:
            try:
                i = 1
                whence = self.animal
                x = d[0] + self.animal[0]
                y = d[1] + self.animal[1]
                while True:
                    backup = (x, y)
                    (x, y) = self.get(x, y).next(whence);

                    self.get(x, y).loop = Pipe.LOOP

                    whence = backup
                    i += 1
            except MovementException:
                continue

    @classmethod
    def from_file(cls, file):
        self = cls()

        y = 0
        for line in file:
            x = 0
            for char in line.strip():
                self.set(x, y, char);
                x+= 1
            y+=1

        return self

