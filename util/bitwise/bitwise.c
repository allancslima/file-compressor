#include <stdio.h>
#include <string.h>
#include "bitwise.h"

unsigned char bits_to_byte(char *bits)
{
    unsigned char bits_len = strlen(bits);

    if (bits_len > 8) {
        return 0;
    }
    unsigned char n = 0;
    int i;

    for (i = bits_len - 1; i >= 0; i--) {
        if (bits[i] == '1') {
            n = set_bit(n, bits_len - 1 - i);
        }
    }
    return n;
}

int is_bit_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}
