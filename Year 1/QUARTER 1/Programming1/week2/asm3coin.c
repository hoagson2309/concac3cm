#include <stdio.h>
#include "functions.h"
int main() {
    double amountPaid, price;
    int change;
    int coins[] = {200, 100, 50, 20, 10, 5, 2, 1}; // Coin values in cents
    int coinCount[8] = {0}; // Array to store the count of each coin type
    int i;

    // Input the amount paid and the price of the product
    printf("Please enter the amount of money that you pay: ");
        amountPaid = read_int();
    printf("Please enter the price of the product: ");
        price = read_int();

    // Calculate the change in cents (to avoid floating-point precision issues)
    change = (int)((amountPaid - price) * 100 + 0.5);

    // Output the total change in euros and cents
    printf("You get back %.2f euro in change.\n", (amountPaid - price));

    // Calculate the number of each coin needed
    for (i = 0; i < 8; i++) {
        if (change >= coins[i]) {
            coinCount[i] = change / coins[i];
            change %= coins[i];
        }
    }

    // Print out the result for each coin type, only if the coin count is greater than 0
    for (i = 0; i < 8; i++) {
        if (coinCount[i] > 0) {
            if (coins[i] >= 100) {
                printf("You get back %d coin(s) of %d euro.\n", coinCount[i], coins[i] / 100);
            } else {
                printf("You get back %d coin(s) of %d cents.\n", coinCount[i], coins[i]);
            }
        }
    }

    return 0;
}