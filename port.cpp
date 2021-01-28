#ifndef PORT_CPP
#define PORT_CPP

#include "string.h"
#include "field.h"
#include "port.h"

    Port::Port(String pattern) : Field(pattern){
      this->range[2] = {0};
    }

    bool Port::set_value(String val) {
        String *strings[2];
        size_t *no_of_strings;
        char delimiters[1] = {'-'};
        val.split(delimiters,strings,no_of_strings);
        for(int i=0 ; i<*no_of_strings ; i++){
            this->range[i] = strings[i]->to_integer();
            strings[i]->~String();
        }
        return true;
    }

    /*
    bool Port::match_value(String val) const {
        int being_checked = val.to_integer();
        if(being_checked>=this->range[0] && being_checked<=this->range[1]) {
            return true;
        } else {
            return false;
        }
    }

     */

    bool Port::match_value(String val) const {
        return ((this->range[1]-val.to_integer())<this->range[0]);
    }

#endif
