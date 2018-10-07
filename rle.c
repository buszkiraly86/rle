#include <string.h>

int RLE_encode(unsigned char* in_buf, unsigned char* out_buf, size_t in_size, size_t* out_size)
{
    if (!in_size) {
        out_size = 0;
        return 0;
    }

    unsigned char *pout = out_buf;
    unsigned char seq_start = *in_buf;
    unsigned char seq_length = 1;

    for (size_t i = 1; i < in_size; ++i) {
        if (seq_start != *(in_buf + i) || seq_length == 255) {
            *pout++ = seq_length;
            *pout++ = seq_start;

            seq_length = 1;
            seq_start = *(in_buf + i);
        } else {
            ++seq_length;
        }
    }

    *pout++ = seq_length;
    *pout++ = seq_start;

    *out_size = pout - out_buf;

    return 0;
}

int RLE_decode(unsigned char* in_buf, unsigned char* out_buf, size_t in_size)
{
    unsigned char *pout = out_buf;
    for (size_t i = 0; i < in_size / 2; ++i) {
        unsigned char seq_length = in_buf[2 * i];
        unsigned char ch = in_buf[2 * i + 1];
        for (unsigned char n = 0; n < seq_length; ++n) {
            *pout++ = ch;
        }
    }

    return 0;
}
