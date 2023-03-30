#include "../file-parser/file_parser.h"
#include <gtest/gtest.h>

// Function to test
int Sum(int a, int b) { return a + b; }

int parse(const std::string &fname) {
  file_parser a(fname);

  return a.parse_file();
}

// Test case
TEST(SumTest, PositiveNumbers) {
  // EXPECT_EQ(5, Sum(2, 3));
  // EXPECT_EQ(12, Sum(7, 5));
  EXPECT_EQ(1, parse("../file-parser/file.csv"));
  EXPECT_EQ(-1, parse("../file-parser/file1.csv"));
}

// Main function to run the tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
