#ifndef MAIN_CPP
#define MAIN_CPP

#include "field.h"
#include "input.h"
#include "ip.h"
#include "port.h"

#define NO_OF_DELIMITERS 1

int main (int argc, char **argv)  {

    if(check_args(argc, argv)){
        return 1;
    }

    char delimiters [NO_OF_DELIMITERS] = {'='};
    String **strings = new String*();
    size_t no_of_strings = 1;

    String rule = String(argv[1]);

    /**
     * Separating rule type and rule parameters.
     */

    rule.split(delimiters, strings, &no_of_strings);
    for(size_t i = 0 ; i < no_of_strings ; i++){
        (*strings)[i] = (*strings)[i].trim();
    }

    /**
     * Create rule object.
     */

    Field *field;

    if (strings[0]->equals("src-ip") || strings[0]->equals("dst-ip")){
        field = new Ip(*strings[0]);
    } else {
        field = new Port(*strings[0]);
    }
    
    field->set_value((*strings)[1]);
    
    (*strings)[0].~String();
    (*strings)[1].~String();

    parse_input(*field);

    field->~Field();


    return 0;
}

#endif

