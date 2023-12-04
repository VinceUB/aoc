
from sys import stdin

total = 0;

for line in stdin:
    line = line.strip();
    line = line.split(': ')[1];

    winners = []
    card = []
    
    for number in line.split(" | ")[0].split(" "):
        if number != '':
            winners.append(number)
    for number in line.split(" | ")[1].split(" "):
        if number != '':
            card.append(number)

    i = list(set(winners) & set(card))
     
    if len(i) > 0:
        total += 2**(len(i)-1);


print(total)

