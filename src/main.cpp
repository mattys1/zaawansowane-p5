#include <cassert>
#include <cmath>
#include <iostream>
#include <thread>
#include <print>
#include <vector>
#include <fstream>

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

void generateBenchmarks(
	const size_t minThreads,
	const size_t maxThreads,
	const size_t minIter,
	const size_t maxIter
) {
	std::ofstream output;
	output.open("benchmark.csv", std::ios::trunc | std::ios::out);
	
	if(!output.is_open()) {
		std::cerr << "Couldn't open benchmark file";
		return;
	}

	output << "Threads;Iterations;Calculated;Time[µs]" << std::endl;

	for(auto threads {minThreads}; threads <= maxThreads; threads++) {
		size_t multiplier {10};

		for(
			size_t iterations {minIter};
			iterations <= maxIter;
			iterations >= 1'000'000'000 ? iterations += 1'000'000'000 : iterations *= multiplier
		) {
			std::println("Benchmarking with {} threads and {} iterations.", threads, iterations);

			auto benchmarkStart { std::chrono::high_resolution_clock::now() };
			auto calculated = getPi(iterations, threads);
			auto benchmarkStop { std::chrono::high_resolution_clock::now() };

			auto benchmarkDuration = std::chrono::duration_cast<std::chrono::microseconds>(
				benchmarkStop - benchmarkStart
			);

			output << std::format("{};{};{};{}", threads, iterations, calculated, benchmarkDuration.count()) << std::endl;

			/* multiplier *= 10; */
		}
	}
}

int main(int argc, char *argv[]) {
	generateBenchmarks(12, 50, 1, 1'000'000'000);
}
