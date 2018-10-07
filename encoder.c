#include <stdio.h>
#include <stdlib.h>

#include "rle.h"

void print_stats(size_t in, size_t out)
{
    printf("initial size: %d\n", in);
    printf("encoded size: %d\n", out);

    if (!out) return;

    printf("compression ratio: %3.2lf%\n",
        (double)out * 100 / in);
}

int main(int argc, char **argv)
{
    FILE *fin, *fout;
    size_t in_size;
    size_t encoded_size;
    char encoded_file_name[256];
    unsigned char *in_buf, *encoded_buf;
    int ret;

    if (argc < 2) {
        printf("Usage: encode input\n");
        return -1;
    }

    if (!(fin = fopen(argv[1], "r"))) {
        printf("Can't open file: %s", argv[1]);
        return -1;
    }

    fseek(fin, 0L, SEEK_END);
    in_size = ftell(fin);

    if (!in_size) {
        print_stats(0, 0);
        return 0;
    }

    in_buf = (unsigned char*)malloc(in_size);
    encoded_buf = (unsigned char*)malloc(in_size * 2);
    rewind(fin);
    fread(in_buf, in_size, 1, fin);
    fclose(fin);

    if (ret = RLE_encode(in_buf, encoded_buf, in_size, &encoded_size)) {
        printf("Error occured: %d\n", ret);
        return -1;
    }

    sprintf(encoded_file_name, "%s.rle", argv[1]);
    fout = fopen(encoded_file_name, "w");
    fwrite(encoded_buf, 1, encoded_size, fout);
    fclose(fout);

    free(in_buf);
    free(encoded_buf);

    print_stats(in_size, encoded_size);
}
