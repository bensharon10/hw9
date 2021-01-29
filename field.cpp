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
        //std::cout << "a new field object of type " << type << std::endl;
    }

    Field::~Field() {
       pattern.~String();
    }

    field_type Field::get_type() const{
        return this->type;
    }

    bool Field::set_value(String val){
        val = val.trim();
        
        //std::cout << "set value field go to split with string: "<< val.equals("whatever") << std::endl;

        //std::cout << "set value Field " << std::endl;
        if (this->get_type()==IP){
            //std::cout << "set value Ip chosen " << std::endl;
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
        //std::cout << "field match started" << std::endl;

        size_t no_of_fields = 0;
        String **fields = new String*();
        char delimiters[2] = {',','='};

        //std::cout << "field match go to split with string: "<< packet.equals("whatever") << std::endl;

        packet.split(delimiters,fields,&no_of_fields);
        
        //std::cout << "field match return from split" << std::endl;
        for (size_t i = 0 ; i < no_of_fields ; i++){
            (*fields)[i] = (*fields)[i].trim();
            if((this->pattern).equals((*fields)[i])){
                if(this->match_value((*fields)[i+1])){
                    //std::cout << "the field is a match start delete loop" << std::endl;
                    for(size_t j = i;j < no_of_fields;j++){
                        (*fields)[j].~String();
                    }
                    return true;
                }
            } else {
                //std::cout << "the field is NOT a match start delete loop" << std::endl;
                (*fields)[i].~String();
            }
        }
        return false;
    }

#endif
