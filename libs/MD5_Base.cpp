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
