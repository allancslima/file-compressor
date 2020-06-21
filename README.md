# File compressor

This file compressor is based on the Huffman's coding algorithm, built with the following data structures:

* Hash Table
* Priority Queue
* Binary Tree

## Compile

`make file-compressor`

Compiled at `/output`.

## Compress

To compress a file:

`./file-compressor.out compress -i input_file -o output_file`

## Decompress

To decompress a compressed file:

`./file-compressor.out decompress -i input_file -o output_file`

## Unit tests

This project contains unit tests for the data structures only.

First, compile the tests:

`make tests`

They are compiled separately by data structure at `/output`.

Then run a test like:

`./output/binary_tree_tests.out`
