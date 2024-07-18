#include <gtest/gtest.h>

#include "../s21_matrix_plus/s21_matrix_exception.h"
#include "../s21_matrix_plus/s21_matrix_oop.h"

int add(int a, int b) { return a + b; }

TEST(AdditionTest, HandlesPositiveNumbers) { EXPECT_EQ(add(1, 2), 3); }

TEST(AdditionTest, HandlesNegativeNumbers) { EXPECT_EQ(add(-1, -1), -2); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
