
from sys import stdin

cards = []

class Card:
    winners = []
    numbers = []
    index = -1

    def __init__(self, index):
        self.winners = []
        self.numbers = []
        self.index = index

    def score(self) -> int:
        intersect = list(set(self.winners) & set(self.numbers))
        
        total = 1
        for i in range(len(intersect)):
            total += cards[self.index+i+1].score()

        return total




for line in stdin:
    line = line.strip();
    line = line.split(': ')[1];

    card = Card(len(cards))
    
    for number in line.split(" | ")[0].split(" "):
        if number != '':
            card.winners.append(number)
    for number in line.split(" | ")[1].split(" "):
        if number != '':
            card.numbers.append(number)
    
    cards.append(card)


total = 0
for card in cards:
    total += card.score();

print(total)
