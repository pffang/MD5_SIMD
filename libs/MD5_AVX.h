#pragma once
#include "MD5_Base.h"

#include <immintrin.h>

class MD5_AVX : public MD5_Base
{
public:
    MD5_AVX();

    using MD5_Base::update;
    virtual void update(const uint8_t *buf, size_t length);
    void finalize();

private:
    __m256i state[4];  // digest so far
    inline __m256i F(__m256i x, __m256i y, __m256i z) { return _mm256_castps_si256(_mm256_or_ps(_mm256_and_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)), _mm256_andnot_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(z)))); }
    inline __m256i G(__m256i x, __m256i y, __m256i z) { return _mm256_castps_si256(_mm256_or_ps(_mm256_and_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(z)), _mm256_andnot_ps(_mm256_castsi256_ps(z), _mm256_castsi256_ps(y)))); }
    inline __m256i H(__m256i x, __m256i y, __m256i z) { return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(x), _mm256_xor_ps(_mm256_castsi256_ps(y), _mm256_castsi256_ps(z)))); }
    inline __m256i I(__m256i x, __m256i y, __m256i z)
    {
        return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(y), _mm256_or_ps(_mm256_castsi256_ps(x), _mm256_andnot_ps(_mm256_castsi256_ps(z), _mm256_cmp_ps(_mm256_castsi256_ps(z), _mm256_castsi256_ps(z), _CMP_EQ_OQ)))));
    }

#define SSE_ROTATE_LEFT(x, n) _mm_or_si128(_mm_slli_epi32((x), (n)), _mm_srli_epi32((x), (32 - (n))))

    inline __m256i rotate_left(__m256i x, uint32_t n) { return _mm256_insertf128_si256(_mm256_castsi128_si256(SSE_ROTATE_LEFT(_mm256_castsi256_si128(x), n)), SSE_ROTATE_LEFT(_mm256_extractf128_si256(x, 1), n), 1); }

#define AVX_ADD_INT(x, y) _mm256_insertf128_si256(_mm256_castsi128_si256(_mm_add_epi32(_mm256_castsi256_si128(x), _mm256_castsi256_si128(y))), _mm_add_epi32(_mm256_extractf128_si256(x, 1), _mm256_extractf128_si256(y, 1)), 1)

    inline void FF(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = AVX_ADD_INT(a, AVX_ADD_INT(AVX_ADD_INT(F(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = AVX_ADD_INT(a, b);
    }
    inline void GG(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = AVX_ADD_INT(a, AVX_ADD_INT(AVX_ADD_INT(G(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = AVX_ADD_INT(a, b);
    }
    inline void HH(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = AVX_ADD_INT(a, AVX_ADD_INT(AVX_ADD_INT(H(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = AVX_ADD_INT(a, b);
    }
    inline void II(__m256i &a, __m256i b, __m256i c, __m256i d, __m256i x, uint32_t s, __m256i ac)
    {
        a = AVX_ADD_INT(a, AVX_ADD_INT(AVX_ADD_INT(I(b, c, d), x), ac));
        a = rotate_left(a, s);
        a = AVX_ADD_INT(a, b);
    }

    void transform(const uint8_t block[BLOCK_SIZE]);

    void decode(__m256i *output, const uint8_t *input, uint64_t len);
};

std::string calc_string_md5_avx(const std::string &str);