all: encode decode test/rle_test

encode: rle.c rle.h encoder.c
	gcc -std=c99 rle.c encoder.c -o encode

decode: rle.c rle.h decoder.c
	gcc -std=c99 rle.c decoder.c -o decode

test/rle_test: rle.c rle.h test/rle_test.c
	gcc -std=c99 -g rle.c test/rle_test.c -o test/rle_test

clean:
	rm -f encode decode test/rle_test

.PHONY: all clean
