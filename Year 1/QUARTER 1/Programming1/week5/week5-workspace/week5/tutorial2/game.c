#include <stdio.h>
#include "game.h"
#include "functions.h"

void shuffle(int values[], int size, int how_many_times)
{
    for (int i = 0; i < how_many_times; i++)
    {
        int index1 = random_int(0, size - 1);
        int index2 = random_int(0, size - 1);
        swap_elements(values, index1, index2);
    }
}

void swap_elements(int values[], int index1, int index2)
{
    int temp;
    temp = values[index1];
    values[index1] = values[index2];
    values[index2] = temp;
}

int count_false(const bool values[], int size)
{
    int falsenum = 0;
    for (int i = 0; i < size; i++)
    {
        if (!values[i])
            falsenum++;
    }
    return falsenum;
}

int select_face_down_card(const bool values[], int size){
    int a;
    printf("Choose face down cards: ");
    a = read_int();
    while (a < 0 || a > size - 1 || values[a] == true){
        if (a < 0 || a > size - 1){
            printf("TRY AGAIN!");
        }
        else if (values[a]){
            printf("You've chosen a face up card! Try again");
        }
        else{
            return a;
        }
        printf("Choose face down cards: ");
        a = read_int();
    }
    return a;
}

void print_cards(const int cards[], const bool face_up[], int size){
    for (int i=0; i<size; i++){
        printf("%2d: ",i);
    }
    printf("\n");
    for (int i=0; i<size; i++){
        if(face_up[i]){
            printf("%2d: ", cards[i]);
        } else{
            printf("**");
        }
    }
}