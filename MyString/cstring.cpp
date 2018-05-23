#include "cstring.h"

cString& cString::operator= (cString& obj) {
	delete [] this->string;
	string = new char[obj.strlen() + 1];
	strcpy(this->string, obj.string);
	this->size = strlen(this->string);
	return *this;
}

cString& cString::operator= (char* str) {
	if(this->string != nullptr)
		this->~cString();
	string = new char[size = strlen(str) + 1];
	memcpy(this->string, str, size);
	return *this;
}

cString cString::operator+ (const cString& obj) {
	cString temp;
	temp.string = new char[temp.size = strlen(this->string) + strlen(obj.string) + 1];
	strcpy(temp.string, this->string);
	strcat(temp.string, obj.string);
	return temp;
}

cString cString::operator+ (const char* str) {
	cString temp;
	temp.string = new char[temp.size = strlen(this->string) + strlen(str) + 1];
	strcpy(temp.string, this->string);
	strcat(temp.string, str);
	return temp;
}

cString& cString::operator+= (const cString& obj) {
	int SIZE = size + obj.size;
	char* str = new char[SIZE];
	strcpy(str, this->string);
	delete [] this->string;
	this->string = str;
	strcpy(this->string + size, obj.string);
	size = SIZE;
	return *this;
}

cString operator+ (char *str, cString& obj) {
	cString temp;
	temp.string = new char[temp.size = strlen(obj.string) + strlen(str) + 1];
	strcpy(temp.string, str);
	strcat(temp.string, obj.string);
	return temp;
}

char& cString::operator[] (const int& index) {
	if(index <= 0 || index > this->size)
		return string[0];
	return this->string[index];
}

char* cString::operator() (int start, int finish) {
	if(start < 0 || finish > strlen(this->string)) return "Error in indices";
	if(start >= finish) return "Error in indices";
	if(this->empty())
		return "String is empty";
	else {
		char *str;
		int size = finish - start;
		str = new char[size];
		int  j = 0;
		for(int i = start-1; i < finish; i++, j++)
			str[j] = this->string[i];
		str[j] = '\0';
		return str;
	}
}

bool cString::operator== (const cString& obj) {
	if(this->size == obj.size) {
		for(int i = 0; i < obj.size; i++) {
			if(this->string[i] != obj.string[i])
				return false;
		}
	}
	return true;
}

bool cString::operator== (const char* str) {
	if(this->size == strlen(str)) {
		for(int i = 0; i < this->size; i++) {
			if(this->string[i] != str[i])
				return false;
		}
	}
	return true;
}

bool cString::operator!= (const cString& obj) {
	bool BUFF = false;
	if(this->size != obj.size) return true;
	for(int i = 0; i < obj.size; i++) {
		if(this->string[i] != obj.string[i])
			BUFF = true;
	}
	return BUFF ? true : false;
}

void cString::operator++ () {
	for(int i = 0; i < size; i++)
		string[i]++;
}
void cString::operator++ (int) {
	for(int i = 0; i < size; i++)
		string[i]++;
}
void cString::operator-- (int) {
	for(int i = 0; i < size; i++)
		string[i]--;
}

ostream& operator<< (ostream& os, const cString& obj) {
	return os << obj.string;
}
istream& operator>> (istream& is, cString& obj) {

	is >> obj.string;
	obj.size = obj.strlen();
	return is;
}

int cString::empty() {
	if(this->size == 0 ) return 1;
	else return 0;
}

int cString::strlen() {
	int size = 0;
    for (; this->string[size] != '\0'; size++);
    return size;
}

int cString::strlen(const char* str) {
	int size = 0;
    for (; str[size] != 0; size++);
    return size;
}

const char* cString::str(){
	char* buffer = new char(this->size );
	memcpy(buffer, this->string, this->size + 1);
	return (const char*)buffer;
}


