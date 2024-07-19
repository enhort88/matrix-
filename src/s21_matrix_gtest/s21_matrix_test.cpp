#include <gtest/gtest.h>

#include "../s21_matrix_plus/s21_matrix_exception.h"
#include "../s21_matrix_plus/s21_matrix_oop.h"

// constructors
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.get_rows(), 0);
  EXPECT_EQ(m.get_cols(), 0);
}

TEST(S21MatrixTest, ParametrizedConstructor) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.get_rows(), 3);
  EXPECT_EQ(m.get_cols(), 4);
}

TEST(S21MatrixTest, InvalidParametrizedConstructor) {
  EXPECT_THROW(S21Matrix m(-3, 4), MatrixException);
  EXPECT_THROW(S21Matrix m(3, -4), MatrixException);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m1(3, 4);
  S21Matrix m2(m1);
  EXPECT_EQ(m2.get_rows(), 3);
  EXPECT_EQ(m2.get_cols(), 4);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix m1(3, 4);
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.get_rows(), 3);
  EXPECT_EQ(m2.get_cols(), 4);
  EXPECT_EQ(m1.get_rows(), 0);
  EXPECT_EQ(m1.get_cols(), 0);
}

// accessors & mutators
TEST(S21MatrixTest, GetSetRows) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.get_rows(), 3);
  m.set_rows(5);
  EXPECT_EQ(m.get_rows(), 5);
  EXPECT_THROW(m.set_rows(-5), MatrixException);
}

TEST(S21MatrixTest, GetSetCols) {
  S21Matrix m(3, 4);
  EXPECT_EQ(m.get_cols(), 4);
  m.set_cols(6);
  EXPECT_EQ(m.get_cols(), 6);
  EXPECT_THROW(m.set_cols(-6), MatrixException);
}

// set_element & get_element
TEST(S21MatrixTest, SetElement) {
  S21Matrix m(3, 3);
  m.set_element(0, 0, 1.5);
  EXPECT_EQ(m.get_element(0, 0), 1.5);
  EXPECT_THROW(m.set_element(3, 0, 2.5), MatrixException);
  EXPECT_THROW(m.set_element(0, 3, 2.5), MatrixException);
}

TEST(S21MatrixTest, GetElement) {
  S21Matrix m(3, 3);
  m.set_element(0, 0, 1.5);
  EXPECT_EQ(m.get_element(0, 0), 1.5);
  EXPECT_THROW(m.get_element(3, 0), MatrixException);
  EXPECT_THROW(m.get_element(0, 3), MatrixException);
}

// + & -
TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m2.set_element(0, 0, 3.0);
  m2.set_element(0, 1, 4.0);
  S21Matrix result = m1 + m2;
  EXPECT_EQ(result.get_element(0, 0), 4.0);
  EXPECT_EQ(result.get_element(0, 1), 6.0);
}
// try - catch for +
TEST(S21MatrixTest, OperatorPlusIncompatibleDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  EXPECT_THROW(
      {
        try {
          S21Matrix result = m1 + m2;
        } catch (const MatrixException& e) {
          EXPECT_STREQ(
              e.what(),
              "SumMatrix: Matrices dimensions do not match for addition.");
          throw;
        }
      },
      MatrixException);
}
// -
TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1.set_element(0, 0, 5.0);
  m1.set_element(0, 1, 6.0);
  m2.set_element(0, 0, 3.0);
  m2.set_element(0, 1, 4.0);
  S21Matrix result = m1 - m2;
  EXPECT_EQ(result.get_element(0, 0), 2.0);
  EXPECT_EQ(result.get_element(0, 1), 2.0);
}

// try - catch for -
TEST(S21MatrixTest, OperatorMinusIncompatibleDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  EXPECT_THROW(
      {
        try {
          S21Matrix result = m1 - m2;
        } catch (const MatrixException& e) {
          EXPECT_STREQ(
              e.what(),
              "SubMatrix: Matrices dimensions do not match for subtraction.");
          throw;
        }
      },
      MatrixException);
}
// *
TEST(S21MatrixTest, OperatorMultiplyNumber) {
  S21Matrix m1(2, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  S21Matrix result = m1 * 2.0;
  EXPECT_EQ(result.get_element(0, 0), 2.0);
  EXPECT_EQ(result.get_element(0, 1), 4.0);
}

// * for matrix
TEST(S21MatrixTest, OperatorMultiplyMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m1.set_element(0, 2, 3.0);
  m2.set_element(0, 0, 4.0);
  m2.set_element(1, 0, 5.0);
  m2.set_element(2, 0, 6.0);
  S21Matrix result = m1 * m2;
  EXPECT_EQ(result.get_rows(), 2);
  EXPECT_EQ(result.get_cols(), 2);
  EXPECT_EQ(result.get_element(0, 0), 32.0);
  EXPECT_EQ(result.get_element(0, 1), 0.0);
}
// * Exception
TEST(S21MatrixTest, OperatorMultiplyMatrixExeption) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 2);
  EXPECT_THROW(m1 * m2, MatrixException);
}
// == 1
TEST(S21MatrixTest, OperatorEqual1) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m2.set_element(0, 0, 1.0);
  m2.set_element(0, 1, 2.0);
  EXPECT_TRUE(m1 == m2);
  m2.set_element(0, 1, 3.0);
  EXPECT_FALSE(m1 == m2);
}
// == 2
TEST(S21MatrixTest, OperatorEqual2) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 4);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m2.set_element(0, 0, 1.0);
  m2.set_element(0, 1, 2.0);
  EXPECT_FALSE(m1 == m2);
  m2.set_element(0, 1, 3.0);
  EXPECT_FALSE(m1 == m2);
}

// +=
TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m2.set_element(0, 0, 3.0);
  m2.set_element(0, 1, 4.0);
  m1 += m2;
  EXPECT_EQ(m1.get_element(0, 0), 4.0);
  EXPECT_EQ(m1.get_element(0, 1), 6.0);
}

// -=
TEST(S21MatrixTest, OperatorMinusEqual) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  m1.set_element(0, 0, 5.0);
  m1.set_element(0, 1, 6.0);
  m2.set_element(0, 0, 3.0);
  m2.set_element(0, 1, 4.0);
  m1 -= m2;
  EXPECT_EQ(m1.get_element(0, 0), 2.0);
  EXPECT_EQ(m1.get_element(0, 1), 2.0);
}

// *= for matrix
TEST(S21MatrixTest, OperatorMultiplyEqualMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m1.set_element(0, 2, 3.0);
  m2.set_element(0, 0, 4.0);
  m2.set_element(1, 0, 5.0);
  m2.set_element(2, 0, 6.0);
  m2.set_element(0, 1, 7.0);
  m2.set_element(1, 1, 8.0);
  m2.set_element(2, 1, 9.0);

  m1 *= m2;
  EXPECT_EQ(m1.get_rows(), 2);
  EXPECT_EQ(m1.get_cols(), 2);
  EXPECT_EQ(m1.get_element(0, 0), 32.0);
  EXPECT_EQ(m1.get_element(0, 1), 50.0);
}
// *=
TEST(S21MatrixTest, OperatorMultiplyEqualNumber) {
  S21Matrix m1(2, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m1 *= 2.0;
  EXPECT_EQ(m1.get_element(0, 0), 2.0);
  EXPECT_EQ(m1.get_element(0, 1), 4.0);
}
// ()
TEST(S21MatrixTest, OperatorParentheses) {
  S21Matrix m1(2, 2);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  EXPECT_EQ(m1(0, 0), 1.0);
  EXPECT_EQ(m1(0, 1), 2.0);
  m1(0, 0) = 3.0;
  EXPECT_EQ(m1(0, 0), 3.0);
}
// Minor
TEST(S21MatrixTest, Minor) {
  S21Matrix m1(3, 3);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m1.set_element(0, 2, 3.0);
  m1.set_element(1, 0, 0.0);
  m1.set_element(1, 1, 4.0);
  m1.set_element(1, 2, 5.0);
  m1.set_element(2, 0, 1.0);
  m1.set_element(2, 1, 0.0);
  m1.set_element(2, 2, 6.0);

  S21Matrix minor(2, 2);
  m1.Minor(minor, 0, 0);
  EXPECT_EQ(minor.get_element(0, 0), 4.0);
  EXPECT_EQ(minor.get_element(0, 1), 5.0);
  EXPECT_EQ(minor.get_element(1, 0), 0.0);
  EXPECT_EQ(minor.get_element(1, 1), 6.0);
}

// Transpose
TEST(S21MatrixTest, Transpose) {
  S21Matrix m1(2, 3);
  m1.set_element(0, 0, 1.0);
  m1.set_element(0, 1, 2.0);
  m1.set_element(0, 2, 3.0);
  S21Matrix result = m1.Transpose();
  EXPECT_EQ(result.get_rows(), 3);
  EXPECT_EQ(result.get_cols(), 2);
  EXPECT_EQ(result.get_element(0, 0), 1.0);
  EXPECT_EQ(result.get_element(1, 0), 2.0);
  EXPECT_EQ(result.get_element(2, 0), 3.0);
}

// Determinant1
TEST(S21MatrixTest, Determinant1) {
  S21Matrix m(2, 2);
  m.set_element(0, 0, 1.0);
  m.set_element(0, 1, 2.0);
  m.set_element(1, 0, 3.0);
  m.set_element(1, 1, 4.0);
  double det = m.Determinant();
  EXPECT_EQ(det, -2.0);
}
// Determinant2
TEST(S21MatrixTest, Determinant2) {
  S21Matrix m(3, 3);
  m.set_element(0, 0, 1.0);
  m.set_element(0, 1, 2.0);
  m.set_element(0, 2, 3.0);
  m.set_element(1, 0, 0.0);
  m.set_element(1, 1, 4.0);
  m.set_element(1, 2, 5.0);
  m.set_element(2, 0, 1.0);
  m.set_element(2, 1, 0.0);
  m.set_element(2, 2, 6.0);
  double det = m.Determinant();
  EXPECT_EQ(det, 22.0);
}

// Inverse
TEST(S21MatrixTest, Inverse) {
  S21Matrix m(2, 2);
  m.set_element(0, 0, 4.0);
  m.set_element(0, 1, 7.0);
  m.set_element(1, 0, 2.0);
  m.set_element(1, 1, 6.0);
  S21Matrix result = m.InverseMatrix();
  EXPECT_NEAR(result.get_element(0, 0), 0.6, 1e-9);
  EXPECT_NEAR(result.get_element(0, 1), -0.7, 1e-9);
  EXPECT_NEAR(result.get_element(1, 0), -0.2, 1e-9);
  EXPECT_NEAR(result.get_element(1, 1), 0.4, 1e-9);
}
// Inverse exception

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
