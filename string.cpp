#ifndef STRING_CPP
#define STRING_CPP

#include "string.h"
#include <string.h>

#define END_OF_STRING "\0"

String::String(){
    data = new char[1];
    strncpy(data,END_OF_STRING,1);
    length = 0;
}
String::String(const String &str){
	length = strlen(str.data);
	data = new char[length+1];
	strncpy(data, str.data, length);
};

String::String(const char *str){
	length = strlen(str);
	data = new char[length+1];
	strncpy(data, str, length);
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

void String::split(const char *delimiters, String **output, size_t *size) const{
	std::cout << "enter split" << std::endl;
	if(delimiters == NULL){
    	std::cerr << "delimitires is null";
    	return;
    }
	*size = 0;
    size_t start = 0, end = 0, num_of_deli = strlen(delimiters);
    int tmp = 0, string_length = 0, match = 0;

    if(output == NULL){
    	tmp = 1;
    }
    else{
    	*output = new String[((this->length / sizeof(short))) + 1];
    }

    while(strncmp(&data[end], END_OF_STRING, 1) != 0){
    	match = 0;
    	for(size_t i = 0; i < num_of_deli; ++i){
    		if(delimiters[i] == data[end]){
    			match = 1;
    			if(start == end){
    				++start;
    				++end;
    				break;
    			}
    			string_length = end - start;
    			std::cout << "aaa" << std::endl;
    			char *tmp_str = new char[string_length + 1];
    			std::cout << "bbb" << std::endl;
    			strncpy(tmp_str, &data[start], string_length);
    			std::cout << "ccc" << std::endl;
    			strncpy(&tmp_str[string_length], END_OF_STRING, 1);
    			std::cout << "ddd" << std::endl;
    			(*output)[*size] = String(tmp_str);
    			std::cout << "eee" << std::endl;
    			++(*size);
    			delete[] tmp_str;
    			++end;
    			start = end;
    			break;
    		}
    	}
    	if(match == 0){
    		++end;
    	}
    }


    if(tmp == 0){
    	string_length = end - start;
    	std::cout << "aaa" << std::endl;
    	char *tmp_str = new char[string_length + 1];
    	std::cout << "bbb" << std::endl;
    	strncpy(tmp_str, &data[start], string_length);
    	strncpy(&tmp_str[string_length], END_OF_STRING, 1);
    	(*output)[*size] = String(tmp_str);
    	++(*size);
    	delete[] tmp_str;
    }
}

/*
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
/*
void String::split(const char *delimiters, String **output, size_t *size) const{
    if(NULL == delimiters){
        std::cerr << "Delimiters are NULL";
        return;
    }

size_t start_idx = 0;
size_t end_idx = 0
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

*/


int String::to_integer() const{
    /*
    int number = 0;
    for(int i = 0; i < strlen(data); i++){
        char cur_char = data[i];
        int cur_digit = cur_char - 48;
        number = 10*number + cur_digit;
    }

    return number;
     */
    return atoi(this->data);
}


String String::trim() const{

	int before = 0;
	int after = 0;

    for (size_t i=0 ; i<this->length ; i++){
        if(this->data[i]!=' '){
            break;
        }
        before++;
    }
    for (int j=this->length ; j>=0 ; j--){
        if((this->data)[j]!=' '){
            break;
        }
        after++;
    }

    char* tmp_string = new char[this->length - (before+after) + 1];
    strncpy(tmp_string,this->data + before ,this->length - (before+after));
    String *tmp = new String(tmp_string);
    return *tmp;
}


#endif
