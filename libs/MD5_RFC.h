#pragma once
#include "MD5_Base.h"

class MD5_RFC : public MD5_Base
{
public:
    MD5_RFC()  = default;
    ~MD5_RFC() = default;

    using MD5_Base::update;
    virtual void update(const uint8_t *buf, size_t length);
    void finalize();

private:
    void transform(const uint8_t block[BLOCK_SIZE]);
    void decode(uint32_t *output, const uint8_t *input);
    void encode(uint8_t *output, const uint32_t *input, size_t count);
    void encode(uint8_t *output, const size_t input);

    // F, G, H and I are basic MD5 functions.
    inline uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | ((~x) & z); }
    inline uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & (~z)); }
    inline uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
    inline uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | (~z)); }

    // rotate_left rotates x left n bits.
    inline uint32_t rotate_left(uint32_t x, uint32_t n) { return (x << n) | (x >> (32 - n)); }

    // FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
    // Rotation is separate from addition to prevent recomputation.
    inline void FF(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) { a = rotate_left(a + F(b, c, d) + x + ac, s) + b; }
    inline void GG(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) { a = rotate_left(a + G(b, c, d) + x + ac, s) + b; }
    inline void HH(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) { a = rotate_left(a + H(b, c, d) + x + ac, s) + b; }
    inline void II(uint32_t &a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) { a = rotate_left(a + I(b, c, d) + x + ac, s) + b; }
};
