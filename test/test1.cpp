//
// Created by maslov on 20.10.20.
//

#include "gtest/gtest.h"

#include "../fast_tree_v1.h"

TEST(sample, sample) {
    tree t;
    EXPECT_EQ(42, t.do_some());
}