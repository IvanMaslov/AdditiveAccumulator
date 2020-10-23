#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include "../additive_accumulator_1.h"
#include "../additive_accumulator_2.h"

#include <random>

namespace TestUtil {
	extern std::random_device rnd_dev;
	extern std::mt19937 rnd;

	additive_accumulator_1::witness break_witness_1(additive_accumulator_1::witness);
	additive_accumulator_2::witness break_witness_2(additive_accumulator_2::witness);
}

#endif //TEST_UTIL_H

