#include <iostream>

class Complex {
	private:
		int re = 0;
		int im = 0;
	public:
		Complex();
		Complex(const int re, const int im);
		
		bool operator == (const Complex& x) const;

		Complex operator + (const Complex& x) const;
		
		int get_re() const;
		int get_im() const;
		void set_re(const int re);
		void set_im(const int im);
		
		friend std::ostream& operator << (std::ostream &os, const Complex& x);
};

int main() {
	Complex cnumber1(2, 3);
	Complex cnumber2(1, 5);
	
	Complex cnumber3;
	cnumber3 = cnumber1 + cnumber2;
	std::cout << "cnumber3.get_re() = " << cnumber3.get_re() << std::endl;
	std::cout << "cnumber3 = " << cnumber3 << std::endl;
	
	cnumber3 = cnumber2;
	cnumber3.set_re(10);
	std::cout << "cnumber2 = " << cnumber2 << std::endl;
	std::cout << "cnumber3 = " << cnumber3 << std::endl;
}

Complex::Complex() {};

Complex::Complex(const int re, const int im) : re(re), im(im) {}

bool Complex::operator == (const Complex& x) const {
	return false;
}

Complex Complex::operator + (const Complex& x) const {
	return { re + x.re, im + x.im };
}

int Complex::get_re() const { return re; }
int Complex::get_im() const { return im; }
void Complex::set_re(const int re) { this->re = re; }
void Complex::set_im(const int im) { this->im = im; }
		
std::ostream& operator << (std::ostream &os, const Complex& x) {
	os << x.get_re() << ", " << x.get_im();
	return os;
}
