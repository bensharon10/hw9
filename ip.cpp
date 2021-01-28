#ifndef IP_CPP
#define IP_CPP

#include "string.h"
#include "field.h"
#include "ip.h"

#define FULL_ONES (2^32)-1

    Ip::Ip(String pattern) : Field(pattern){
        this->low = 0;
        this->high = 0;
    }

    bool Ip::set_value(String val) {
        String *strings[5];
        size_t *no_of_strings;
        int mask = 0;
        char delimiters[2] = {'.','/'};
        val.split(delimiters,strings,no_of_strings);
        for(int i=0 ; i<*no_of_strings-1 ; i++){
            mask += ((strings[i]->to_integer())<<(24-8*i));
            strings[i]->~String();
        }

        int mask_bits = strings[*no_of_strings]->to_integer();
        strings[*no_of_strings]->~String();
        this->low = ((mask>>mask_bits)<<mask_bits);
        this->high = (this->low)|(FULL_ONES);
        return true;
    }

    bool Ip::match_value(String val) const {
        return ((this->high - val.to_integer()) < this->low);
    }
#endif
