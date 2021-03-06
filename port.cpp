#ifndef PORT_CPP
#define PORT_CPP

#include "string.h"
#include "field.h"
#include "port.h"

    Port::Port(String pattern) : Field(pattern){
      this->range[2] = {0};
    }

    bool Port::set_value(String val) {
        String **strings = new String*();
        size_t no_of_strings = 0;
        char delimiters[1] = {'-'};
        val.split(delimiters,strings,&no_of_strings);
        for(size_t i=0 ; i < no_of_strings ; i++){
            this->range[i] = (*strings)[i].to_integer();
            (*strings)[i].~String();
        }
        return true;
    }

    bool Port::match_value(String val) const {
        //std::cout << "Port match value started" << std::endl;
        return ((this->range[1] >= val.to_integer()) && (val.to_integer() >= this->range[0]));
    }

#endif
