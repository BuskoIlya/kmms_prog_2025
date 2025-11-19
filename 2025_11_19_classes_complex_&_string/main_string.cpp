#include <iostream>

class String {
	private:
		static const int END = '\0';
	
		char* data = nullptr;
		int length = 0;
		
	public:
		String();
		String(const char* const str);
		String(const String& str);
		~String();
		
		String& operator = (const String& str);
		String& operator = (const char* const str);
		
		void set_element(const int i, const char c);
		
		friend std::ostream& operator << (std::ostream& os, const String& str);
		
	private:
		int get_length(const char* const str);
		void copy(char* const dest, const char* const source, const int length);
};

int main() {
	String str1("Первая строка");
	
	String str2(str1);
	std::cout << "str2 = " << str2 << std::endl << std::endl;
	
	std::cout 
		<< "Выполнение оператора присвоение копирования "
		<< "и str2.set_element(0, '1'): " 
		<< std::endl;
	str2 = str1;
	str2.set_element(0, '1');
	std::cout << "str1 = " << str1 << std::endl;
	std::cout << "str2 = " << str2 << std::endl;
}

String::String() {}

String::String(const char* const str) {
	length = get_length(str);
	data = new char[length + 1];
	copy(data, str, length);
}

String::String(const String& str) {
	length = str.length;
	data = new char[length + 1];
	copy(data, str.data, length);
}

String::~String() {
	delete [] data;
	data = nullptr;
	length = 0;
}

String& String::operator = (const String& str) {
	if (this == &str) return *this;
	
	if (data != nullptr) {
		delete [] data;
	}
	
	length = str.length;
	data = new char[length + 1];
	copy(data, str.data, length);
	
	return *this;
}

String& String::operator = (const char* const str) {
	if (data != nullptr) {
		delete [] data;
	}
	
	length = get_length(str);
	data = new char[length + 1];
	copy(data, str, length);
	
	return *this;
}

void String::set_element(const int i, const char c) {
	if (i < length) {
		data[i] = c;
	} else {
		// TODO
	}
}

// ----------------------------------------------------------------------------
// 									FRIEND
// ----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const String& str) {
	os << str.data;
	return os;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
int String::get_length(const char* const str) {
	int length = 0;
	while (str[length] != END) {
		length++;
	}
	return length;
}

void String::copy(char* const dest, const char* const source, const int length) {
	for (int i = 0; i < length; i++) {
		dest[i] = source[i];
	}
	dest[length] = END;
}
