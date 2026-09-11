#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

//std::mutex io_mtx;
class Job {
    public:
        void execute(int j) {
			//std::mutex io_mtx;
			//std::lock_guard<std::mutex> lock(io_mtx);
			std::cout << "Поток " << j << std::endl;
		}
};

int counter = 0;
void increment() {
    for (int i = 0; i < 100000; i++) {
        counter++;
    }
}

void multiply_matrix_as_in_math(
	int **a,
	std::size_t l,
	std::size_t m,
	int **b,
	std::size_t n,
	int **c
);

void multiply_matrix_as_in_math_with_multithreading(
    int thread_count, 
	int **a, 
	std::size_t l, 
	std::size_t m,
    int **b, 
	std::size_t n, 
	int **c
);

void multiply_classic_by_rows(
    int thread_count, 
	int **a, 
	std::size_t l, 
	std::size_t m,
    int **b, 
	std::size_t n, 
	int **c
);

int main() {
	{ // Кошмар
		const int job_count = 16;
		std::vector<Job> jobs(job_count);

		const int thread_count = std::thread::hardware_concurrency();
		std::vector<std::thread> threads;

		for (int i = 0; i < thread_count; i++) {
			threads.emplace_back([&jobs, i, thread_count, job_count] {
				for (int j = i * job_count / thread_count;
					 j < (i + 1) * job_count / thread_count;
					 j++) {
					jobs[j].execute(j);
				}
			});
		}

		for (std::thread& th : threads) {
			th.join();
		}
	}
	std::cout << std::endl;
	{ // 2 * 1 000 000
		std::thread t1(increment);
		std::thread t2(increment);
		t1.join();
		t2.join();
		std::cout << "Два миллиона: " << counter << std::endl;
	}
	std::cout << std::endl;
	{ // Умножение матриц
		srand(time(nullptr));
		const std::size_t size = 2000;
		std::cout << "Объём данных = " << size << std::endl;

		int **matrix_a = new int *[size];
		for (std::size_t i = 0; i < size; i++)
		{
			matrix_a[i] = new int[size];
		}
		for (std::size_t i = 0; i < size; i++)
		{
			for (std::size_t j = 0; j < size; j++)
			{
				matrix_a[i][j] = 1;
			}
		}

		int **matrix_b = new int *[size];
		for (std::size_t i = 0; i < size; i++)
		{
			matrix_b[i] = new int[size];
		}
		for (std::size_t i = 0; i < size; i++)
		{
			for (std::size_t j = 0; j < size; j++)
			{
				matrix_b[i][j] = 1;
			}
		}

		int **matrix_c = new int *[size];
		for (std::size_t i = 0; i < size; i++)
		{
			matrix_c[i] = new int[size];
		}
		for (std::size_t i = 0; i < size; i++)
		{
			for (std::size_t j = 0; j < size; j++)
			{
				matrix_c[i][j] = 0;
			}
		}

		auto start{std::chrono::steady_clock::now()};
		auto end{start};
		std::chrono::duration<double> elapsed_seconds;

		// Однопоточное умножение
		{
			// Обычное умножение матриц из алгебры без оптимизаций
			start = std::chrono::steady_clock::now();
			multiply_matrix_as_in_math(matrix_a, size, size, matrix_b, size, matrix_c);
			end = std::chrono::steady_clock::now();

			elapsed_seconds = end - start;
			std::cout
				<< "Время умножения матриц как в математике = "
				<< elapsed_seconds.count()
				<< " секунд."
				<< std::endl;
		}
		std::cout << std::endl;
		// Многопоточное умножение
		{
			// Обычное умножение матриц из алгебры без оптимизаций
			int thread_count = std::thread::hardware_concurrency();
			std::cout << "Количество потоков: " << thread_count << std::endl;
			start = std::chrono::steady_clock::now();
			multiply_matrix_as_in_math_with_multithreading(
				thread_count,
				matrix_a, 
				size, 
				size, 
				matrix_b, 
				size, 
				matrix_c
			);
			end = std::chrono::steady_clock::now();

			elapsed_seconds = end - start;
			std::cout
				<< "Время умножения матриц как в математике "
				<< "при многопоточности = "
				<< elapsed_seconds.count()
				<< " секунд."
				<< std::endl;
		}
		std::cout << std::endl;
		// Многопоточное умножение с локальностью в кэше
		{
			int thread_count = std::thread::hardware_concurrency();
			std::cout << "Количество потоков: " << thread_count << std::endl;
			start = std::chrono::steady_clock::now();
			multiply_classic_by_rows(
				thread_count,
				matrix_a, 
				size, 
				size, 
				matrix_b, 
				size, 
				matrix_c
			);
			end = std::chrono::steady_clock::now();

			elapsed_seconds = end - start;
			std::cout
				<< "Время умножения матриц как в математике "
				<< "при многопоточности с локальностью в кэше = "
				<< elapsed_seconds.count()
				<< " секунд."
				<< std::endl;
		}
	}
	{
		
	}
}

void multiply_matrix_as_in_math(
	int **a,
	std::size_t l,
	std::size_t m,
	int **b,
	std::size_t n,
	int **c
) {
	int summ;
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < n; j++) {
			summ = 0;
			for (int k = 0; k < m; k++) {
				summ += a[i][k] * b[k][j];
			}
			c[i][j] = summ;
		}
	}
}

void multiply_matrix_as_in_math_with_multithreading(
    int thread_count, 
	int **a, 
	std::size_t l, 
	std::size_t m,
    int **b, 
	std::size_t n, 
	int **c
) {
    if (thread_count < 1) thread_count = 1;
    std::vector<std::thread> pool;
    pool.reserve(thread_count);

    for (int t = 0; t < thread_count; t++) {
        const std::size_t col_begin = n * t / thread_count;
        const std::size_t col_end   = n * (t + 1) / thread_count;

        pool.emplace_back([&, col_begin, col_end]() {
            for (std::size_t column = col_begin; column < col_end; ++column) {
                for (std::size_t i = 0; i < m; i++) {
                    for (std::size_t j = 0; j < l; j++) {
                        c[j][column] += a[j][i] * b[i][column];
					}
				}
			}
        });
    }

    for (std::thread &th : pool) {
        th.join();
	}
}

void multiply_classic_by_rows(
    int thread_count, 
	int **a, 
	std::size_t l, 
	std::size_t m,
    int **b, 
	std::size_t n, 
	int **c
) {
    if (thread_count < 1) thread_count = 1;
    std::vector<std::thread> pool;
    pool.reserve(thread_count);

    for (int t = 0; t < thread_count; t++) {
        const std::size_t row_begin = l * t / thread_count;
        const std::size_t row_end   = l * (t + 1) / thread_count;

        pool.emplace_back([&, row_begin, row_end]() {
            for (std::size_t row = row_begin; row < row_end; ++row) {
                for (std::size_t i = 0; i < m; i++) {
                    for (std::size_t j = 0; j < n; j++) {
                        c[row][j] += a[row][i] * b[i][j];
					}
				}
			}
        });
    }

    for (std::thread &th : pool) {
        th.join();
	}
}
