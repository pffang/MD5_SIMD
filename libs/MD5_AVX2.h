#pragma once
#include "MD5_Base.h"

#include <immintrin.h>

class MD5_AVX2 : public MD5_Base
{
public:
    MD5_AVX2();

    using MD5_Base::update;
    virtual void update(const uint8_t *buf, size_t length);
    void finalize();

private:
    __m256i state[4];  // digest so far
    inline __m256i F(__m256i x, __m256i y, __m256i z) { return _mm256_or_si256(_mm256_and_si256(x, y), _mm256_andnot_si256(x, z)); }
    inline __m256i G(__m256i x, __m256i y, __m256i z) { return _mm256_or_si256(_mm256_and_si256(x, z), _mm256_andnot_si256(z, y)); }
    inline __m256i H(__m256i x, __m256i y, __m256i z) { return _mm256_xor_si256((x), _mm256_xor_si256((y), (z))); }
    inline __m256i I(__m256i x, __m256i y, __m256i z)
    {
        return _mm256_xor_si256((y), _mm256_or_si256((x), _mm256_andnot_si256((z), _mm256_cmpeq_epi32((z), (z)))));
    }

    inline __m256i rotate_left(__m256i x, uint32_t n) { return _mm256_or_si256(_mm256_slli_epi32((x), (n)), _mm256_srli_epi32((x), (32-(n)))); }

    inline void FF(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = _mm256_add_epi32((a), _mm256_add_epi32(_mm256_add_epi32(F((b), (c), (d)), (x)),(ac)));
        a = rotate_left(a, s);
        a = _mm256_add_epi32(a, b);
    }
    inline void GG(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = _mm256_add_epi32(a, _mm256_add_epi32(_mm256_add_epi32(G(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm256_add_epi32(a, b);
    }
    inline void HH(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = _mm256_add_epi32(a, _mm256_add_epi32(_mm256_add_epi32(H(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm256_add_epi32(a, b);
    }
    inline void II(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = _mm256_add_epi32(a, _mm256_add_epi32(_mm256_add_epi32(I(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = _mm256_add_epi32(a, b);
    }

    void transform(const uint8_t block[BLOCK_SIZE]);

    void decode(__m256i *output, const uint8_t *input, uint64_t len);
};

std::string calc_string_md5_avx2(const std::string &str);