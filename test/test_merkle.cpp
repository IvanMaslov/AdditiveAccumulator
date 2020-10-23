//
// Created by maslov on 22.10.20.
//

#include "gtest/gtest.h"

#include "../sha256.h"
#include "../utils.h"
#include "../merkle_tree.h"

TEST(merkle, API) {
	merkle_tree a;
	
	std::vector<std::string> b_arg;
	b_arg.push_back("a");
	merkle_tree b(b_arg);
	
	a.add(std::string("b"));
	a.set(0, std::string("a"));

	EXPECT_TRUE(a.verify_witness(a.create_witness(0), 0, "a"));
	EXPECT_TRUE(b.verify_witness(b.create_witness(0), 0, "a"));
}

TEST(utils, call) {
	size_t a = 1;
	pred(a);
	zeros(a);
	rpred(a, a);
	bit_lift(a, a);
}

TEST(utils, functional) {
	EXPECT_EQ(pred(0), 0);
	EXPECT_EQ(pred(7), 6);
	EXPECT_EQ(pred(8), 0);

	EXPECT_EQ(zeros(0), 0);
	EXPECT_EQ(zeros(7), 3);
	EXPECT_EQ(zeros(8), 1);
}
