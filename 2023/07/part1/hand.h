#pragma once

#include <stdbool.h>
#include <stdlib.h>

#define HAND_SIZE 5

typedef enum{
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	TEN, JACK, QUEEN, KING, ACE
} Card;

int card_compare(const Card* a, const Card* b);

typedef enum {
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIR,
	THREE_OF_A_KIND,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	FIVE_OF_A_KIND
} HandType;

typedef struct {
	int bid;
	Card c[HAND_SIZE];
} Hand;

/*bool is_five_of_a_kind(Hand);
bool is_four_of_a_kind(Hand);
bool is_full_house(Hand);
bool is_three_of_a_kind(Hand);
bool is_two_pair(Hand);
bool is_one_pair(Hand);
bool high_card(Hand);*/

HandType type(Hand);

char* hand_to_str(Hand);

int hand_compare(const Hand*, const Hand*);