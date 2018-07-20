#pragma once
#include <iostream>

class MD5
{
public:
    MD5();
    ~MD5();

    void update(const uint8_t *buf, size_t length);
    void update(const char *buf, size_t length);
    void finalize();
    std::string hexdigest() const;
    friend std::ostream &operator<<(std::ostream &, MD5 md5);
};
