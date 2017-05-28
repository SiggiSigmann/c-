#include "String.h"

ostream& operator<<(ostream &out, String &s) {
	for (int i = 0; i < s.size; i++) {
		out << s.str[i];
	}
	return out;
}

int main() {
	String s;
	String s2('H');
	String s3("hao123");
	cout << s3 << s3[2]<< endl;
	String s4;
	s4 = s3;
	s4+=s2;
	cout << s4 << endl;
	String s5(s4);
	cout << s4 << endl;
	s5[0]='1';
	cout << s4 << endl;
	cout << s5 << endl;
	s3=s4=s5;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	return 0;
}

