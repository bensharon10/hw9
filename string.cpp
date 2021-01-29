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
	strncpy(data, str, length + 1);
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
	std::cout << "enter split" << std::endl;
	if(delimiters == NULL){
    	std::cerr << "delimitires is null" << std::endl;
    	return;
    }

	(*size) = 0;
    size_t start = 0, end = 0, num_of_deli = strlen(delimiters);
    int tmp = 0, string_length = 0, match = 0, counter = 1;

    if(output == NULL){
    	tmp = 1;
    }
    else{
    	*output = new String[((this->length) / sizeof(short)) + 1];
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

    			++counter;
    			if(tmp == 1){
    				++end;
    				start = end;
    				break;
    			}
    			string_length = end - start;
    			std::cout << "aaaaa" << std::endl;
    			char *tmp_str = new char[string_length + 1];
    			std::cout << "bbbbb" << std::endl;
    			strncpy(tmp_str, &data[start], string_length);
    			std::cout << "ccccc" << std::endl;
    			strncpy(&tmp_str[string_length], END_OF_STRING, 1);
    			std::cout << "ddddd" << std::endl;
    			(*output)[*size] = String(tmp_str);
    			std::cout << "eeeee" << std::endl;
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

    *size = counter;

    if(tmp == 0){
    	string_length = end - start;
    	char *tmp_str = new char[string_length + 1];
    	strncpy(tmp_str, &data[start], string_length);
    	strncpy(&tmp_str[string_length], END_OF_STRING, 1);
    	(*output)[*size] = String(tmp_str);
    	delete[] tmp_str;
    }
}


int String::to_integer() const{
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
