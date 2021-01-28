#ifndef MAIN_CPP
#define MAIN_CPP

#include "field.h"
#include "input.h"
#include "ip.h"
#include "port.h"

#define NO_OF_DELIMITERS 2

int main (int argc, char **argv)  {

    if(check_args(argc, argv)){
        return 1;
    }
    printf("!!!!!!!!!!!!!!2\n");

    char delimiters [NO_OF_DELIMITERS] = {'=','-'};
    String **strings = new String*();
    size_t no_of_strings = 0;
    printf("!!!!!!!!!!!!!!3\n");

    String rule = String(*argv);
    rule = rule.trim();
    /**
     * Separating rule type and rule parameters
     */
    rule.split(delimiters, strings, &no_of_strings);
    /**
     * Create rule object
     */
    Field *field;
    printf("!!!!!!!!!!!!!!4\n");

    if (strings[0]->equals("src-ip") || strings[0]->equals("dst-ip")){
        field = new Ip(*strings[0]);
    } else {
        field = new Port(*strings[0]);
    }

    field->set_value(*strings[1]);

    parse_input(*field);

    return 0;
}

#endif

