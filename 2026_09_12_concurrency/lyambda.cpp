#include <functional>
#include <iostream>

/*
	Лямбда-выражения:
	С++ - С++11, 11 октября 2011
	Java - Java8, март 2014
	JavaScript - июнь 2015
	
	Python - январь 1994
	Lisp - 1958
*/

void ffunc(int a) { 
	std::cout << a << std::endl; 
}

void print_array(
	const int* const arr, 
	std::size_t size, 
	bool (*filter)(int) = nullptr
) {
	const char space = ' ';
	if (filter) {
		for (std::size_t i = 0; i < size; i++) {
			if (filter(arr[i])) {
				std::cout << arr[i] << space;
			}
		}
	} else {
		for (std::size_t i = 0; i < size; i++) {
			std::cout << arr[i] << space;
		}
	}
}

class PrintInt {
		unsigned int count = 0;
	public:
		void operator()(int a) {
			std::cout << ++count << ": " << a << std::endl;
		}   
};

int main() {

	// ------------------------------------------------------------------------
	// Класс функтор
	// ------------------------------------------------------------------------	
	{
		std::cout << std::endl;
		std::cout << "Объект функция / класс функтор" << std::endl;
		
		class Print {
				unsigned int count = 0;
			public:
				void operator()(int a) {
					std::cout << ++count << ": " << a << std::endl;
				}   
		};
		Print print;    
		print(11); 
		print(12);
	}
	
	// ------------------------------------------------------------------------
	// Лямбда-выражение — это специальный синтаксис для определения 
	// функциональных объектов.
	// [внешние переменные для захвата](параметры) пусто/mutable {тело функции}
	// ------------------------------------------------------------------------
	{
		std::cout << std::endl;
		std::cout << "Функция объявлена, но не вызвана" << std::endl;
		[](int a) {
			std::cout << a << std::endl;
		};
	}
	
	{
		std::cout << std::endl;
		std::cout << "Функция объявлена и вызвана" << std::endl;
		[](int a) {
			std::cout << a << std::endl;
		}(5);
	}
	
	{
		std::cout << std::endl;
		std::cout << "Присвоение функций переменным" << std::endl;
		
		void (*var_ffunc)(int a) = ffunc;
		std::cout << "var_ffunc & = " << (void*)var_ffunc << std::endl;
		std::cout << "var_ffunc = f -> ";
		var_ffunc(1);
		std::cout << std::endl;
		
		std::cout << "f является объектом-функцей" << std::endl;
		void (*f)(int a);
		f = [](int a) {
			std::cout << a << std::endl;
		};
		f(5);
	}
	
	// ------------------------------------------------------------------------
	// auto - это вычисляемый тип
	// ------------------------------------------------------------------------
	{
		std::cout << std::endl;
		std::cout << "Вычисляемый тип и возвращаемое значение" << std::endl;
		auto f = [](int a) -> int {
			std::cout << a << std::endl;
			return --a;
		};
		int a = f(5);
	}
	
	{
		std::cout << std::endl;
		std::cout << "Какой результат выполнения кода?" << std::endl;
		auto f = [](int a) {
			std::cout << a << std::endl;
		};
		f(5);
		f(4);
		f(3);
		//f("Несделанные ДЗ - это незачёт!");
	}
	
	{
		std::cout << std::endl;
		std::cout 
			<< "Начиная с с++14 у аргументов можно использовать " 
			<< "вычисляемые типы параметров" 
			<< std::endl;
		auto f = [](auto a) {
			std::cout << a << std::endl;
		};
		f(5);
		f(4);
		f(3);
		f("Несделанные ДЗ - это незачёт!");
	}
	
	{
		std::cout << std::endl;
		std::cout << "Использование лямбда-функций" << std::endl;
		
		int arr[] = { 1, -2, 5, 4, -10, 6 };
		const std::size_t size = sizeof(arr) / sizeof(*arr);
		print_array(arr, size);
		std::cout << std::endl;
		
		print_array(arr, size, [](int x) { return x >= 0; });
		std::cout << std::endl;
		print_array(
			arr, 
			size, 
			[](int x) { return x < 0; }
		);
	}
	
	{
		std::cout << std::endl;
		std::cout 
			<< "Захват внешних переменных для лямбда-функций" 
			<< std::endl
			<< "[=](параметры) {тело функции}" 
			<< std::endl
			<< "[=](параметры) mutable {тело функции}" 
			<< std::endl
			<< "[=, &arr, size](параметры) {тело функции}"
			<< std::endl
			<< "И другие варианты захватов..."
			<< std::endl;
			
		int x = 1;
		[x](auto a) mutable {
			std::cout << a << std::endl;
			x++;
			std::cout << "x внутрие = " << x << std::endl;
		}(5);
		std::cout << "x снаружи = " << x << std::endl;
	}
	
	{
		std::function<void(int)> func;
		func = PrintInt();
		func(101);
		
		func = ffunc;
		func(102);
		
		func = [](int a) { std::cout << a << std::endl; };
		func(103);
		
		
		//auto func2;
		//func2(104);
		
		/*
		auto func2 = PrintInt();
		func2(104);
		
		func2 = [](int a) { std::cout << a << std::endl; };
		func2(105);
		*/
	}
	
	return 0;
}
