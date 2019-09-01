#ifndef BITWISE_H
#define BITWISE_H

/**
 * Checks if the bit in the given position is set.
 *
 * @param c byte to be verified.
 * @param i position to check if the bit is 1.
 * @return 1 if bit is set or 0 otherwise.
 */
int is_bit_set(unsigned char c, int i);

/**
 * Sets the bit in the given position.
 *
 * @param c byte to be mapped.
 * @param i position to set the bit in 1.
 * @return byte with the bit in the given position set.
 */
unsigned char set_bit(unsigned char c, int i);

#endif
