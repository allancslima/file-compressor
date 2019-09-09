COMPRESSOR = compression/compressor.c
DECOMPRESSOR = compression/decompressor.c
HUFFMAN = compression/huffman.c

HASHTABLE = util/hashtable/hashtable.c
PRIORITY_QUEUE = util/queue/priority_queue.c
QUEUE = util/queue/queue.c
BINARY_TREE = util/tree/binary_tree.c

BITWISE = util/bitwise/bitwise.c

file_compressor:
	mkdir -p output/
	gcc main.c -o file-compressor.out $(COMPRESSOR) $(DECOMPRESSOR) $(HUFFMAN) $(HASHTABLE) $(PRIORITY_QUEUE) $(QUEUE) $(BINARY_TREE) $(BITWISE)

tests:
	mkdir -p output/
	gcc unit_tests/hashtable/hashtable_tests.c -o output/hashtable_tests.out $(HASHTABLE) -lcunit
	gcc unit_tests/queue/priority_queue_tests.c -o output/priority_queue_tests.out $(PRIORITY_QUEUE) $(QUEUE) -lcunit
	gcc unit_tests/tree/binary_tree_tests.c -o output/binary_tree_tests.out $(BINARY_TREE) -lcunit
