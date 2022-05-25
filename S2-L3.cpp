// Лабораторная работа №3 (2 семестр) Вариант №2
// 
// 1. Реализуйте алгоритм бинарного поиска, о котором шла речь на лекции. 
// Решите задачу выполнения M (0<M<10000) поисковых запросов над массивом из N (0<N<100000) элементов, 
// используя проход по массиву циклом и бинарный поиск. Сравните время работы этих двух подходов.
// 
// 2. Найдите корень уравнения x ^ 2 - 10 = 0 на отрезке[0; +беск] с точностью до 10 ^ -4 с помощью бисекции.
//

#include <iostream>
#include <chrono>
#include <cmath>

#define N 100
#define M 100

using std::cout;
using std::endl;
using std::swap;

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

void QuickSort(int a, int b, int* x)
{
	if (a >= b) return;
	int m = ((a + b) / 2) + 1;
	int k = x[m];
	int l = a - 1;
	int r = b + 1;
	while (1)
	{
		do l++; while (x[l] < k);
		do r--; while (x[r] > k);
		if (l >= r) break;
		swap(x[l], x[r]);
	}
	r = l;
	l = l - 1;
	QuickSort(a, l, x);
	QuickSort(r, b, x);
}

int BinarySearch(int* mass, int left, int right, int key)
{
	if (key < mass[left]) return -1;
	if (key == mass[left]) return left;
	if (key > mass[right]) return -1;

	while (left + 1 < right)
	{
		int middle = (left + right) / 2;
		if (key > mass[middle]) left = middle;
		else right = middle;
	}
	if (mass[right] == key) return right;
	return -1;
}

double function(double x)
{
	return x * x - 10;
}

double bisection(double left, double right, double eps)
{
	while (true)
	{
		double middle = (left + right) / 2;
		if ((abs(middle - left) < eps) || (abs(middle - right) < eps)) return middle;
		else if (function(middle) * function(left) > 0) left = middle;
		else right = middle;
	}
}

int main()
{
	srand(time(0));

	int mass[N], sortedMass[N];
	for (int i = 0; i < N; i++) {
		int r = rand() % 100;
		mass[i] = r;
		sortedMass[i] = r;
	}
	QuickSort(0, N - 1, sortedMass);

	int queries[M];
	for (int i = 0; i < M; i++) queries[i] = rand() % 100;
	
	Timer binary;
	for (int i = 0; i < M; i++)
	{
		BinarySearch(mass, 0, N - 1, queries[i]);
	}
	double binarySearchTime = binary.elapsed();

	Timer common;
	for (int i = 0; i < M; i++)
	{
		int key = queries[i];
		{
			for (int j = 0; j < N; j++)
			if (mass[j] == key)
			{
				break;
			}
		}
	}
	double commonSearchTime = common.elapsed();

	cout << "Binary search = " << binarySearchTime << endl;
	cout << "Common search = " << commonSearchTime << endl;

	std::cout << "(x^2)-10 = 0" << std::endl;
	std::cout << "x = " << bisection(0, 10000, 0.0001);
}