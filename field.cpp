#ifndef FIELD_CPP
#define FIELD_CPP

#include "field.h"
#include "ip.h"
#include "port.h"


    Field::Field(String pattern){

        this->pattern = pattern;
        if (pattern.equals("src-ip") || pattern.equals("dst-ip")){
            this->type = IP;
        } else {
            this->type = PORT;
        }
    }

    Field::~Field() {
        
        pattern.~String();
        
        if (this->get_type()==IP){
            ((Ip*) (this))->~Ip();
        } else {
            ((Port*) (this))->~Port();
        }       
    }

    field_type Field::get_type() const{

        return this->type;
    }

    bool Field::set_value(String val){

        val = val.trim();
        
        if (this->get_type()==IP){
            return  ((Ip*) (this))->set_value(val);
        } else {
            return ((Port*) (this))->set_value(val);
        }
    }

    bool Field::match_value(String val) const{

        val = val.trim();
        if (this->get_type()==IP){
            return ((Ip*) (this))->match_value(val);
        } else {
            return ((Port*) (this))->match_value(val);
        }
    }

    bool Field::match(String packet){

        size_t no_of_fields = 0;
        String **fields = new String*();
        char delimiters[2] = {',','='};


        packet.split(delimiters,fields,&no_of_fields);
        
        for (size_t i = 0 ; i < no_of_fields ; i++){
            (*fields)[i] = (*fields)[i].trim();
            if((this->pattern).equals((*fields)[i])){
                if(this->match_value((*fields)[i+1])){
                    for(size_t j = i;j < no_of_fields;j++){
                        (*fields)[j].~String();
                    }
                    return true;
                }
            } else {
                (*fields)[i].~String();
            }
        }
        return false;
    }

#endif
