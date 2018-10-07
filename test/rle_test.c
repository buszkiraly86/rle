#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../rle.h"

int main()
{
    FILE *f;
    size_t in_size;
    size_t encoded_size;
    const size_t expected_size = 26;
    unsigned char *in_buf, *encoded_buf, *decoded_buf;
    int ret;

    f = fopen("test.txt", "r");
    fseek(f, 0L, SEEK_END);
    in_size = ftell(f);
    rewind(f);
    in_buf = (unsigned char*)malloc(in_size);
    fread(in_buf, in_size, 1, f);

    encoded_buf = (unsigned char*)malloc(in_size * 2);
    decoded_buf = (unsigned char*)malloc(in_size);

    // encode it
    if (ret = RLE_encode(in_buf, encoded_buf, in_size, &encoded_size)) {
        printf("Error occured: %d\n", ret);
        return -1;
    }

    // check the size
    if (expected_size != encoded_size) {
        printf("Expected size and returned size differ. Expected %d, returned %d\n",
            expected_size, encoded_size);
        return -1;
    }

    // decode it
    if (ret = RLE_decode(encoded_buf, decoded_buf, encoded_size)) {
        printf("Error occured: %d\n", ret);
        return -1;
    }

    // compare with the original data
    if (memcmp(in_buf, decoded_buf, in_size)) {
        printf("Decoded and original don't match\n");
        return -1;
    }

    free(in_buf);
    free(encoded_buf);
    free(decoded_buf);
}

