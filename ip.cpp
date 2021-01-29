#ifndef IP_CPP
#define IP_CPP

#include "string.h"
#include "field.h"
#include "ip.h"

#define FULL_ONES (2^32)-1

    Ip::Ip(String pattern) : Field(pattern){
        this->low = 0;
        this->high = 0;
        //std::cout << "new Ip object" << std::endl;
    }

    bool Ip::set_value(String val) {
        //std::cout << "set value Ip started " << std::endl;
        String **strings = new String*();
        size_t no_of_strings = 0;
        int mask = 0;
        char delimiters[2] = {'.','/'};
        val.split(delimiters,strings,&no_of_strings);
        for(size_t i=0 ; i<no_of_strings-1 ; i++){
            //std::cout << strings[i] << std::endl;
            mask += (((*strings)[i].to_integer())<<(24-(8*i)));
            //std::cout << mask << std::endl;
            (*strings)[i].~String();
        }

        std::cout << mask << std::endl;

        int mask_bits = (*strings)[no_of_strings-1].to_integer();
        (*strings)[no_of_strings].~String();
        this->low = ((mask>>mask_bits)<<mask_bits);
        
        size_t ones = 0;
        
        for(int i=0; i<(32-mask_bits);i++){
            ones = ones << 1;
            ones+=1;
        }

        this->high = ((mask)|(ones));

        std::cout << "low is - " << low << " high is -  " << high << std::endl;

        return true;
    }

    bool Ip::match_value(String val) const {
        //std::cout << "ip match value started" << std::endl;

        String **ip_parts = new String*();
        size_t no_of_strings;
        size_t ip_value = 0;

        val.split(".",ip_parts,&no_of_strings);
        for(size_t i=0 ; i<no_of_strings ; i++){
            //std::cout << (*ip_parts)[i] << std::endl;
            ip_value += (((*ip_parts)[i].to_integer())<<(24-(8*i)));
            (*ip_parts)[i].~String();
        }

        std::cout << "ready to leave ip match value, ip value is: " << ip_value << std::endl;
        return ((this->high >= ip_value) && (ip_value >= this->low));
    }
#endif
