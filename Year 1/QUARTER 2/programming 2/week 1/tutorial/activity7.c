#include <stdio.h>

void print_raw_data(const unsigned char *data, size_t size) {
    // FIXME: print each byte in the data the raw data in hexadecimal format
    //        Example output: "0x48 0x65 0x6c 0x6c 0x6f 0x2c 0x20 0x77 0x6f 0x72 0x6c 0x64 0x21"
    // Use the printf function with the %02x format specifier to print each byte
    for (size_t i = 0; i < size; i++) {
        printf("0x%02x ", *data);
        data++;
    }
    printf("\n");  
}   

int main(void) {
    int values[] = {1, 2, 3, 4, 5};
    char str[] = "Hello, world!";
    double pi = 3.14159265359;
    short int shorts[] = {1, 2, 3, 4, 5};
    long long int long_int = 1234567890123456789;

    printf("values (array of int): ");
    print_raw_data((unsigned char *)values, sizeof(values));

    printf("str (array of char): ");
    print_raw_data((unsigned char *)str, sizeof(str));

    printf("pi (double): ");
    print_raw_data((unsigned char *)&pi, sizeof(pi));

    printf("shorts (array of short int): ");
    print_raw_data((unsigned char *)shorts, sizeof(shorts));

    printf("long_int (long long int): ");
    print_raw_data((unsigned char *)&long_int, sizeof(long_int));

    return 0;
}
