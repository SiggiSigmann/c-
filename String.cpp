// String.cpp
#include <iostream>
using namespace std;
#include "String.h"

int getSize(const char *s);

String::String() {
	size = 0;
	str = new char[1];
	str[0] = '\0';
}
String::String(char c) {
	size = 1;
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
}
String::String(const char *s) {
	size = getSize(s);
	str = new char[size];
	for (int i = 0; i < size; i++) {
		str[i] = s[i];
	}
}
String::String(const String& s) {
	size = s.size;
	str = new char[size];
	for (int i = 0; i < size; i++) {
		str[i] = s.str[i];
	}
}

String::~String() {
	delete[] str;
}

char& String::operator[](int index) {
	return str[index];
}

String& String::operator=(String& s) {
	size = s.size;
	char *str2 = new char[size];
	for (int i = 0; i < size; i++) {
		str2[i] = s[i];
	}
	str = str2;
	delete[] str2;
	return *this;
}

String& String::operator+=(String& s) {
	int oldsize = size;
	size += s.size;
	char *str2 = new char[size];
	for (int i = 0; i < size; i++) {
		str2[i] = str[i];
	}
	for (int i = 0; i < size; i++) {
		str2[i + oldsize] = s[i];
	}
	str = str2;
	delete[] str2;
	return *this;
}

int getSize(const char *s) {
	int i = 0;
	while (*(s + i) != '\0') {
		i++;
	}
	return i;
}
