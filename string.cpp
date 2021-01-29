#ifndef STRING_CPP
#define STRING_CPP

#include "string.h"
#include <string.h>

#define STRING_END "\0"

String::String(){

    data = new char[1];
    strncpy(data,STRING_END,1);
    length = 0;
}
String::String(const String &str){

    length = str.length;
    data = new char[length+1];
    strcpy(data, str.data);
};

String::String(const char *str){

    length = strlen(str);
    data = new char[length+1];
    strcpy(data, str);
}

String::~String(){

    delete data;
}

String& String::operator=(const String &rhs){

    this->length = rhs.length;
    delete data;
    this->data = new char[strlen(rhs.data)+1];
    strcpy(this->data, rhs.data);

    return *this;
}

String& String::operator=(const char *str){

    this->length = strlen(str);
    delete data;
    this->data = new char[strlen(str)+1];
    strcpy(this->data, str);

    return *this;
}

bool String::equals(const String &rhs) const{

    return (!strcmp(this->data, rhs.data));
}

bool String::equals(const char *rhs) const{

    return (!strcmp(this->data, rhs));
}


void String::split(const char *delimiters, String **output, size_t *size) const{

    size_t no_of_strings = 1;
    size_t no_of_delimiters = strlen(delimiters);
    size_t l_pntr = 0;
    size_t r_pntr = 0;

    int out_is_null = 0;
    int string_size = 0;
    int delim_found = 0;

    /**
     * Check inputs for NULL
     */

    if(delimiters == NULL){
        std::cerr << "No delimiters!" << std::endl;
        return;
    }

    if(NULL == output){
        out_is_null = 1;
    } else {
        *output = new String[((this->length)/sizeof(short))+1];
    }

    /**
     * Go over str looking for delims. when found, mark and adjust pointers.
     * When next delim is found snip the str and store it.
     */

    while(strncmp(&data[r_pntr],STRING_END,1) != 0){
        delim_found = 0;
        for(size_t delim = 0; delim < no_of_delimiters; delim++){

            if(data[r_pntr] == delimiters[delim]){

                delim_found = 1;

                if(l_pntr == r_pntr){

                    l_pntr++;
                    r_pntr++;
                    break;

                }

                no_of_strings++;

                if(out_is_null == 1){

                    r_pntr++;
                    l_pntr = r_pntr;
                    break;
                }

                string_size = r_pntr - l_pntr;
                char *tmp_str = new char[string_size + 1];
                strncpy(tmp_str,&data[l_pntr],string_size);
                strncpy(&tmp_str[string_size],STRING_END,1);
                
                (*output)[no_of_strings - sizeof(short)] = String(tmp_str);

                delete[] tmp_str;
                r_pntr++;
                l_pntr = r_pntr;
                break;
            }
        }
        if(delim_found == 0){
            r_pntr++;
        }
    }

    *size = no_of_strings;

     /**
     * Last str has no delim to border it so we do it here.
     */

    if(out_is_null == 0){
        string_size = r_pntr - l_pntr;
        char *last_string = new char[string_size + 1];

        strncpy(last_string,&data[l_pntr],string_size);
        strncpy(&last_string[string_size],STRING_END,1);
        
        (*output)[no_of_strings - 1] = String(last_string);
        

        delete[] last_string;
    }
}


int String::to_integer() const{
    return atoi(this->data);
}


    /**
     * Trim uses pointers to track the str limits and copy into a new str.
     */

String String::trim() const{

    int trimmed_len = 0;
    char *pntr = this->data;

    while (*pntr == ' ') {
        pntr++;
    }

    char *l_pntr = pntr;

    while (*pntr != '\0' && *pntr != ' '){
        trimmed_len++;
        pntr++;
    }
    if(trimmed_len == 0) {
        return String();
    }

    char *trimmed_str = new char[trimmed_len + 1];

    for(int i=0; i<trimmed_len;i++){
        trimmed_str[i] = *l_pntr;
        l_pntr++;
    }

    trimmed_str[trimmed_len] = '\0';
    String trimmed_string(trimmed_str);

    delete[] trimmed_str;

    return trimmed_string;
}

#endif
