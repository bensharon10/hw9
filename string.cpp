#ifndef STRING_CPP
#define STRING_CPP

#include "string.h"
#include <string.h>

String::String():data(""),length(0){}

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


void String::split(const char *delimiters, String **output, size_t *size) const{
    int delimiter_length = strlen(delimiters);
    int current_delimiter = 0;
    int no_of_strings = 0;
    for (int i=0 ; i<delimiter_length ; i++){
        int last = 0;
        for (int j=0 ; j<this->length ; j++){
            if(delimiters[i]==this->data[j]){
                char* tmp_string = new char[j-last];
                strncpy(tmp_string,this->data,j-last);
                String *tmp = new String(tmp_string);
                output[no_of_strings] = tmp;
                no_of_strings++;
            }
        }
    }
}
*/

void String::split(const char *delimiters, String **output, size_t *size) const{
    int no_of_delimiters = sizeof(delimiters)/ sizeof(delimiters[0]);
    int current_delimiter = 0;
    int no_of_strings = 0;
    int last = 0;

    for (int i=0 ; i<no_of_delimiters ; i++){
        for (int j=0 ; j<this->length ; j++){
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
}

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

    for (int i=0 ; i<this->length ; i++){
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
