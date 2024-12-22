#include <cassert>
#include <cmath>
#include <thread>
#include <print>
#include <vector>

double getPi(const long steps, const size_t threads) {
	long double deltax { 1. / steps };

	if(deltax > 1) {
		std::println("Rectangle width should be smaller than 1");
		return -1;
	}

	if(threads == 0) {
		std::println("Threads should be a non-zero value");
		return -1;
	}

	double sum = 0.;
		
	auto calculate = [&](const long double start, const long double end) {
		long double localSum = 0.;
		std::println("Start: {}", start);
		std::println("End: {}", end);
		for(long double i {start}; i < end; i+= deltax) {
			localSum += sqrt(1 - i * i) * deltax;
		} 

		sum += localSum;
	};

	std::vector<std::thread> threadPool;
	threadPool.reserve(threads);

	for(int i = 0; i < threads; i++) {
		threadPool.push_back(std::thread([&, i] {
			calculate(
				(1. / static_cast<double>(threads)) * i,
				(1. / static_cast<double>(threads)) * (i + 1)
			);
		}));

		/* threadPool.back().join(); */
	}

	for(auto &thread : threadPool) {
		thread.join();
	}

	return sum * 4;
}

int main(int argc, char *argv[]) {
	auto pi { getPi(1'000'000, 12) };

	std::println("PI = {}", pi);
}
