#ifndef MAIN_CPP
#define MAIN_CPP

#include "field.h"
#include "input.h"
#include "ip.h"
#include "port.h"

#define NO_OF_DELIMITERS 2

int main (int argc, char **argv)  {

    //if(check_args(argc, argv)){
  //      return 1;
//    }

    char delimiters [NO_OF_DELIMITERS] = {'=','-'};
    String **strings = new String*();
    size_t no_of_strings = 0;

    String rule = String(argv[1]);
    rule = rule.trim();
    /**
     * Separating rule type and rule parameters
     */
    rule.split(delimiters, strings, &no_of_strings);
    /**
     * Create rule object
     */
    Field *field;

    if (strings[0]->equals("src-ip") || strings[0]->equals("dst-ip")){
        field = new Ip(*strings[0]);
    } else {
        field = new Port(*strings[0]);
    }
    printf("!!!!!!!!!!!!!!1\n");
    field->set_value(*strings[1]);
    printf("!!!!!!!!!!!!!!2\n");

    parse_input(*field);

    return 0;
}

#endif

