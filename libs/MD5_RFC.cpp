#include "MD5_RFC.h"

// decodes input (unsigned char) into output (uint32_t). BLOCK_SIZE
void MD5_RFC::decode(uint32_t *output, const uint8_t *input)
{
    for (size_t i = 0, j = 0; j < BLOCK_SIZE; i++, j += 4)
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) | (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
}

// apply MD5 algo on a block
void MD5_RFC::transform(const uint8_t block[BLOCK_SIZE])
{
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16] = {0};
    decode(x, block);

    /* Round 1 */
    FF(a, b, c, d, x[0], S11, AC[0]);   /* 1 */
    FF(d, a, b, c, x[1], S12, AC[1]);   /* 2 */
    FF(c, d, a, b, x[2], S13, AC[2]);   /* 3 */
    FF(b, c, d, a, x[3], S14, AC[3]);   /* 4 */
    FF(a, b, c, d, x[4], S11, AC[4]);   /* 5 */
    FF(d, a, b, c, x[5], S12, AC[5]);   /* 6 */
    FF(c, d, a, b, x[6], S13, AC[6]);   /* 7 */
    FF(b, c, d, a, x[7], S14, AC[7]);   /* 8 */
    FF(a, b, c, d, x[8], S11, AC[8]);   /* 9 */
    FF(d, a, b, c, x[9], S12, AC[9]);   /* 10 */
    FF(c, d, a, b, x[10], S13, AC[10]); /* 11 */
    FF(b, c, d, a, x[11], S14, AC[11]); /* 12 */
    FF(a, b, c, d, x[12], S11, AC[12]); /* 13 */
    FF(d, a, b, c, x[13], S12, AC[13]); /* 14 */
    FF(c, d, a, b, x[14], S13, AC[14]); /* 15 */
    FF(b, c, d, a, x[15], S14, AC[15]); /* 16 */

    /* Round 2 */
    GG(a, b, c, d, x[1], S21, AC[16]);  /* 17 */
    GG(d, a, b, c, x[6], S22, AC[17]);  /* 18 */
    GG(c, d, a, b, x[11], S23, AC[18]); /* 19 */
    GG(b, c, d, a, x[0], S24, AC[19]);  /* 20 */
    GG(a, b, c, d, x[5], S21, AC[20]);  /* 21 */
    GG(d, a, b, c, x[10], S22, AC[21]); /* 22 */
    GG(c, d, a, b, x[15], S23, AC[22]); /* 23 */
    GG(b, c, d, a, x[4], S24, AC[23]);  /* 24 */
    GG(a, b, c, d, x[9], S21, AC[24]);  /* 25 */
    GG(d, a, b, c, x[14], S22, AC[25]); /* 26 */
    GG(c, d, a, b, x[3], S23, AC[26]);  /* 27 */
    GG(b, c, d, a, x[8], S24, AC[27]);  /* 28 */
    GG(a, b, c, d, x[13], S21, AC[28]); /* 29 */
    GG(d, a, b, c, x[2], S22, AC[29]);  /* 30 */
    GG(c, d, a, b, x[7], S23, AC[30]);  /* 31 */
    GG(b, c, d, a, x[12], S24, AC[31]); /* 32 */

    /* Round 3 */
    HH(a, b, c, d, x[5], S31, AC[32]);  /* 33 */
    HH(d, a, b, c, x[8], S32, AC[33]);  /* 34 */
    HH(c, d, a, b, x[11], S33, AC[34]); /* 35 */
    HH(b, c, d, a, x[14], S34, AC[35]); /* 36 */
    HH(a, b, c, d, x[1], S31, AC[36]);  /* 37 */
    HH(d, a, b, c, x[4], S32, AC[37]);  /* 38 */
    HH(c, d, a, b, x[7], S33, AC[38]);  /* 39 */
    HH(b, c, d, a, x[10], S34, AC[39]); /* 40 */
    HH(a, b, c, d, x[13], S31, AC[40]); /* 41 */
    HH(d, a, b, c, x[0], S32, AC[41]);  /* 42 */
    HH(c, d, a, b, x[3], S33, AC[42]);  /* 43 */
    HH(b, c, d, a, x[6], S34, AC[43]);  /* 44 */
    HH(a, b, c, d, x[9], S31, AC[44]);  /* 45 */
    HH(d, a, b, c, x[12], S32, AC[45]); /* 46 */
    HH(c, d, a, b, x[15], S33, AC[46]); /* 47 */
    HH(b, c, d, a, x[2], S34, AC[47]);  /* 48 */

    /* Round 4 */
    II(a, b, c, d, x[0], S41, AC[48]);  /* 49 */
    II(d, a, b, c, x[7], S42, AC[49]);  /* 50 */
    II(c, d, a, b, x[14], S43, AC[50]); /* 51 */
    II(b, c, d, a, x[5], S44, AC[51]);  /* 52 */
    II(a, b, c, d, x[12], S41, AC[52]); /* 53 */
    II(d, a, b, c, x[3], S42, AC[53]);  /* 54 */
    II(c, d, a, b, x[10], S43, AC[54]); /* 55 */
    II(b, c, d, a, x[1], S44, AC[55]);  /* 56 */
    II(a, b, c, d, x[8], S41, AC[56]);  /* 57 */
    II(d, a, b, c, x[15], S42, AC[57]); /* 58 */
    II(c, d, a, b, x[6], S43, AC[58]);  /* 59 */
    II(b, c, d, a, x[13], S44, AC[59]); /* 60 */
    II(a, b, c, d, x[4], S41, AC[60]);  /* 61 */
    II(d, a, b, c, x[11], S42, AC[61]); /* 62 */
    II(c, d, a, b, x[2], S43, AC[62]);  /* 63 */
    II(b, c, d, a, x[9], S44, AC[63]);  /* 64 */

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5_RFC::update(const uint8_t *buf, size_t length)
{
    size_t index = 0;

    index = bits_count / 8 % BLOCK_SIZE;
    bits_count += length * 8;

    // number of bytes we need to fill in buffer
    size_t firstpart = BLOCK_SIZE - index;

    size_t i;

    // transform as many times as possible.
    if (length >= firstpart)
    {
        // fill buffer first, transform
        std::memcpy(&buffer[index], buf, firstpart);
        transform(buffer);

        // transform chunks of blocksize (64 bytes)
        for (i = firstpart; i + BLOCK_SIZE <= length; i += BLOCK_SIZE)
            transform(&buf[i]);

        index = 0;
    }
    else
        i = 0;

    // buffer remaining input
    std::memcpy(&buffer[index], &buf[i], length - i);
}

void MD5_RFC::finalize()
{

    if (!finalized)
    {
        size_t index = 0;
        // Save number of bits
        uint8_t bits[8];

        encode(bits, bits_count);
        index = bits_count / 8 % BLOCK_SIZE;

        size_t padLen = (index < 56) ? (56 - index) : (120 - index);
        update(padding, padLen);

        // Append length (before padding)
        update(bits, 8);

        // Store state in digest
        encode(digest, state, 4);

        // Zeroize sensitive information.
        std::memset(buffer, 0, sizeof(buffer));
        bits_count = 0;
        finalized  = true;
    }
}
