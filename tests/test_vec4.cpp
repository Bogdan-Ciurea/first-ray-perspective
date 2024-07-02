#include <gtest/gtest.h>

#include "math/vec4.hpp"

class TestVec4 : public ::testing::Test {
 public:
  TestVec4() {}
  virtual ~TestVec4() {}

  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST_F(TestVec4, TestInstance) {
  vec4 v = vec4(1, 2, 3, 4);
  EXPECT_EQ(v.x(), 1);
  EXPECT_EQ(v.y(), 2);
  EXPECT_EQ(v.z(), 3);
  EXPECT_EQ(v.w(), 4);
}

TEST_F(TestVec4, TestInstanceRGB) {
  vec4 v = vec4(1, 2, 3, 4);
  EXPECT_EQ(v.r(), 1);
  EXPECT_EQ(v.g(), 2);
  EXPECT_EQ(v.b(), 3);
  EXPECT_EQ(v.a(), 4);
}

TEST_F(TestVec4, TestInstanceArray) {
  vec4 v = vec4(1, 2, 3, 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST_F(TestVec4, TestEquality) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(1, 2, 3, 4);
  EXPECT_TRUE(v1 == v2);
}

TEST_F(TestVec4, TestInequality) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(1, 2, 4, 5);
  EXPECT_TRUE(v1 != v2);
}

TEST_F(TestVec4, TestAddition) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  vec4 v3 = v1 + v2;
  EXPECT_EQ(v3.x(), 6);
  EXPECT_EQ(v3.y(), 8);
  EXPECT_EQ(v3.z(), 10);
  EXPECT_EQ(v3.w(), 12);
}

TEST_F(TestVec4, TestSubtraction) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  vec4 v3 = v1 - v2;
  EXPECT_EQ(v3.x(), -4);
  EXPECT_EQ(v3.y(), -4);
  EXPECT_EQ(v3.z(), -4);
  EXPECT_EQ(v3.w(), -4);
}

TEST_F(TestVec4, TestMultiplication) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  vec4 v3 = v1 * v2;
  EXPECT_EQ(v3.x(), 5);
  EXPECT_EQ(v3.y(), 12);
  EXPECT_EQ(v3.z(), 21);
  EXPECT_EQ(v3.w(), 32);
}

TEST_F(TestVec4, TestDivision) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  vec4 v3 = v1 / v2;
  EXPECT_NEAR(v3.x(), 0.2, 0.0001);
  EXPECT_NEAR(v3.y(), 1.0 / 3.0, 0.0001);
  EXPECT_NEAR(v3.z(), 3.0 / 7.0, 0.0001);
  EXPECT_NEAR(v3.w(), 0.5, 0.0001);
}

TEST_F(TestVec4, TestAdditionAssignment) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  v1 += v2;
  EXPECT_EQ(v1.x(), 6);
  EXPECT_EQ(v1.y(), 8);
  EXPECT_EQ(v1.z(), 10);
  EXPECT_EQ(v1.w(), 12);
}

TEST_F(TestVec4, TestSubtractionAssignment) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  v1 -= v2;
  EXPECT_EQ(v1.x(), -4);
  EXPECT_EQ(v1.y(), -4);
  EXPECT_EQ(v1.z(), -4);
  EXPECT_EQ(v1.w(), -4);
}

TEST_F(TestVec4, TestMultiplicationAssignment) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  v1 *= v2;
  EXPECT_EQ(v1.x(), 5);
  EXPECT_EQ(v1.y(), 12);
  EXPECT_EQ(v1.z(), 21);
  EXPECT_EQ(v1.w(), 32);
}

TEST_F(TestVec4, TestDivisionAssignment) {
  vec4 v1 = vec4(1, 2, 3, 4);
  vec4 v2 = vec4(5, 6, 7, 8);
  v1 /= v2;
  EXPECT_NEAR(v1.x(), 0.2, 0.0001);
  EXPECT_NEAR(v1.y(), 1.0 / 3.0, 0.0001);
  EXPECT_NEAR(v1.z(), 3.0 / 7.0, 0.0001);
  EXPECT_NEAR(v1.w(), 0.5, 0.0001);
}

TEST_F(TestVec4, TestNegation) {
  vec4 v = vec4(1, 2, 3, 4);
  vec4 v2 = -v;
  EXPECT_EQ(v2.x(), -1);
  EXPECT_EQ(v2.y(), -2);
  EXPECT_EQ(v2.z(), -3);
  EXPECT_EQ(v2.w(), -4);
}

TEST_F(TestVec4, TestScalarMultiplication) {
  vec4 v = vec4(1, 2, 3, 4);
  vec4 v2 = 2.f * v;
  EXPECT_EQ(v2.x(), 2);
  EXPECT_EQ(v2.y(), 4);
  EXPECT_EQ(v2.z(), 6);
  EXPECT_EQ(v2.w(), 8);
}

TEST_F(TestVec4, TestScalarDivision) {
  vec4 v = vec4(1, 2, 3, 4);
  vec4 v2 = v / 2;
  EXPECT_NEAR(v2.x(), 0.5, 0.0001);
  EXPECT_NEAR(v2.y(), 1, 0.0001);
  EXPECT_NEAR(v2.z(), 1.5, 0.0001);
  EXPECT_NEAR(v2.w(), 2, 0.0001);
}

TEST_F(TestVec4, TestScalarMultiplicationAssignment) {
  vec4 v = vec4(1, 2, 3, 4);
  v *= 2;
  EXPECT_EQ(v.x(), 2);
  EXPECT_EQ(v.y(), 4);
  EXPECT_EQ(v.z(), 6);
  EXPECT_EQ(v.w(), 8);
}

TEST_F(TestVec4, TestScalarDivisionAssignment) {
  vec4 v = vec4(1, 2, 3, 4);
  v /= 2;
  EXPECT_EQ(v.x(), 0.5);
  EXPECT_EQ(v.y(), 1);
  EXPECT_EQ(v.z(), 1.5);
  EXPECT_EQ(v.w(), 2);
}

TEST_F(TestVec4, TestLength) {
  vec4 v = vec4(1, 2, 3, 4);
  EXPECT_NEAR(v.length(), sqrt(30), 0.0001);
}

TEST_F(TestVec4, TestLengthSquared) {
  vec4 v = vec4(1, 2, 3, 4);
  EXPECT_EQ(v.length_squared(), 30);
}

TEST_F(TestVec4, TestUnitVector) {
  vec4 v = vec4(1, 2, 3, 4);
  vec4 v2 = unit_vector(v);
  EXPECT_NEAR(v2.x(), 1 / sqrt(30), 0.0001);
  EXPECT_NEAR(v2.y(), 2 / sqrt(30), 0.0001);
  EXPECT_NEAR(v2.z(), 3 / sqrt(30), 0.0001);
}

TEST_F(TestVec4, TestUnitVectorZero) {
  vec4 v = vec4(0, 0, 0, 0);
  vec4 v2 = unit_vector(v);
  EXPECT_EQ(v2.x(), 0);
  EXPECT_EQ(v2.y(), 0);
  EXPECT_EQ(v2.z(), 0);
  EXPECT_EQ(v2.w(), 0);
}
