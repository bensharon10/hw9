#ifndef FIELD_CPP
#define FIELD_CPP

#include "field.h"
#include "ip.h"
#include "port.h"
//#include <field>


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
    }

    field_type Field::get_type() const{
        return this->type;
    }

    bool Field::set_value(String val){
        if (this->get_type()==IP){
            return  ((Ip*) (this))->set_value(val);
        } else {
            return ((Port*) (this))->set_value(val);
        }
    }

    bool Field::match_value(String val) const{
        if (this->get_type()==IP){
            return ((Ip*) (this))->match_value(val);
        } else {
            return ((Port*) (this))->match_value(val);
        }
    }

    bool Field::match(String packet){
        size_t *no_of_fields;
        String *fields[4];
        char delimiters[2] = {',','='};
        packet.split(delimiters,fields,no_of_fields);
        for (int i=0 ; i<*no_of_fields ; i++){
            if((this->pattern).equals(*fields[i])){
                if(this->match_value(*fields[i+1])){
                    for(int j=i;j<*no_of_fields;j++){
                        fields[j]->~String();
                    }
                    return true;
                }
            } else {
                fields[i]->~String();
            }
        }
        return false;
    }

#endif