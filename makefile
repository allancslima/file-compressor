COMPRESSOR = compression/compressor.c
DECOMPRESSOR = compression/decompressor.c
HUFFMAN = compression/huffman.c

HASHTABLE = util/hashtable/hashtable.c
PRIORITY_QUEUE = util/queue/priority_queue.c
QUEUE = util/queue/queue.c
BINARY_TREE = util/tree/binary_tree.c

BITWISE = util/bitwise/bitwise.c

compile_tree:
	gcc main.c -o file-compressor.out $(COMPRESSOR) $(DECOMPRESSOR) $(HUFFMAN) $(HASHTABLE) $(PRIORITY_QUEUE) $(QUEUE) $(BINARY_TREE) $(BITWISE)
