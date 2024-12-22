#include <thread>
#include <print>
#include <vector>

double getPi(const double deltax, const size_t threads) {
	double test = 0.;

	auto calculate = [&]() -> double {
		std::println("Hello World");
		return test++;
	};

	std::vector<std::thread> threadPool;
	threadPool.reserve(threads);

	for(int i = 0; i < threads; i++) {
		threadPool.push_back(std::thread(calculate));
	}

	for(auto &thread : threadPool) {
		thread.join();
	}

	std::println("Test: {}", test);

	return 0.;
}

int main(int argc, char *argv[]) {
	getPi(1, 10);
}
