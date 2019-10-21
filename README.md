# File compressor

This file compressor is based on the Huffman's coding algorithm and was built with the follow data structures:

* Hash Table
* Priority Queue
* Binary Tree

## Compile

`make file-compressor`

The program is compiled at `/output`.

## Compress

To compress a file:

`./file-compressor.out compress -i input_file -o output_file`

## Decompress

To decompress a compressed file:

`./file-compressor.out decompress -i input_file -o output_file`

## Unit tests

First, compile the tests:

`make tests`

The tests are compiled separately by data structure at `/output`.

Then run the tests of a data structure like:

`./output/binary_tree_tests.out`

