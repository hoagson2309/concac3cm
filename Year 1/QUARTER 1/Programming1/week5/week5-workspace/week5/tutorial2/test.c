int count_false(const bool values[], int size) {
    int amount_of_false = 0;
    for (int i = 0; i < size; i++)
    {
        if (!values[i])
        {
            amount_of_false++;
        }
        
    }
    return amount_of_false;    
}

int select_face_down_card(const bool values[], int size) {
    int index = 8;
    while (index < 0 || index > 7 || values[index] == true)
    {
        printf ("Choose a card by entering its order: ");
        index = read_int();
        if (index < 0 || index  > 7) 
        {
            printf ("You may only choose between 0 and 7 (It is what it is brother). \n");
        } else if (values[index]) {
            printf ("This card is facing up already! \n");
        }
    }
    
    return index;
}

void print_cards(const int cards[], const bool face_up[], int size) {
    printf ("\n");
    for (int i = 0; i < size; i++)
    {
        printf ("%2d ", i + 1);
    }
    printf ("\n");
    for (int ii = 0; ii < size; ii++)
    {
        if (face_up[ii])
        {
            printf ("%2d ", cards[ii]);
        } else {
            printf ("** ");
        }
        
    }
    printf ("\n \n");          
}