/*
#include <iostream>

using namespace std;

class A
{
public:
	
	float v;
	A()
	{
		A::v = 1;
	}
	float set(float v)
	{
		A::v += 1.0;
		return v;
	}
	float set(void)
	{
		A::v = v + 1.0f;
		return 0.0;
	}
	float get(float v)
	{
		v += A::v;
		return v;
	}
};

int main()
{
	A a, b(a);
	cout << a.get(a.set(a.set(a.set()))) << endl;
	cout << b.v << endl;
}
*/


/*
#include <iostream>
using namespace std;

class A
{
	int* val;
public:
	A() {
		val = new int;
		*val = 0;
	}
	int get()
	{
		return ++(*val);
	}
};

int main()
{
	A a, b = a;
	cout << a.get() << b.get();
	return 0;
}
*/


/*
#include <iostream>

using namespace std;

class X
{
public:
	int v;
	void put(int x)
	{
		v = x;
	}
	int get(void)
	{
		return v;
	}
};

class Y : public X
{
public:
	Y()
	{
		put(0);
	}
	void write(int x)
	{
		put(x + 1);
	}
	int read(void)
	{
		return get() - 1;
	}
};

int main()
{
	Y* y = new Y();
	y->write(1);
	cout << y->read();
	delete y;
	return 0;
}
*/


/*
#include <iostream>

using namespace std;

class X
{
private:
	int v;
protected:
	X()
	{
		v = 12;
	}
	X(int v)
	{
		this->v = v;
	}
	int get()
	{
		return v;
	}
};

class Y : public X
{
public:
	Y(int v): X(v) {}
	int get()
	{
		return X::get();
	}
};

int main()
{
	Y y(23);
	cout << y.get();
	return 0;
}
*/


// წინაპარი კლასის ფუნქცია თუ virtual არის (ვირტუალურია) მაშინ მისი შთამომავალი კლასის იგივე ფუნქციაც ვირტუალური იქნება
/*
#include <iostream>

using namespace std;

class X
{
public:
	virtual void shout()
	{
		cout << "X";
	}
};

class Y : public X
{
public:
	void shout() override
	{
		cout << "Y";
	}
};

class Z : public Y
{
public:
	void shout() override
	{
		cout << "Z";
	}
};

int main()
{
	Z* z = new Z();
	dynamic_cast<Y*>(z)->shout();
	return 0;
}
*/


/*
#include <iostream>

using namespace std;

class A
{
	void shout()
	{
		cout << "X";
	}
	void pr()
	{
		cout << "Luka";
	}
};

class X : public A
{
public:
	void shout()
	{
		cout << "X";
	}
	void pr()
	{
		cout << "Luka";
	}
};

class Y : public X
{
public:
	void shout()
	{
		cout << "Y";
	}
	void pr()
	{
		cout << "Luka";
	}
};

class Z : public X
{
public:
	void shout()
	{
		cout << "Z";
	}
};

class T : public Z
{
public:
	void shout()
	{
		cout << "T";
	}
};

int main()
{
	Y* y = new Y();
	//X* x = dynamic_cast<X*>(y);
	A* a = dynamic_cast<A*>(y);
	return 0;
}
*/

// up_cast შეიძლება static და dynamic cast-ით
// dawn_cast შეიძლება static cast-ით და ასევე dynamic-თაც თუ მისი ოპერანდის კლასი პოლიმორფულია ანუ შეიცავს ერთ ვირტუალურ ფუნქციას მაინც


// როცა Virtual გადაამისამართებს პოინტერს "_რეალური_ კლასის" ფუნქციასთან ამ დროს ამ კლასის ფუნქციაც virtual უნდა იყოს თორემ მოხდება EXCEPTION-ი


// dynamic_cast-ს შეუძლია "ნებისმიერი რაოდენობის გზის" cast-ის გაკეთება ოღონდ ამ გზაში თუ down_cast-იც შედის მაშინ აუცილებელია რომ პოლიმორფული იყოს მისი ოპერანდის კლასი
// თუ ამ გზების გავლისას down_cast არ გვხვდება მაშინ არაა აუცილებელი პოლიმორფული რომ იყოს მისი ოპერანდის კლასი -> ეს გამომდინარეობს წინა დასკვნებიდან


// static_cast ყოველ ჯერზე ერთგზიან cast-ს აკეთებს ან up-ს ან dawn-ს.
// dynamic_cast ნებისმიერი რაოდენობის cast-ს აკეთებს პირდაპირ ერთი მოქმედებით, ოღონდ თუ მასში dawn_cast-იც შედის მაშინ პოლიმორფულობა არ უნდა დაგვავიწყდეს!



//---------------------------------------------------------


// EXCEPTIONS

/*
#include <iostream>

using namespace std;

class Luka
{
public:
	Luka() {}
};

int get()
{
	return 0;
}

int main()
{
	int a = 8, b = 0, c = 6;
	try {
		//c = a / get();
		throw exception();
	}
	catch (logic_error & e)
	{
		cout << "Luka4";
		cout<<+e.what();
	}
	catch (exception e)
	{
		cout << "Luka1";
	}
	catch (...)
	{
		cout << "shemeshviiit" << endl;
	}
	try {
		cout << "raginda?";
		throw logic_error("???????");
	}
	catch (logic_error e)
	{
		cout << "Luka1";
	}
	catch (...)
	{
		cout << c;
	}
	cout << c;
	return 0;
}
*/

// try ერთ catch-ერს(handler-ს) მაინც ითხოვს და ასევე პირიქითაც
// void* -> ??
// exception()-ს - პარამეტრი არ სჭირდება, ცარიელ სტრინგს ბეჭდავს, ხოლო logic_error-ს სჭირდება
// ის მეოთხე შეცდომის კოდი გასინჯე მაინტერესებს! :)
/*
#include <iostream>

using namespace std;

int main()
{
	cout << "luka";
	try {
		throw 2 / 4;
	}
	catch (int i)
	{
		cout << i;
	}
	return 0;
}
*/


/*
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

class E {};

class X {
public:
	static int c;
	X(int a) { c = a; }
	~X() { if (c++ > 2) throw new E; }
};

int X::c = 0;

void f(int i) {
	X* t[2];
	for (int j = 0; j < i; j++)
		t[j] = new X(i + 1);
	for (int j = 0; j < i; j++)
		delete t[j];
}

int main(void)
{
	try {
		f(2);
	}
	catch (...)
	{
		cout << X::c;
	}
}
*/




// operator overloading and enumeration

/*
#include <iostream>

using namespace std;

class A
{
public:
	int v;
	A()
	{
		v = 1;
	}
	A(int v)
	{
		this->v = v;
	}
	void operator&&(int k)
	{
		v >>= 1;
	}
};

ostream& operator<<(ostream& out, A& a)
{
	return out << a.v;
}

int main()
{
	A luka = 8;
	luka = 1;
	cout << luka << endl;
}
*/


/*
#include <iostream>

using namespace std;

enum e{a,b,c,d = -7};
enum s{x,y,z,w};

e& operator++(e& x)
{
	x = c; return x;
}

int main()
{
	e f = c;
	e t = c;
	cout << int(++(f)) << endl;
	cout << c << b << endl;
}
*/

/*
#include <iostream>

using namespace std;
class Int {
public:
	int v;
	Int(int a)
	{
		v = a;
	}
	Int& operator--()
	{
		++v;
		return *this;
	}
	Int& operator--(int v)
	{
		v += 2;
		return *this;
	}
};

ostream& operator<<(ostream& o, Int& a)
{
	return o << a.v++;
}
int main()
{
	Int i = 0;
	cout << --i << i--;
}
*/

/*
#include <iostream>

using namespace std;

enum T { A = 2, B = -1, C };

class Int {
public:
	T v;
	Int(T a) {
		v = a;
	}
	Int& operator++()
	{
		//v += 2;
		return *this;
	}
};

int main()
{
	T f = A;
	f = T(f + 1);
	cout << f;
}
*/


/*
#include <iostream>

using namespace std;

class N {
public:
	float x;
	N() { x = 0.0; }
	N(float a) { x = a; }
	N(N& n) {
		x = n.x;
	}
};

N& operator=(N& y, float f)
{
	return *new N(f);
}

int main()
{
	N a, b;
	b = a = 2.0;
	cout << a.x;
	return 0;
}
*/


// ისწავლე preprocessor-ი გირჩევნია :)
/*
#include <iostream>

using namespace std;

#define A 0
#define B A+1
#define C 1-B

int main()
{
	cout << C;
}
*/

/*
#include <iostream>

using namespace std;

namespace Space
{
	char a = 'a', b = 'b';
}

int a = 1, b = 2;

int main()
{
	using Space::a;
	cout << a << "  " << b;
}
*/


/*
#include <iostream>

using namespace std;

class C1
{
public: int p;
private: int q;
protected: int r;
};

class C2 : private C1 {};

class C3 :public C2
{
	void foo()
	{
		r = 12;
	}
};

int a = 1, b = 2;

int main()
{

}
*/



// preprocessor directives

/*
#include <iostream>

using namespace std;

#define max(k,b) (++k > b)
# define CALL(param) { if(param) cout<<param++;}
# define A 3
# define B -A + 1
# define C 1 - B

int main()
{
	cout << C << endl;
	int a = 1;
	bool s = max(a, 2); // ++a > 2
	CALL(a);
	cout << a << endl;
	cout << s;
}
*/