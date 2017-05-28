// RE.h
// Reguläre Ausdrücke

#ifndef __RE__
#define __RE__

#include <string>
#include <sstream>

using namespace std;

// Vorwaertzreferenz
class RE;

// Prototypen von Hilfsfunktionen
bool equals(RE* r1, RE* r2);

enum REType {
	PhiType, //leere Sprache
	EpsType, //leere Wort
	ChType,  //ein Zeichen
	AltType, //Oder
	ConcType, //Und
	StarType //Kleenesche Hülle
};

// Basisklasse
/**
 * RE ist ein Regulärer Ausdruck.
 */
class RE {
	public:
		//virtuel sorgt für das berschreiben der mthode.8
		virtual REType ofType()=0;
		virtual string pretty()=0;
		virtual bool containsEps()=0;
		virtual bool isPhi()=0;
		virtual RE* simp() {
			return this;
		}
};

// Abgeleitete Klassen
/**
 * Phi erbt von RE und ist die leere Sprache
 */
class Phi: public RE {
	public:
		REType ofType() {  //liegert typ zurück
			return PhiType;
		}
		string pretty() {  //toString
			return "phi";
		}
		bool containsEps() { //falls das leere den leeren string beihnalted
			return false;
		}
		bool isPhi() {
			return true;
		}
};

/**
 * Eps erbt von RE und ist das leere Wort
 */
class Eps: public RE {
	public:
		REType ofType() {
			return EpsType;
		}
		string pretty() {
			return "eps";
		}
		bool containsEps() {
			return true;
		}
		bool isPhi() {
			return false;
		}
};

/**
 * Ch erbt von RE und representiert ein Zeichen
 */
class Ch: public RE {
	private:
		char c;
	public:
		Ch(char _c) {
			c = _c;
		}
		char getChar() {
			return c;
		}
		REType ofType() {
			return ChType;
		}
		string pretty() {
			stringstream ss;
			ss << c;
			return ss.str();
		}
		bool containsEps() {
			return false;
		}
		bool isPhi() {
			return false;
		}
};

/**
 * Alt erbt von RE stellt eine Oder-verknüpfung dar
 */
class Alt: public RE {
	private:
		RE* r1;
		RE* r2;
	public:
		Alt(RE* _r1, RE* _r2) {
			r1 = _r1;
			r2 = _r2;
		}
		RE* getLeft() {
			return r1;
		}
		RE* getRight() {
			return r2;
		}
		REType ofType() {
			return AltType;
		}
		string pretty() {
			string s("(");
			s.append(r1->pretty());
			s.append("+");
			s.append(r2->pretty());
			s.append(")");
			return s;
		}
		bool containsEps() {
			return (r1->containsEps() || r2->containsEps());
		}
		bool isPhi() {
			return (r1->isPhi() && r2->isPhi());
		}
		RE* simp() {

			// ferinfachung der Teilausdrücke(rekussion)
			r1 = r1->simp();
			r2 = r2->simp();

			//überprüfung ob die hier vereinfacht werden kann
			// 6. `r1 + r2 ==> r2` falls `L(r1)={}`
			if (r1->isPhi()) {
				//delete r1;
				return r2;
			}
			// 7. `r1 + r2 ==> r1` falls `L(r2)={}`
			if (r2->isPhi()) {
				//delete r2;
				return r1;
			}
			// 5. r + r ==> r
			if (equals(r1, r2)) {
				//delete r2;
				return r1;
			}

			return this;

			// N.B. We're a bit relaxed when it comes to garbage collection.
			// For example, in case of rule (6) we should clean up the
			// memory space occupied by r1 which we ignore here.

		}
};

/**
 * Conc erbt von RE stellt eine Und-verknüpfung dar
 */
class Conc: public RE {
	private:
		RE* r1;
		RE* r2;
	public:
		Conc(RE* _r1, RE* _r2) {
			r1 = _r1;
			r2 = _r2;
		}
		RE* getLeft() {
			return r1;
		}
		RE* getRight() {
			return r2;
		}
		REType ofType() {
			return ConcType;
		}
		string pretty() {
			string s("(");
			s.append(r1->pretty());
			s.append(r2->pretty());
			s.append(")");
			return s;
		}
		bool containsEps() {
			return (r1->containsEps() && r2->containsEps());
		}
		bool isPhi() {
			return (r1->isPhi() || r2->isPhi());
		}
		RE* simp() {

			r1->simp();
			r2->simp();

			// 1. eps r ==> r
			if (r1->containsEps()) {
				//delete r1;
				return r2;
			}

			if (r2->containsEps()) {
				//delete r2;
				return r1;
			}

			// 2. r1 r2 ==> phi falls L(r1)={} oder L(r2)={}
			if (r1->isPhi() || r2->isPhi()) {
				/*delete r1;
				delete r2;
				delete this;*/
				return new Phi;
			}
			return this;
		}
};

/**
 * Star erbt von RE stellt die Kleenische hülle dar.
 */
class Star: public RE {
	private:
		RE* r;
	public:
		Star(RE* _r) {
			r = _r;
		}
		RE* getRE() {
			return r;
		}
		REType ofType() {
			return StarType;
		}
		string pretty() {
			string s;
			s.append(r->pretty());
			s.append("*");
			return s;
		}
		bool containsEps() {
			return true;
		}
		bool isPhi() {
			return false;
		}
		RE* simp() {

			// Simplify subparts
			r = r->simp();

			// Then, check if any of the simplification rules are applicable

			// 3. `r* ==> eps` falls `L(r)={}`
			if (r->isPhi()) {
				//delete r;
				return new Eps();
			}
			// 4. `(r*)* ==> r*`
			if (r->ofType() == StarType) {
				return this->r;
			}

			return this;
		}
};

// Structural comparison among regular expressions
bool equals(RE* r1, RE* r2) {
	bool b;

	if (r1->ofType() != r2->ofType())
		return false;

	switch (r1->ofType()) {
		case PhiType:
			b = true;
			break;
		case EpsType:
			b = true;
			break;
		case ChType: {
			Ch* c1 = (Ch*) r1;
			Ch* c2 = (Ch*) r2;
			b = c1->getChar() == c2->getChar();
			break;
		}
		case StarType: {
			Star* r3 = (Star*) r1;
			Star* r4 = (Star*) r2;
			b = equals(r3->getRE(), r4->getRE());
			break;
		}
		case AltType: {
			Alt* r3 = (Alt*) r1;
			Alt* r4 = (Alt*) r2;
			b = equals(r3->getLeft(), r4->getLeft())
					&& equals(r3->getRight(), r4->getRight());
			break;
		}
		case ConcType: {
			Conc* r3 = (Conc*) r1;
			Conc* r4 = (Conc*) r2;
			b = equals(r3->getLeft(), r4->getLeft())
					&& equals(r3->getRight(), r4->getRight());
			break;
		}
	}    // switch
	return b;
} // equals

// Repeated application of simp until we reach a fixpoint
RE* simpFix(RE* r1) {
	RE* r2 = r1->simp();

	if (equals(r1, r2))
		return r1;

	return simpFix(r2);
}

#endif // __RE__
