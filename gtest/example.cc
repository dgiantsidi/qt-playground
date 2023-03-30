#include "../file-parser/file_parser.h"
#include <gtest/gtest.h>

int parse(const std::string &fname) {
  file_parser a(fname);

  return a.parse_file();
}

int timestep_test(const std::string &fname) {
  file_parser a(fname);
  a.parse_file();
  return a.ret_timestep();
}

int flag_test(const std::string &fname) {
  file_parser a(fname);
  a.parse_file();
  return a.ret_flag();
}

QString units_test(const std::string &fname) {
  file_parser a(fname);
  a.parse_file();
  return a.ret_units();
}

// Test case
TEST(Test1, CorrectFile) { EXPECT_EQ(1, parse("../file-parser/file.csv")); }

TEST(Test2, InvalidFile) { EXPECT_EQ(-1, parse("../file-parser/file1.csv")); }

TEST(Test3, CheckTimestamp) {
  std::string fname("../file-parser/file.csv");
  EXPECT_EQ(100, timestep_test(fname));
}

TEST(Test4, CheckFlag) {
  std::string fname("../file-parser/file.csv");
  EXPECT_EQ(1, flag_test(fname));
}

TEST(Test5, CheckUnits) {
  std::string fname("../file-parser/file.csv");
  EXPECT_EQ(QString("ns"), units_test(fname));
}

// Main function to run the tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
