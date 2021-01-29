#ifndef IP_CPP
#define IP_CPP

#include "string.h"
#include "field.h"
#include "ip.h"

    Ip::Ip(String pattern) : Field(pattern){

        this->low = 0;
        this->high = 0;
    }

    bool Ip::set_value(String val) {

        String **strings = new String*();
        size_t no_of_strings = 0;
        int mask = 0;
        char delimiters[2] = {'.','/'};

        val.split(delimiters,strings,&no_of_strings);

        for(size_t i=0 ; i<no_of_strings-1 ; i++){


            mask += (((*strings)[i].to_integer())<<(24-(8*i)));
            (*strings)[i].~String();
        }

        int mask_bits = (*strings)[no_of_strings-1].to_integer();

        (*strings)[no_of_strings-1].~String();

        this->low = ((mask>>(32-mask_bits))<<(32-mask_bits));
        
        size_t ones = 0;
        
        for(int i=0; i<(32-mask_bits);i++){
            ones = ones << 1;
            ones+=1;
        }

        this->high = ((mask)|(ones));

        return true;
    }

    bool Ip::match_value(String val) const {


        String **ip_parts = new String*();
        size_t no_of_strings;
        size_t ip_value = 0;

        val.split(".",ip_parts,&no_of_strings);
        for(size_t i=0 ; i<no_of_strings ; i++){
            ip_value += (((*ip_parts)[i].to_integer())<<(24-(8*i)));
            (*ip_parts)[i].~String();
        }

        return ((this->high >= ip_value) && (ip_value >= this->low));
    }
#endif
