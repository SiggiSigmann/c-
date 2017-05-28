// Main fuer Teilaufgabe 1
// Bitte weitere Testfaelle hinzufuegen.

#include "RE.h"
#include <iostream>

using namespace std;

int main() {

	// phi + c
	RE* r3 = new Alt(new Phi(), new Ch('c'));
	cout << "vorher: " << r3->pretty() << endl;
	cout << "nachher: " << r3->simp()->pretty() << endl;

	// c + phi
	RE* r4 = new Alt(new Ch('c'), new Phi());
	cout << "vorher: " << r4->pretty() << endl;
	cout << "nachher: " << r4->simp()->pretty() << endl;

	// c**
	RE* r5 = new Star(new Star(new Ch('c')));
	cout << "vorher: " << r5->pretty() << endl;
	cout << "nachher: " << r5->simp()->pretty() << endl;

	// phi*
	RE* r6 = new Star(new Phi());
	cout << "vorher: " << r6->pretty() << endl;
	cout << "nachher: " << r6->simp()->pretty() << endl;

	// (phi + c) + c**
	RE* r7 = new Alt(r3, r5);
	cout << "vorher: " << r7->pretty() << endl;
	cout << "nachher: " << simpFix(r7)->pretty() << endl;

	// (phi + c) + c**
	RE* r8 = new Alt(new Conc(new Star(r5),new Star(r4)), new Alt(new Conc(new Ch('a'), new Eps()), new Phi()));
	cout << "vorher: " << r8->pretty() << endl;
	cout << "nachher: " << simpFix(r8)->pretty() << endl;
}
