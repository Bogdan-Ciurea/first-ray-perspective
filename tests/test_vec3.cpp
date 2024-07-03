#include <gtest/gtest.h>

#include "math/vec3.hpp"

class TestVec3 : public ::testing::Test {
 public:
  TestVec3() {}
  virtual ~TestVec3() {}

  virtual void SetUp() override {}
  virtual void TearDown() override {}
};

TEST_F(TestVec3, TestInstance) {
  vec3 v = vec3(1, 2, 3);
  EXPECT_EQ(v.x(), 1);
  EXPECT_EQ(v.y(), 2);
  EXPECT_EQ(v.z(), 3);
}

TEST_F(TestVec3, TestInstanceRGB) {
  vec3 v = vec3(1, 2, 3);
  EXPECT_EQ(v.r(), 1);
  EXPECT_EQ(v.g(), 2);
  EXPECT_EQ(v.b(), 3);
}

TEST_F(TestVec3, TestInstanceArray) {
  vec3 v = vec3(1, 2, 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST_F(TestVec3, TestEquality) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(1, 2, 3);
  EXPECT_TRUE(v1 == v2);
}

TEST_F(TestVec3, TestInequality) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(1, 2, 4);
  EXPECT_TRUE(v1 != v2);
}

TEST_F(TestVec3, TestAddition) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  vec3 v3 = v1 + v2;
  EXPECT_EQ(v3.x(), 5);
  EXPECT_EQ(v3.y(), 7);
  EXPECT_EQ(v3.z(), 9);
}

TEST_F(TestVec3, TestSubtraction) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  vec3 v3 = v1 - v2;
  EXPECT_EQ(v3.x(), -3);
  EXPECT_EQ(v3.y(), -3);
  EXPECT_EQ(v3.z(), -3);
}

TEST_F(TestVec3, TestMultiplication) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  vec3 v3 = v1 * v2;
  EXPECT_EQ(v3.x(), 4);
  EXPECT_EQ(v3.y(), 10);
  EXPECT_EQ(v3.z(), 18);
}

TEST_F(TestVec3, TestDivision) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  vec3 v3 = v1 / v2;
  EXPECT_NEAR(v3.x(), 0.25, 0.001);
  EXPECT_NEAR(v3.y(), 0.4, 0.001);
  EXPECT_NEAR(v3.z(), 0.5, 0.001);
}

TEST_F(TestVec3, TestAdditionAssignment) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  v1 += v2;
  EXPECT_EQ(v1.x(), 5);
  EXPECT_EQ(v1.y(), 7);
  EXPECT_EQ(v1.z(), 9);
}

TEST_F(TestVec3, TestSubtractionAssignment) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  v1 -= v2;
  EXPECT_EQ(v1.x(), -3);
  EXPECT_EQ(v1.y(), -3);
  EXPECT_EQ(v1.z(), -3);
}

TEST_F(TestVec3, TestMultiplicationAssignment) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  v1 *= v2;
  EXPECT_EQ(v1.x(), 4);
  EXPECT_EQ(v1.y(), 10);
  EXPECT_EQ(v1.z(), 18);
}

TEST_F(TestVec3, TestDivisionAssignment) {
  vec3 v1 = vec3(1, 2, 3);
  vec3 v2 = vec3(4, 5, 6);
  v1 /= v2;
  EXPECT_NEAR(v1.x(), 0.25, 0.001);
  EXPECT_NEAR(v1.y(), 0.4, 0.001);
  EXPECT_NEAR(v1.z(), 0.5, 0.001);
}

TEST_F(TestVec3, TestNegation) {
  vec3 v = vec3(1, 2, 3);
  vec3 v2 = -v;
  EXPECT_EQ(v2.x(), -1);
  EXPECT_EQ(v2.y(), -2);
  EXPECT_EQ(v2.z(), -3);
}

TEST_F(TestVec3, TestScalarMultiplication) {
  vec3 v = vec3(1, 2, 3);
  vec3 v2 = v * 2;
  EXPECT_EQ(v2.x(), 2);
  EXPECT_EQ(v2.y(), 4);
  EXPECT_EQ(v2.z(), 6);
}

TEST_F(TestVec3, TestScalarDivision) {
  vec3 v = vec3(1, 2, 3);
  vec3 v2 = v / 2;
  EXPECT_NEAR(v2.x(), 0.5, 0.0001);
  EXPECT_NEAR(v2.y(), 1, 0.0001);
  EXPECT_NEAR(v2.z(), 1.5, 0.0001);
}

TEST_F(TestVec3, TestScalarMultiplicationAssignment) {
  vec3 v = vec3(1, 2, 3);
  v *= 2;
  EXPECT_EQ(v.x(), 2);
  EXPECT_EQ(v.y(), 4);
  EXPECT_EQ(v.z(), 6);
}

TEST_F(TestVec3, TestScalarDivisionAssignment) {
  vec3 v = vec3(1, 2, 3);
  v /= 2;
  EXPECT_EQ(v.x(), 0.5);
  EXPECT_EQ(v.y(), 1);
  EXPECT_EQ(v.z(), 1.5);
}

TEST_F(TestVec3, TestLength) {
  vec3 v = vec3(1, 2, 3);
  EXPECT_NEAR(v.length(), sqrt(14), 0.0001);
}

TEST_F(TestVec3, TestLengthSquared) {
  vec3 v = vec3(1, 2, 3);
  EXPECT_EQ(v.length_squared(), 14);
}

TEST_F(TestVec3, TestUnitVector) {
  vec3 v = vec3(1, 2, 3);
  vec3 v2 = unit_vector(v);
  EXPECT_NEAR(v2.x(), 1 / sqrt(14), 0.0001);
  EXPECT_NEAR(v2.y(), 2 / sqrt(14), 0.0001);
  EXPECT_NEAR(v2.z(), 3 / sqrt(14), 0.0001);
}

TEST_F(TestVec3, TestUnitVectorZero) {
  vec3 v = vec3(0, 0, 0);
  vec3 v2 = unit_vector(v);
  EXPECT_EQ(v2.x(), 0);
  EXPECT_EQ(v2.y(), 0);
  EXPECT_EQ(v2.z(), 0);
}
