// Main fuer Teilaufgabe 1
// Bitte weitere Testfaelle hinzufuegen.

#include "RE.h"
#include "Orakel.h"
#include <iostream>

using namespace std;

void anwenden(RE* r, string s);

int main() {

	// phi + c
	RE* r3 = new Alt(new Phi(), new Ch('c'));
	cout << "vorher: " << r3->pretty() << endl;
	cout << "nachher: " << r3->simp()->pretty() << endl;
	anwenden(r3, "c");
	anwenden(r3, "cc");
	anwenden(r3, "");
	anwenden(r3, "hallo");

	// c + phi
	RE* r4 = new Alt(new Ch('c'), new Phi());
	cout << "vorher: " << r4->pretty() << endl;
	cout << "nachher: " << r4->simp()->pretty() << endl;
	anwenden(r4, "c");
	anwenden(r4, "cc");
	anwenden(r4, "");
	anwenden(r4, "hallo");

	// c**
	RE* r5 = new Star(new Star(new Ch('c')));
	cout << "vorher: " << r5->pretty() << endl;
	cout << "nachher: " << r5->simp()->pretty() << endl;
	anwenden(r5, "c");
	anwenden(r5, "cc");
	anwenden(r5, "cccccccccccccccc");
	anwenden(r5, "hallo");

	// phi*
	RE* r6 = new Star(new Phi());
	cout << "vorher: " << r6->pretty() << endl;
	cout << "nachher: " << r6->simp()->pretty() << endl;
	cout << orakel(r6, r6->simp(), "c") << endl;
	anwenden(r6, "");
	anwenden(r6, "  ");
	anwenden(r6, "hallo");

	// (phi + c) + c**
	RE* r7 = new Alt(r3, r5);
	cout << "vorher: " << r7->pretty() << endl;
	cout << "nachher: " << simpFix(r7)->pretty() << endl;
	anwenden(r7, "");
	anwenden(r7, "c");
	anwenden(r7, "ccccccc");
	anwenden(r7, "hallo");

	// (r5* r4*) + (('a' Eps)+Phi)
	RE* r8 = new Alt(new Conc(new Star(r5), new Star(r4)),
			new Alt(new Conc(new Ch('a'), new Eps()), new Phi()));
	cout << "vorher: " << r8->pretty() << endl;
	cout << "nachher: " << simpFix(r8)->pretty() << endl;
	anwenden(r8, "");
	anwenden(r8, "a");
	anwenden(r8, "aaaaaaaaa");
	anwenden(r8, "hallo");

	RE* r9 = new Conc(new Conc(new Ch('a'), new Ch('b')),
			new Alt(new Ch('a'), new Phi()));
	cout << "vorher: " << r9->pretty() << endl;
	cout << "nachher: " << simpFix(r9)->pretty() << endl;
	anwenden(r9, "");
	anwenden(r9, "a");
	anwenden(r9, "aaaaaaaaa");
	anwenden(r9, "hallo");
}

void anwenden(RE* r, string s) {
	cout << orakel(r, r->simp(), "s") << endl;
}
