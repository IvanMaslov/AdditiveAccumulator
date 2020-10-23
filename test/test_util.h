#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <random>

namespace TestUtil {
	extern std::random_device rnd_dev;
	extern std::mt19937 rnd;
}

#endif //TEST_UTIL_H

