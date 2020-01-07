#include <gtest/gtest.h>
#include "executor.h"
#include "parser.h"

using namespace std;

// used to run the googletests
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
