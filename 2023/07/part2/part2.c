#include <stdio.h>
#include <stdlib.h>
#include "hand.h"

Card char_to_card(char c){
	switch (c){
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			return TWO + c-'2';
		case 'T':
			return TEN;
		case 'J':
			return JOKER;
		case 'Q':
			return QUEEN;
		case 'K':
			return KING;
		case 'A':
			return ACE;
		default:
			fprintf(stderr, "Character '%c' is not valid", c);
			exit(-1);
	}
}

const char* type_name(HandType t){
	switch(t){
		case HIGH_CARD:
			return "High card";
		case ONE_PAIR:
			return "One pair";
		case TWO_PAIR:
			return "Two pair";
		case THREE_OF_A_KIND:
			return "Three of a kind";
		case FULL_HOUSE:
			return "Full house";
		case FOUR_OF_A_KIND:
			return "Four of a kind";
		case FIVE_OF_A_KIND:
			return "Five of a kind";
		default:
			return "Unknown card type";
	}
};

int main(int argc, char** argv){
	Hand handv[10000]; //Assume there'll never be more than 10k hands
	int handc = 0;

	FILE* f = fopen(argv[1], "r");

	char line[100];
	while(fgets(line, 99, f)){
		for (int i = 0; i < HAND_SIZE; i++) {
			handv[handc].c[i] = char_to_card(line[i]);
			printf("%c", line[i]);
		}

		handv[handc].bid = strtol(&(line[HAND_SIZE]), NULL, 10);
		printf(" %3d. Type: %s\n", handv[handc].bid, type_name(type(handv[handc])));
		handc++;
	}

	qsort(handv, handc, sizeof(Hand), hand_compare);

	long long int total = 0;
	for (int i = 0; i < handc; ++i) {
		total += handv[i].bid * (i+1);
		printf("%04d * %04d, %s\n", i+1, handv[i].bid, hand_to_str(handv[i]));
	}

	printf("%lld\n", total);
}