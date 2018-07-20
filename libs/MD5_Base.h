#pragma once
#include <cstdint>
#include <cstring>
#include <iostream>

class MD5_Base
{
public:
    MD5_Base()          = default;
    virtual ~MD5_Base() = default;

    void update(const char *buf, size_t length);
    virtual void update(const uint8_t *buf, size_t length) = 0;
    std::string hexdigest() const;

protected:
    // MD5 finalization. Ends an MD5 message-digest operation, writing the
    // the message digest and zeroizing the context.
    static const uint32_t BLOCK_SIZE  = 64;
    const uint8_t padding[BLOCK_SIZE] = {
        0b10000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //
        0,          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //
        0,          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  //
        0,          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0   //
    };

    // Constants for MD5Transform routine.
    const uint32_t S11 = 7;
    const uint32_t S12 = 12;
    const uint32_t S13 = 17;
    const uint32_t S14 = 22;
    const uint32_t S21 = 5;
    const uint32_t S22 = 9;
    const uint32_t S23 = 14;
    const uint32_t S24 = 20;
    const uint32_t S31 = 4;
    const uint32_t S32 = 11;
    const uint32_t S33 = 16;
    const uint32_t S34 = 23;
    const uint32_t S41 = 6;
    const uint32_t S42 = 10;
    const uint32_t S43 = 15;
    const uint32_t S44 = 21;

    // magic initialization constants.
    const uint32_t MAGIC_NUMBER[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    const uint32_t AC[64]          = {
        //
        0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501, 0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,  //
        0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x2441453,  0xD8A1E681, 0xE7D3FBC8, 0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,  //
        0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, 0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x4881D05,  0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,  //
        0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1, 0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391   //
    };

    size_t bits_count          = 0;                                                 // counter for number of bits
    uint32_t state[4]          = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};  // digest so far
    uint8_t digest[16]         = {0};                                               // the result
    bool finalized             = false;
    uint8_t buffer[BLOCK_SIZE] = {0};  // bytes that didn't fit in last 64 byte chunk
};
