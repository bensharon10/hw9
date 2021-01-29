#ifndef STRING_CPP
#define STRING_CPP

#include "string.h"
#include <string.h>

#define END_OF_STRING "\0"

String::String(){
    data = new char[1];
    strncpy(data,END_OF_STRING,1);
    length = 0;
    //std::cout << "created string is: " << data << std::endl;
}
String::String(const String &str){
    length = str.length;
    data = new char[length+1];
    strcpy(data, str.data);
    //std::cout << "created string is: " << data << std::endl;
};

String::String(const char *str){
    length = strlen(str);
    data = new char[length+1];
    strcpy(data, str);
    //std::cout << "created string is: " << data << std::endl;
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
    //std::cout << "String_equal - the string is: " << this->data << std::endl;
    return (!strcmp(this->data, rhs.data));
}

bool String::equals(const char *rhs) const{
    //std::cout << "String_equal - the string is: " << this->data << std::endl;
    return (!strcmp(this->data, rhs));
}

/*
void String::split(const char *delimiters, String **output, size_t *size) const{
    size_t delimiter_length = strlen(delimiters) - 1;
    bool is_added = false;
    for(int i = 0; i < this->length; ++i){
        int j = 0, start = i;
        while(delimiters[j] == this->data[i]){
            if(j == delimiter_length){
                strncpy(*output + *size, this->data + start, delimiter_length-1);
                ++(*size);
                is_added = true;
            }
            else{
                ++i;
                ++j;
            }
        }
        if(!is_added){
            i = start;
        }
    }
}
*/
/*
void String::split(const char *delimiters, String **output, size_t *size) const{
    std::cout << "reached split" << std::endl;
    size_t no_of_delimiters = strlen(delimiters);
    size_t no_of_strings = 0;
    size_t last = 0;
    bool empty = !output;
    *output = new String[((this->length)/sizeof(short))+1];
    for (size_t i = 0 ; i < this->length ; i++){
        for (size_t j = 0 ; j < no_of_delimiters ; j++){
            if(delimiters[j]==this->data[i]){
                if(!empty){
                    std::cout << "if" << std::endl;
                    char* tmp_string = new char[j-last];
                    std::cout << "tmp string" << std::endl;
                    std::cout << tmp_string << std::endl;
                    std::cout << "after tmp string" << std::endl;
                    strncpy(tmp_string,this->data,j-last);
                    String *tmp = new String(tmp_string);
                    output[no_of_strings] = tmp;
                    no_of_strings++;
                    (*size)++;
                    last = j;
                } else {
                    (*size)++;    
                }
            }
        }
    }
    std::cout << "finished split" << std::endl;
}
void String::split(const char *delimiters, String **output, size_t *size) const{
    size_t no_of_delimiters = strlen(delimiters);
    size_t no_of_strings = 0;
    size_t last = 0;
    bool empty = output;
    *output = new String[((this->length)/sizeof(short))+1];
    for (size_t i=0 ; i<no_of_delimiters ; i++){
        for (size_t j=0 ; j<this->length ; j++){
            if(delimiters[i]==this->data[j]){
                char* tmp_string = new char[j-last];
                strncpy(tmp_string,this->data,j-last);
                String *tmp = new String(tmp_string);
                tmp->split(delimiters,output+no_of_strings,size);
                no_of_strings++;
                (*size)++;
                last=j;
            }
        }
        char* tmp_string = new char[(this->length)-last];
        strncpy(tmp_string,this->data+last,this->length-last);
        String *tmp = new String(tmp_string);
        *tmp = tmp->trim();
        if(output){
            output[0] = tmp;
        }
        tmp->~String();
    }
    if(!empty){
        for(size_t i = 0 ; i<no_of_strings ; i++){
            delete output[i];
        }
    }
}
*/



void String::split(const char *delimiters, String **output, size_t *size) const{
    //std::cout << "reached split" << std::endl;
    if(NULL == delimiters){
        //std::cerr << "Delimiters are NULL";
        return;
    }

    size_t start_idx = 0;
    size_t end_idx = 0;
    size_t str_count = 1;
    size_t num_of_delimiters = strlen(delimiters);
    int flag = 0;
    int ch_num = 0;
    int delim_flag = 0;

    if(NULL == output){
        flag = 1;
    } else {
        *output = new String[((this->length)/sizeof(short))+1];
    }

    while(strncmp(&data[end_idx],END_OF_STRING,1) != 0){
        delim_flag = 0;
        for(size_t delim = 0; delim < num_of_delimiters; delim++){
            if(data[end_idx] == delimiters[delim]){
                delim_flag = 1;
                if(start_idx == end_idx){
                    start_idx++;
                    end_idx++;
                    break;
                }
                str_count++;
                if(flag == 1){
                    end_idx++;
                    start_idx = end_idx;
                    break;
                }
                ch_num = end_idx - start_idx;
                char *str_to_cpy = new char[ch_num + 1];
                strncpy(str_to_cpy,&data[start_idx],ch_num);
                strncpy(&str_to_cpy[ch_num],END_OF_STRING,1);

                //std::cout << "I used trim here and..." << std::endl;
                
                (*output)[str_count - sizeof(short)] = String(str_to_cpy);
                
                //std::cout << "It worked!" << std::endl;

                delete[] str_to_cpy;
                end_idx++;
                start_idx = end_idx;
                break;
            }
        }
        if(delim_flag == 0){
            end_idx++;
        }
    }

    *size = str_count;

    if(flag == 0){
        ch_num = end_idx - start_idx;
        char *str_to_cpy_end = new char[ch_num + 1];
        strncpy(str_to_cpy_end,&data[start_idx],ch_num);
        strncpy(&str_to_cpy_end[ch_num],END_OF_STRING,1);

        //std::cout << "I used trim here and..." << std::endl;
        
        (*output)[str_count - 1] = String(str_to_cpy_end);
        
        //std::cout << "It worked!" << std::endl;

        delete[] str_to_cpy_end;
    }
    //std::cout << "finished split" << std::endl;
}
/*
    
void String::split(const char *delimiters, String **output, size_t *size) const {
    int number_of_strings = 0;
    char *temp_data = new char[this->length + 1];
    strcpy(temp_data, data);
    for (char *p = strtok(temp_data, delimiters); 
        p != NULL; p = strtok(NULL, delimiters)) {
        number_of_strings++;
    }
    if (output == NULL) {
        delete[] temp_data;
        *size = number_of_strings;
        return;
    }
    strcpy(temp_data, data);
    String *strings = new String[number_of_strings];

    char *p = strtok(temp_data, delimiters);
    for (int i = 0; i < number_of_strings; i++) {
        strings[i] = p;
        p = strtok(NULL, delimiters);
    }
    *output = strings;
    *size = number_of_strings;
    delete[] temp_data;
}
*/

int String::to_integer() const{
    return atoi(this->data);
}

/*
String String::trim() const{
    std::cout << "trim started" << std::endl;
    int before = 0;
    int after = 0;
    for (size_t i=0 ; i<this->length -1; i++){
        if(this->data[i]!=' '){
            break;
        }
        before++;
    }
    for (int j=this->length-1 ; j>=0 ; j--){
        if((this->data)[j]!=' '){
            break;
        }
        after++;
    }
    std::cout << "at least I counted right" << std::endl;
    char *tmp_string = new char[this->length - (before+after) + 1];
    std::cout << "phase 1, before+after = " << before+after << std::endl;
    strncpy(tmp_string,this->data + before ,this->length - (before+after));
    
    std::cout << "phase 2" << std::endl;
    String *tmp = new String(tmp_string);
    std::cout << "trim ended" << std::endl;
    return *tmp;
}
*/


String String::trim() const{
    int trimmed_string_length = 0;
    char *p = this->data;
    while (*p == ' ') {
        p++;
    }
    char *start = p;
    while (*p != '\0' && *p != ' '){
        trimmed_string_length++;
        p++;
    }
    if(trimmed_string_length == 0) {
        return String();
    }

    char *new_data = new char[trimmed_string_length + 1];
    for(int i=0; i<trimmed_string_length;i++){
        new_data[i] = *start;
        start++;
    }
    new_data[trimmed_string_length] = '\0';
    String trimmed_string(new_data);
    delete[] new_data;
    return trimmed_string;
}

#endif
