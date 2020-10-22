//
// Created by maslov on 20.10.20.
//

#include "gtest/gtest.h"

#include "../additive_accumulator_1.h"

#include <string>

TEST(unit1, API1) {
    additive_accumulator_1 a;
    a.add(std::string("adding"));
    additive_accumulator_1::witness c = a.create_witness(0);
    additive_accumulator_1::witness d = a.create_witness(0, 1);
    EXPECT_EQ(c.size(), d.size());
    EXPECT_TRUE(a.verify_witness("adding", 0, 1, c));
    EXPECT_TRUE(a.verify_witness("adding", 0, 1, d));
}

TEST(unit1, API2) {
    statement_1 s("a", "b", "c");
    EXPECT_EQ(s.x, "a");
    EXPECT_EQ(s.prev, "b");
    EXPECT_EQ(s.parent, "c");
}


