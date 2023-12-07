#include "hand.h"

int card_compare(const Card* a, const Card* b){
	return *a-*b;
}

char card_to_char(Card c){
	switch(c) {
		case TWO: case THREE: case FOUR: case FIVE:
		case SIX: case SEVEN: case EIGHT: case NINE:
			return c+'2';
		case TEN:
			return 'T';
		case JACK:
			return 'J';
		case QUEEN:
			return 'Q';
		case KING:
			return 'K';
		case ACE:
			return 'A';
		default:
			return '?';
	}
}

char* hand_to_str(Hand h){
	char* str = malloc(HAND_SIZE+1);
	for (int i = 0; i < HAND_SIZE; ++i) {
		str[i] = card_to_char(h.c[i]);
	}
	str[HAND_SIZE] = '\0';
	return str;
}

bool is_five_of_a_kind(Hand h){
	return h.c[0] == h.c[1] &&
	       h.c[0] == h.c[2] &&
	       h.c[0] == h.c[3] &&
	       h.c[0] == h.c[4];
}

bool is_four_of_a_kind(Hand h){
	qsort(h.c, HAND_SIZE, sizeof(h.c[0]), &card_compare);

	return (h.c[0] == h.c[1] && h.c[0] == h.c[2] && h.c[0] == h.c[3]) ||
	       (h.c[1] == h.c[2] && h.c[1] == h.c[3] && h.c[1] == h.c[4]);
}

bool is_full_house(Hand h){
	qsort(h.c, HAND_SIZE, sizeof(h.c[0]), &card_compare);

	return (h.c[0] == h.c[1] && h.c[2] == h.c[3] && h.c[2] == h.c[4]) || // AABBB
	       (h.c[0] == h.c[1] && h.c[0] == h.c[2] && h.c[3] == h.c[4]);   // AAABB
}

bool is_three_of_a_kind(Hand h){
	qsort(h.c, HAND_SIZE, sizeof(h.c[0]), &card_compare);

	return (h.c[2] == h.c[3] && h.c[2] == h.c[4]) || //ABCCC
	       (h.c[0] == h.c[1] && h.c[0] == h.c[2]) || //AAABC
		   (h.c[1] == h.c[2] && h.c[1] == h.c[3]);   //ABBBC
}

bool is_two_pair(Hand h){
	qsort(h.c, HAND_SIZE, sizeof(h.c[0]), &card_compare);

	return (h.c[0] == h.c[1] && h.c[2] == h.c[3]) || //AABBC
	       (h.c[0] == h.c[1] && h.c[3] == h.c[4]) || //AABCC
	       (h.c[1] == h.c[2] && h.c[3] == h.c[4]);   //ABBCC
}

Card is_one_pair(Hand h){
	qsort(h.c, HAND_SIZE, sizeof(h.c[0]), &card_compare);

	return (h.c[0] == h.c[1] || h.c[1] == h.c[2] ||
	        h.c[2] == h.c[3] || h.c[3] == h.c[4]);
}


HandType type(Hand h){
	if(is_five_of_a_kind(h))
		return FIVE_OF_A_KIND;
	if(is_four_of_a_kind(h))
		return FOUR_OF_A_KIND;
	if(is_full_house(h))
		return FULL_HOUSE;
	if(is_three_of_a_kind(h))
		return THREE_OF_A_KIND;
	if(is_two_pair(h))
		return TWO_PAIR;
	if(is_one_pair(h))
		return ONE_PAIR;
	else
		return HIGH_CARD;
}

int hand_compare(const Hand *a, const Hand *b) {
	HandType a_type = type(*a);
	HandType b_type = type(*b);

	printf("Comparing hands %s and %s, of types %d and %d: ", hand_to_str(*a), hand_to_str(*b), a_type, b_type);

	if (a_type == b_type) {
		for (int i = 0; i < HAND_SIZE; i++) {
			if (a->c[i] != b->c[i]) {
				printf("%d\n", a->c[i] - b->c[i]);
				return a->c[i] - b->c[i];
			}
		}
	} else {
		printf("%d\n", a_type-b_type);
		return a_type-b_type;
	}

}