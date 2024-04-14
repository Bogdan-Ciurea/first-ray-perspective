#include <gtest/gtest.h>

class TempTest : public ::testing::Test {
 public:
  TempTest() {}
  virtual ~TempTest() {}

  virtual void SetUp() override {}
  virtual void TearDown() override {}
};