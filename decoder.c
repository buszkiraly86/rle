#include <stdio.h>
#include <stdlib.h>

#include "rle.h"

int main(int argc, char **argv)
{
    FILE *fin, *fout; 
    size_t in_size;
    size_t decoded_size = 0;
    unsigned char *in_buf, *decoded_buf;
    int ret;

    if (argc <3) {
        printf("Usage: decode input output\n");
        return -1;
    }

    if (!(fin = fopen(argv[1], "r"))) {
        printf("Can't open file: %s", argv[1]);
        return -1;
    }

    fseek(fin, 0L, SEEK_END);
    in_size = ftell(fin);
    rewind(fin);

    in_buf = (unsigned char*)malloc(in_size);
    fread(in_buf, in_size, 1, fin);
    fclose(fin);

    if (!in_size) return 0;

    for (size_t i = 0; i < in_size; i += 2) {
        decoded_size += in_buf[i]; 
    }
    decoded_buf = (unsigned char*)malloc(decoded_size);

    if (ret = RLE_decode(in_buf, decoded_buf, in_size)) {
        printf("Error occured: %d\n", ret);
        return -1;
    }

    if (!(fout = fopen(argv[2], "w"))) {
        printf("Can't open file: %s", argv[2]);
        return -1;
    }
    fwrite(decoded_buf, 1, decoded_size, fout);
    fclose(fout);

    free(in_buf);
    free(decoded_buf);
}
