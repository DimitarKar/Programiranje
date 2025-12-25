#include <cstdint>
#include <cstring>
#include <algorithm>

// sizeof(void*) - kolku bajti ima edna memoriska adresa (pokazuvac) na sistem (32-bit ili 64-bit)

class GermanString{
public:
    uint32_t len;

    char prefix[4];

    union Data{
        const char* ptr;
        char suffix[sizeof(void*)];
    } data;

    GermanString(const char* input_str, uint32_t length) {
        len = length;

        uint32_t kolkMoze = 4 + sizeof(void*);

        if(len <= kolkMoze) {
            std::memset(prefix, 0, 4); 
            std::memcpy(prefix, input_str, std::min(len, (uint32_t)4));

            if(len > 4) {
                std::memcpy(data.suffix, input_str + 4, len - 4);
            }
        } 
        else{
            std::memcpy(prefix, input_str, 4);

            data.ptr = input_str; 
        }
    }
};
