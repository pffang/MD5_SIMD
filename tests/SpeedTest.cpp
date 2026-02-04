#include "MD5_AVX.h"
#include "MD5_AVX2.h"
#include "MD5_RFC.h"
#include "MD5_SSE.h"
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/md5.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

std::string hexdigest(uint8_t digest[16])
{
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::ostringstream ssbuf;
    for (int i = 0; i < 16; i++)
        ssbuf << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (uint32_t)digest[i];

    return ssbuf.str();
}

bool md5_hash_new_api(const unsigned char *data, size_t length, uint8_t digest[16])
{
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx)
    {
        return false;
    }

    const EVP_MD *md = EVP_md5();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;

    if (EVP_DigestInit_ex(ctx, md, NULL) != 1 || EVP_DigestUpdate(ctx, data, length) != 1 || EVP_DigestFinal_ex(ctx, hash, &hash_len) != 1)
    {
        EVP_MD_CTX_free(ctx);
        return false;
    }
    EVP_MD_CTX_free(ctx);
    if (hash_len > 16)
    {
        std::cerr << "Hash over flow!" << std::endl;
    }
    std::memcpy(digest, hash, 16);

    return true;
}

int main()
{
    size_t data_size = 100 * 1024 * 1024;
    std::vector<uint8_t> data(data_size, 0x41);

    int iterations = 50;
    std::cout << "Start memory MD5 test (Data size: " << data_size / (1024 * 1024) << " MB)..." << std::endl;

    MD5_RFC md5rfc;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        md5rfc.update(data.data(), data.size());
        md5rfc.finalize();
    }
    auto end                              = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double total_gb                       = (static_cast<double>(data_size) * iterations) / (1024 * 1024 * 1024);

    std::cout << "RFC: " << md5rfc.hexdigest() << std::endl;
    std::cout << "Total Time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Throughput: " << total_gb / elapsed.count() << " GB/s" << std::endl;
    std::cout << std::endl;

    MD5_SSE md5sse;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        md5sse.update(data.data(), data.size());
        md5sse.finalize();
    }
    end      = std::chrono::high_resolution_clock::now();
    elapsed  = end - start;
    total_gb = (static_cast<double>(data_size) * iterations) / (1024 * 1024 * 1024);

    std::cout << "SSE: " << md5sse.hexdigest() << std::endl;
    std::cout << "Total Time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Throughput: " << total_gb / elapsed.count() << " GB/s" << std::endl;
    std::cout << std::endl;

    MD5_AVX md5avx;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        md5avx.update(data.data(), data.size());
        md5avx.finalize();
    }
    end      = std::chrono::high_resolution_clock::now();
    elapsed  = end - start;
    total_gb = (static_cast<double>(data_size) * iterations) / (1024 * 1024 * 1024);

    std::cout << "AVX: " << md5avx.hexdigest() << std::endl;
    std::cout << "Total Time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Throughput: " << total_gb / elapsed.count() << " GB/s" << std::endl;
    std::cout << std::endl;

    MD5_AVX2 md5avx2;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        md5avx2.update(data.data(), data.size());
        md5avx2.finalize();
    }
    end      = std::chrono::high_resolution_clock::now();
    elapsed  = end - start;
    total_gb = (static_cast<double>(data_size) * iterations) / (1024 * 1024 * 1024);

    std::cout << "AVX2: " << md5avx2.hexdigest() << std::endl;
    std::cout << "Total Time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Throughput: " << total_gb / elapsed.count() << " GB/s" << std::endl;
    std::cout << std::endl;

    unsigned char digest[MD5_DIGEST_LENGTH];
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        MD5(data.data(), data.size(), digest);
    }
    end      = std::chrono::high_resolution_clock::now();
    elapsed  = end - start;
    total_gb = (static_cast<double>(data_size) * iterations) / (1024 * 1024 * 1024);

    std::cout << "OpenSSL Legacy MD5: " << hexdigest(digest) << std::endl;
    std::cout << "Total Time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Throughput: " << total_gb / elapsed.count() << " GB/s" << std::endl;
    std::cout << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i)
    {
        md5_hash_new_api(data.data(), data.size(), digest);
    }
    end      = std::chrono::high_resolution_clock::now();
    elapsed  = end - start;
    total_gb = (static_cast<double>(data_size) * iterations) / (1024 * 1024 * 1024);

    std::cout << "OpenSSL EVP: " << hexdigest(digest) << std::endl;
    std::cout << "Total Time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Throughput: " << total_gb / elapsed.count() << " GB/s" << std::endl;
    std::cout << std::endl;

    return 0;
}
