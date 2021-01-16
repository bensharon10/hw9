#ifndef STRING_CPP
#define STRING_CPP

#include <string.h>
#include <string>

class String {
    char *data;
    size_t length;
}
String::String():data(""),length(0){}

String::String(const String &str){
	length = strlen(str.data);
	data = new char[length];
	strncpy(data, str.data, length);
};

String::String(const char *str){
	length = strlen(str);
	data = new char[length];
	strncpy(data, str, length);
}

String::~String(){
	delete data;
}

String::String& operator=(const String &rhs){
	length = rhs->length;
	delete data;
	data = new char[length](rhs);
	return *this;
}

String::String& operator=(const char *str){
	this->length = strlen(str);
	delete data;
	this->data = new char[length](str);
	return *this;
}

bool String::equals(const String &rhs) const{
	return (!strcmp(this->data, rhs->data));
}

bool String::equals(const char *rhs) const{
	return (!strcmp(this->data, rhs));
}

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

int String::to_integer() const{

}

String String::trim() const{
	String str = new String;
	str->length = this->length;
	strncpy(str->data, this->data, str->length);
	return str;
}


#endif
