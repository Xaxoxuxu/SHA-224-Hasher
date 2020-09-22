#pragma once
#include <sstream>
#include <iomanip>
#include <functional>

namespace sha
{
    // ch := (e and f) xor ((not e) and g)
    inline uint32_t CH(const uint32_t& x, const uint32_t& y, const uint32_t& z)
    {
        return (x & y) ^ (~x & z);
    }

    // maj := (a and b) xor (a and c) xor (b and c)
    inline uint32_t MAJ(const uint32_t& x, const uint32_t& y, const uint32_t& z)
    {
        return (x & y) ^ (x & z) ^ (y & z);
    }

    // rotate right
    inline uint32_t ROTR_32(const uint32_t& x, const uint32_t& n)
    {
        return (x >> n) | (x << (32 - n));
    }

    // rotate left
    inline uint32_t ROTL_32(const uint32_t& x, const uint32_t& n)
    {
        return (x << n) | (x >> (32 - n));
    }

    // shift right
    inline uint32_t SHR(const uint32_t& x, const uint32_t& n)
    {
        return x >> n;
    }

    // S0 := (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
    inline uint32_t S0_256(const uint32_t& x)
    {
        return ROTR_32(x, 2) ^ ROTR_32(x, 13) ^ ROTR_32(x, 22);
    }

    // S1 := (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
    inline uint32_t S1_256(const uint32_t& x)
    {
        return ROTR_32(x, 6) ^ ROTR_32(x, 11) ^ ROTR_32(x, 25);
    }

    // s0 := (w[i-15] rightrotate  7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift  3)
    inline uint32_t s0_256(const uint32_t& x)
    {
        return ROTR_32(x, 7) ^ ROTR_32(x, 18) ^ SHR(x, 3);
    }

    // s1 := (w[i- 2] rightrotate 17) xor (w[i- 2] rightrotate 19) xor (w[i- 2] rightshift 10)
    inline uint32_t s1_256(const uint32_t& x)
    {
        return ROTR_32(x, 17) ^ ROTR_32(x, 19) ^ SHR(x, 10);
    }

    // first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311
    constexpr uint32_t K_256[64]{
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
      0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
      0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
      0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
      0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
      0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
      0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
      0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
      0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
      0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

    std::string sha_224(const std::string&);
}