#include <stdio.h>
#include "functions.h"
#include "morefunctions.h"

#define DECK_SIZE 52

typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } suit_t;
typedef enum { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING } rank_t;

typedef struct {
    suit_t suit;
    rank_t rank;
} playing_card_t;

typedef struct {
    playing_card_t cards[DECK_SIZE];
    size_t count;
} deck_t;

/// @brief Builds a standard deck of 52 playing cards.
/// @param cards The array to store the playing cards.
void build_deck(playing_card_t cards[]);

/// @brief Draws a number of cards from a deck.
/// @param target_deck The deck to draw cards into.
/// @param source_deck The deck to draw cards from.
/// @param count The number of cards to draw.
/// @return The number of cards actually drawn.
int draw_cards(deck_t *target_deck, deck_t *source_deck, size_t count);

/// @brief Prints a playing card.
/// @param card The card to print.
void print_card(const playing_card_t *card);

/// @brief Prints all cards in a deck.
/// @param deck The deck to print.
void print_deck(const deck_t *deck);

int main(void) {
    deck_t deck;
    build_deck(deck.cards);
    deck.count = DECK_SIZE;
    shuffle(deck.cards, DECK_SIZE, sizeof(playing_card_t));

    while (deck.count > 0) {
        printf("There are %zu cards left in the deck.\n", deck.count);

        printf("How many cards would you like to draw? ");
        int count = read_int();

        deck_t hand = { .count = 0 };
        int drawn = draw_cards(&hand, &deck, count);

        printf("Here are the %d cards you've drawn:\n", drawn);
        print_deck(&hand);
    }
}

void build_deck(playing_card_t cards[]) {
    size_t count = 0;
    for (suit_t suit = HEARTS; suit <= SPADES; suit++) {
        for (rank_t rank = ACE; rank <= KING; rank++) {
            cards[count++] = (playing_card_t) { suit, rank };
        }
    }
}

int draw_cards(deck_t *target_deck, deck_t *source_deck, size_t count) {
    if (source_deck->count < count) {
        // if the source_deck doesn't have enough cards, draw all of them
        count = source_deck->count;
    }

    // TODO: remove count cards from source_deck and add them to target_deck
    //       make sure to update the count of both decks
    for(size_t i = 0; i < count; i++) {
        target_deck->cards[target_deck->count] = source_deck->cards[source_deck->count - 1 - i];
        target_deck->count++;
    }

    // Update source_deck count
    source_deck->count -= count;

    // return the number of cards actually drawn
    return count;
}

void print_card(const playing_card_t *card) {
    const char *suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char *ranks[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

    if (card->rank < ACE || card->rank > KING || card->suit < HEARTS || card->suit > SPADES) {
        printf("Invalid card\n");
    }
    else {
        printf("%s of %s\n", ranks[card->rank], suits[card->suit]);
    }
}

void print_deck(const deck_t *deck) {
    // TODO: print all cards in the deck using print_card
    for(size_t i = 0; i < deck->count; i++){
        print_card(&deck->cards[i]);
    }
}
    
