#include <thread>
#include <print>

double getPi(const long deltax, const int threads) {
	auto calculate = [&]() {
		std::println("Hello World");
	};

	std::jthread calculateThread(calculate);

	return 0.;
}

int main(int argc, char *argv[]) {
	getPi(1, 1);
}
