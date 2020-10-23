//
// Created by maslov on 20.10.20.
//

#include "gtest/gtest.h"

#include "../additive_accumulator_1.h"

#include <string>
#include <chrono>
#include <random>

TEST(unit1, API_accumulator) {
    additive_accumulator_1 a;
    a.add(std::string("adding"));
    additive_accumulator_1::witness c = a.create_witness(1);
    additive_accumulator_1::witness d = a.create_witness(1, 1);
    EXPECT_EQ(c.size(), d.size());
    EXPECT_TRUE(a.verify_witness("adding", 1, 1, c));
    EXPECT_TRUE(a.verify_witness("adding", 1, 1, d));
}

TEST(unit1, API_statement) {
    statement_1 s("a", "b", "c");
    EXPECT_EQ(s.x, "a");
    EXPECT_EQ(s.prev, "b");
    EXPECT_EQ(s.parent, "c");
}

namespace TestUtil {
	std::random_device rnd_dev;
	std::mt19937 rnd(rnd_dev());
}

TEST(functional1, emplty_verify) {
	additive_accumulator_1 a;
	a.add("add");
	EXPECT_FALSE(a.verify_witness("add", 0, 1, std::vector<statement_1>()));
	EXPECT_FALSE(a.verify_witness("add", 1, 1, std::vector<statement_1>()));
}

TEST(functional1, load) {
	using namespace std::chrono;
	high_resolution_clock::time_point begin = high_resolution_clock::now();
	additive_accumulator_1 a;
	for (size_t iter = 0; iter < 10000; ++iter) {
		a.add(std::to_string(iter));
		a.create_witness(iter);
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	EXPECT_TRUE(duration_cast<milliseconds>( end - begin ).count() < 500);
}

TEST(functional1, sequential_verify) {
	additive_accumulator_1 a;
	std::vector<std::string> r;
	std::vector<additive_accumulator_1::witness> p;
	for (size_t iter = 0; iter < 1000; ++iter) {
		r.push_back(std::to_string(TestUtil::rnd()));
		a.add(r.back());
		p.push_back(a.create_witness(iter + 1));
	}
	for (size_t iter = 0; iter < 1000; ++iter) {
		ASSERT_TRUE(a.verify_witness(r[iter], iter + 1, iter + 1, p[iter]));
	}
}

TEST(functional1, unsequential_verify) {
	additive_accumulator_1 a;
	std::vector<std::string> r;
	std::vector<size_t> l;
	std::vector<additive_accumulator_1::witness> p;
	for (size_t iter = 0; iter < 1000; ++iter) {
		r.push_back(std::to_string(TestUtil::rnd()));
		l.push_back(1 + TestUtil::rnd() % (1 + iter));
		a.add(r.back());
		p.push_back(a.create_witness(l.back(), iter + 1));
	}
	for (size_t iter = 0; iter < 1000; ++iter) {
		ASSERT_TRUE(a.verify_witness(r[l[iter] - 1], l[iter], iter + 1, p[iter]));
	}
}
