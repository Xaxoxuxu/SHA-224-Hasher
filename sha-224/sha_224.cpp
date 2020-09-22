#include "sha_224.h"

namespace sha
{
    using std::string;

    /**
     * Padding
     */
    string pre_processing(const string& msg)
    {
        std::stringstream ss;

        // l + 1 + k ≡ 448 mod 512 (1 -> 1000 0000(bin) = 80(hex) -> 8 bit)
        const uint32_t l{ 8 * static_cast<uint32_t>(msg.length()) };
        const uint32_t k{ (448 - (8 + l)) % 512 };

        for (size_t i{}; i < msg.length(); ++i)
        {
            ss << std::setw(2) << std::setfill('0') << std::hex << static_cast<uint32_t>(msg[i]);
        }
        // append bit "1" (1 -> 1000 0000(bin) = 80(hex) -> 8 bit), fill with zeroes and append message length
        ss << "80" << std::setw(static_cast<std::streamsize>(16) + k / 4) << std::setfill('0') << std::hex << l;

        return ss.str();
    }

    string hash_computation(const string& msg)
    {
        // working variables
        uint32_t a, b, c, d, e, f, g, h, temp1, temp2;
        // The initial values in w[0..63] don't matter, so many implementations zero them here
        uint32_t w[64]{ 0 };
        // SHA-224 initial hash values (in big endian):
        // (The second 32 bits of the fractional parts of the square roots of the 9th through 16th primes 23..53)
        uint32_t H[8]{
          0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
          0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
        };

        for (size_t i{}, j{}; i < msg.length(); i += 8, ++j)
        {
            // cast result to uint32_t since std::stoul() returns unsigned long which is MINIMUM 32bits, we need it to be 32bits
            w[j] = static_cast<uint32_t>(std::stoul(msg.substr(i, 8), nullptr, 16));

            if (j == 15)
            {
                for (j = 16; j < 64; ++j)
                {
                    w[j] = s1_256(w[j - 2]) + w[j - 7] + s0_256(w[j - 15]) + w[j - 16];
                }
                j = -1;

                a = H[0];
                b = H[1];
                c = H[2];
                d = H[3];
                e = H[4];
                f = H[5];
                g = H[6];
                h = H[7];

                for (size_t t{}; t < 64; ++t)
                {
                    temp1 = h + S1_256(e) + CH(e, f, g) + K_256[t] + w[t];
                    temp2 = S0_256(a) + MAJ(a, b, c);
                    h = g;
                    g = f;
                    f = e;
                    e = d + temp1;
                    d = c;
                    c = b;
                    b = a;
                    a = temp1 + temp2;
                }

                H[0] += a;
                H[1] += b;
                H[2] += c;
                H[3] += d;
                H[4] += e;
                H[5] += f;
                H[6] += g;
                H[7] += h;
            }
        }

        // Produce the final hash value (big-endian)
        std::stringstream ss;
        for (size_t i{}; i < 7; ++i)
        {
            ss << std::setw(8) << std::setfill('0') << std::hex << H[i];
        }

        // final digest
        return ss.str();
    }

    string sha_224(const string& msg)
    {
        const string processedMsg{ pre_processing(msg) };
        return hash_computation(processedMsg);
    }
}