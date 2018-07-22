#include "MD5_Base.h"
#include <iomanip>  // std::setfill, std::setw
#include <locale>
#include <sstream>

// for convenience provide a verson with signed char
void MD5_Base::update(const char *buf, size_t length)
{
    update((const uint8_t *)buf, length);
}

// return hex representation of digest as string
std::string MD5_Base::hexdigest() const
{
    if (!finalized)
        return "";

    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::ostringstream ssbuf;
    for (int i = 0; i < 16; i++)
        ssbuf << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (uint32_t)digest[i];

    return ssbuf.str();
}

void MD5_Base::encode(uint8_t *output, const uint32_t *input, size_t count)
{
    for (size_t i = 0, j = 0; i < count; i++, j += 4)
    {
        for (uint32_t k = 0; k < 4; k++)
        {
            output[j + k] = (input[i] >> (k << 3)) & 0xFF;
        }
    }
}

void MD5_Base::encode(uint8_t *output, const uint32_t input)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        output[i] = (input >> (i << 3)) & 0xFF;
    }
}

void MD5_Base::encode(uint8_t *output, const uint64_t input)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        output[i] = (input >> (i << 3)) & 0xFF;
    }
}