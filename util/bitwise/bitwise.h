#ifndef BITWISE_H
#define BITWISE_H

/**
 * Converts a bits string to a unsigned number of 1 byte.
 *
 * @param bits string of bits with max length of 8 and terminating character.
 * @return correspondent unsigned char or 0 if input length is bigger than 8.
 */
unsigned char bits_to_byte(char *bits);

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
