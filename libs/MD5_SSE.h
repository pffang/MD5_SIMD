#pragma once
#include "MD5_Base.h"

#include <emmintrin.h>

class MD5_SSE : public MD5_Base
{
public:
    MD5_SSE();

    using MD5_Base::update;
    virtual void update(const uint8_t *buf, size_t length);
    void finalize();

private:
    __m128i state[4];  // digest so far
    inline __m128i F(__m128i x, __m128i y, __m128i z) { return _mm_or_si128(_mm_and_si128((x), (y)), _mm_andnot_si128((x), (z))); }
    inline __m128i G(__m128i x, __m128i y, __m128i z) { return _mm_or_si128(_mm_and_si128((x), (z)), _mm_andnot_si128((z), (y))); }
    inline __m128i H(__m128i x, __m128i y, __m128i z) { return _mm_xor_si128((x), _mm_xor_si128((y), (z))); }
    inline __m128i I(__m128i x, __m128i y, __m128i z) { return _mm_xor_si128((y), _mm_or_si128((x), _mm_andnot_si128((z), _mm_cmpeq_epi32((z), (z))))); }

    inline __m128i rotate_left(__m128i x, uint32_t n) { return _mm_or_si128(_mm_slli_epi32(x, n), _mm_srli_epi32(x, (32 - n))); }

    inline void FF(__m128i &a, __m128i b, __m128i c, __m128i d, __m128i x, uint32_t s, __m128i ac)
    {
        a = _mm_add_epi32(a, _mm_add_epi32(_mm_add_epi32(F(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm_add_epi32(a, b);
    }
    inline void GG(__m128i &a, __m128i b, __m128i c, __m128i d, __m128i x, uint32_t s, __m128i ac)
    {
        a = _mm_add_epi32(a, _mm_add_epi32(_mm_add_epi32(G(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm_add_epi32(a, b);
    }
    inline void HH(__m128i &a, __m128i b, __m128i c, __m128i d, __m128i x, uint32_t s, __m128i ac)
    {
        a = _mm_add_epi32(a, _mm_add_epi32(_mm_add_epi32(H(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm_add_epi32(a, b);
    }
    inline void II(__m128i &a, __m128i b, __m128i c, __m128i d, __m128i x, uint32_t s, __m128i ac)
    {
        a = _mm_add_epi32(a, _mm_add_epi32(_mm_add_epi32(I(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm_add_epi32(a, b);
    }

    void transform(const uint8_t block[BLOCK_SIZE]);

    void decode(__m128i *output, const uint8_t *input, uint64_t len);
};

std::string calc_string_md5_sse(const std::string &str);
