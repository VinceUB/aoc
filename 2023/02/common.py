max_reds   = 12
max_greens = 13
max_blues  = 14

class Handful: #I guess Handful just means CubeSet now 
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

    def power(self):
        return self.red * self.green * self.blue


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
    
    def minimum_set(self) -> Handful:
        minimum = Handful('')

        for handful in self.handfuls:
            if handful.red > minimum.red:
                minimum.red = handful.red
            if handful.green > minimum.green:
                minimum.green = handful.green
            if handful.blue > minimum.blue:
                minimum.blue = handful.blue

        return minimum


#Man, I should've just written this in C and used scanf:(
