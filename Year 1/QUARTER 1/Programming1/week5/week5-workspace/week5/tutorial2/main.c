#include <stdio.h>
#include "game.h"

int main(void) {
    printf("Welcome to the memory game!\n");
    int cards[8] = {1, 1, 2, 2, 3, 3, 4, 4};
    bool face_up[sizeof(cards) / sizeof(cards[0])] = {false};
    const int nr_of_cards = sizeof(cards) / sizeof(cards[0]);
    int rounds = 0;     // the number of rounds played

    

    // TODO: shuffle the cards
    shuffle(face_up, nr_of_cards, random_int(1,20));

    while (count_false(face_up, nr_of_cards) > 0) {
        // TODO: print the cards
        print_cards(cards, face_up, nr_of_cards);
        // TODO: ask the user to select two cards
        printf("Please select face down cards")
        int a = select_face_down_card(face_up, nr_of_cards);
        face_up[a] == true;
        print_cards(cards, face_up, nr_of_cards);

        int b = select_face_down_card(face_up, nr_of_cards);
        face_up[b] == true;
        print_cards(cards, face_up, nr_of_cards);

        // TODO: check if the selected cards are a pair. If not, turn them face down again. If they are, tell the user he found a match
        if (cards[a] == cards[b]){
            printf("You found a match! \n");
        }else{
            printf("This wasn't a pair! \n");
            cards[a] = cards[b] = false;
        }

        rounds++;
    }
    // TODO: print the cards (they're all turned face up now)
    print_cards(cards, face_up, nr_of_cards);
    printf("Congratulations, you found all pairs in %d rounds!\n", rounds);
}