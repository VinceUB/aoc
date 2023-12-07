#include <stdio.h>
#include <stdlib.h>
#include "hand.h"

Card char_to_card(char c){
	switch (c){
		case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			return c-'2';
		case 'T':
			return TEN;
		case 'J':
			return JACK;
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
		printf(" %d\n", handv[handc].bid);
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