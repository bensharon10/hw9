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
    size_t no_of_strings = 0;

    //std::cout << "created string is:" << argv [1] << std::endl;

    String rule = String(argv[1]);
    //std::cout << "main gets string: "<< rule.equals("whatever") << std::endl;
    //rule = rule.trim();
    /**
     * Separating rule type and rule parameters
     */

    //std::cout << "main after initial trim: "<< rule.equals("whatever") << std::endl;

    rule.split(delimiters, strings, &no_of_strings);
    for(size_t i = 0 ; i < no_of_strings ; i++){
        (*strings)[i] = (*strings)[i].trim();
    }
    /**
     * Create rule object
     */
    Field *field;

    if (strings[0]->equals("src-ip") || strings[0]->equals("dst-ip")){
        field = new Ip(*strings[0]);
    } else {
        field = new Port(*strings[0]);
    }
    
    //std::cout << "main go to set_value with string: "<< (*strings)[1].equals("whatever") << std::endl;

    field->set_value((*strings)[1]);
    //printf("!!!!!!!!!!!!!!2\n");

    parse_input(*field);

    return 0;
}

#endif

