#pragma once

#include <stdbool.h>
#include <stdlib.h>

#define HAND_SIZE 5

typedef enum{
	JOKER,
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	TEN, QUEEN, KING, ACE
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
	int consumed_jokers;
	Card c[HAND_SIZE];
} Hand;

HandType type(Hand);

char* hand_to_str(Hand);

int hand_compare(const Hand*, const Hand*);