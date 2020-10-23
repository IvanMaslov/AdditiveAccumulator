//
// Created by maslov on 22.10.20.
//

#include "gtest/gtest.h"

#include "../additive_accumulator_2.h"
#include "test_util.h"

#include <string>
#include <chrono>


TEST(unit2, API_accumulator) {
	additive_accumulator_2 a;
	a.add(std::string("adding"));
	additive_accumulator_2::witness c = a.create_witness(1, 1);
 	additive_accumulator_2::witness d = a.create_witness(1, 1);
	EXPECT_EQ(c.size(), d.size());
	EXPECT_TRUE(a.verify_witness("adding", 1, 1, c));
	EXPECT_TRUE(a.verify_witness("adding", 1, 1, d));
}

TEST(unit2, API_statement) {
	statement_2 s("a", "b");
	EXPECT_EQ(s.x, "a");
	EXPECT_EQ(s.rh, "b");
}


TEST(functional2, emplty_verify) {
	additive_accumulator_2 a;
	a.add("add");
	EXPECT_FALSE(a.verify_witness("add", 0, 1, std::vector<statement_2>()));
	EXPECT_FALSE(a.verify_witness("add", 1, 1, std::vector<statement_2>()));
}

TEST(functional2, load) {
	using namespace std::chrono;
	high_resolution_clock::time_point begin = high_resolution_clock::now();
	additive_accumulator_2 a;
	for (size_t iter = 0; iter < 10000; ++iter) {
		a.add(std::to_string(iter));
		a.create_witness(iter + 1, iter + 1);
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	EXPECT_TRUE(duration_cast<milliseconds>( end - begin ).count() < 1800);
	EXPECT_TRUE(duration_cast<milliseconds>( end - begin ).count() > 1200);
}

TEST(functional2, sequential_verify) {
	additive_accumulator_2 a;
	std::vector<std::string> r;
	std::vector<additive_accumulator_2::witness> p;
	for (size_t iter = 0; iter < 1000; ++iter) {
		r.push_back(std::to_string(TestUtil::rnd()));
		a.add(r.back());
		p.push_back(a.create_witness(iter + 1, iter + 1));
	}
	for (size_t iter = 0; iter < 1000; ++iter) {
		ASSERT_TRUE(a.verify_witness(r[iter], iter + 1, iter + 1, p[iter])) << " in " << iter << "th iteration" << std::endl;
	}
}

TEST(functional2, unsequential_verify) {
	additive_accumulator_2 a;
	std::vector<std::string> r;
	std::vector<size_t> l;
	std::vector<additive_accumulator_2::witness> p;
	for (size_t iter = 0; iter < 1000; ++iter) {
		r.push_back(std::to_string(TestUtil::rnd()));
		l.push_back(1 + TestUtil::rnd() % (1 + iter));
		a.add(r.back());
		p.push_back(a.create_witness(l.back(), iter + 1));
	}
	for (size_t iter = 0; iter < 1000; ++iter) {
		ASSERT_TRUE(a.verify_witness(r[l[iter] - 1], l[iter], iter + 1, p[iter])) << " in " << iter << "th iteration" << std::endl;
	}
}

TEST(functional2, corrupted__verify) {
	additive_accumulator_2 a;
	std::vector<std::string> r;
	std::vector<size_t> l;
	std::vector<additive_accumulator_2::witness> p;
	for (size_t iter = 0; iter < 1000; ++iter) {
		r.push_back(std::to_string(TestUtil::rnd()));
		l.push_back(1 + TestUtil::rnd() % (1 + iter));
		a.add(r.back());
		p.push_back(TestUtil::break_witness_2(a.create_witness(l.back(), iter + 1)));
	}
	for (size_t iter = 0; iter < 1000; ++iter) {
		ASSERT_FALSE(a.verify_witness(r[l[iter] - 1], l[iter], iter + 1, p[iter])) << " in " << iter << "th iteration" << std::endl;
	}
}
