#include <gtest/gtest.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include "../src/parser.h"
#include "../src/executor.h"
#include "../src/util.h"

using namespace std;

TEST(parser_tests, BasicOutput)
{
  parser p;
  auto test = p.parse("echo hello");
  ASSERT_EQ(test.size(), 1);
}

TEST(parser_tests, BasicOutputwithAnd)
{
  parser p;
  auto test = p.parse("echo hello&&");
  ASSERT_EQ(test.size(), 1);
}

TEST(parser_tests, BasicOutputwithOr)
{
  parser p;
  auto test = p.parse("echo hello||");
  ASSERT_EQ(test.size(), 1);
}

TEST(parser_tests, BasicOutputwithSemi)
{
  parser p;
  auto test = p.parse("echo hello;");
  ASSERT_EQ(test.size(), 1);
}

TEST(parser_tests, DoubleOutputwithSemi)
{
  parser p;
  auto test = p.parse("echo hello; echo hello;");
  ASSERT_EQ(test.size(), 2);
}

TEST(parser_tests, DoubleOutputwithAnd)
{
  parser p;
  auto test = p.parse("echo hello&& echo hello&&");
  ASSERT_EQ(test.size(), 2);
}

TEST(parser_tests, DoubleOutputwithOr)
{
  parser p;
  auto test = p.parse("echo hello|| echo hello||");
  ASSERT_EQ(test.size(), 2);
}
TEST(parser_tests, DoubleOutputwithSemiAnd)
{
  parser p;
  auto test = p.parse("echo hello; echo hello&&");
  ASSERT_EQ(test.size(), 2);
}

TEST(parser_tests, DoubleOutputwithSemiOr)
{
  parser p;
  auto test = p.parse("echo hello; echo hello||");
  ASSERT_EQ(test.size(), 2);
}

TEST(parser_tests, TripleOutputwithSemi)
{
  parser p;
  auto test = p.parse("echo hello; echo hello; echo hello;");
  ASSERT_EQ(test.size(), 3);
}

TEST(parser_tests, TripleOutputwithAnd)
{
  parser p;
  auto test = p.parse("echo hello&& echo hello&& echo hello&&");
  ASSERT_EQ(test.size(), 3);
}

TEST(parser_tests, TripleOutputwithOr)
{
  parser p;
  auto test = p.parse("echo hello|| echo hello|| echo hello||");
  ASSERT_EQ(test.size(), 3);
}

TEST(parser_tests, TripleOutputwithSemiAndOr)
{
  parser p;
  auto test = p.parse("echo hello; echo hello&& echo hello||");
  ASSERT_EQ(test.size(), 3);
}

TEST(executor_tests, SemiAnd)
{
  parser p;
  auto test = p.parse("echo hello; echo hello&& echo hello");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\nhello\nhello\n", result.c_str());
}

TEST(executor_tests, DoubleAnd)
{
  parser p;
  auto test = p.parse("echo hello&& echo hello&& echo hello");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\nhello\nhello\n", result.c_str());
}

TEST(executor_tests, TripleAnd)
{
  parser p;
  auto test = p.parse("echo hello&& echo hello&& echo hello&& echo hello");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\nhello\nhello\nhello\n", result.c_str());
}

TEST(executor_tests, TripleOr)
{
  parser p;
  auto test = p.parse("echo hello|| echo hello|| echo hello|| echo hello");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\n", result.c_str());
}

TEST(executor_tests, TestAndOr)
{
  parser p;
  auto test = p.parse("echo hello&& echo hello|| echo hello&& echo hello");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\nhello\nhello\n", result.c_str());
}

TEST(executor_tests, TestAndOrLetters)
{
  parser p;
  auto test = p.parse("echo A&& echo B|| echo C&& echo D");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("A\nB\nD\n", result.c_str());
}

TEST(executor_tests, TestAndOrLetterswithQuotes)
{
  parser p;
  auto test = p.parse("echo \"Apple apple\"&& echo \"Bear bear\"|| echo \"Cat cat\"&& echo \"Dog dog\"");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Apple apple\nBear bear\nDog dog\n", result.c_str());
}

TEST(executor_tests, Testblankwithquotes)
{
  parser p;
  auto test = p.parse("echo \"Apple apple\"");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Apple apple\n", result.c_str());
}

TEST(executor_tests, TestOrwithquotes)
{
  parser p;
  auto test = p.parse("echo \"Apple apple\" || echo billy");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Apple apple\n", result.c_str());
}

TEST(executor_tests, TestAndwithquotes)
{
  parser p;
  auto test = p.parse("echo \"Apple apple\"&&echo \"This is a long input with lots of characters to test longer inputs.\"");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Apple apple\nThis is a long input with lots of characters to test longer inputs.\n", result.c_str());
}

TEST(squarebrac_tests, simpletestE)
{
  parser p;
  auto test = p.parse("[ -e src/test.cpp ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestNoE)
{
  parser p;
  auto test = p.parse("[ src/test.cpp ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestdirecE)
{
  parser p;
  auto test = p.parse("[ -e src ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestdirecnoE)
{
  parser p;
  auto test = p.parse("[ src ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(testinput_tests, simpletestd)
{
  parser p;
  auto test = p.parse("test -d src&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestbracketd)
{
  parser p;
  auto test = p.parse("[ -d src ] && echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestbracketdfail)
{
  parser p;
  auto test = p.parse("[ -d src1 ] || echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestbracketefail)
{
  parser p;
  auto test = p.parse("[ -e src1 ] || echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(testinput_tests, simpletestbracketefail)
{
  parser p;
  auto test = p.parse("test -e src1|| echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(testinput_tests, simpletestbracketEfail)
{
  parser p;
  auto test = p.parse("test -d src1|| echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(testinput_tests, simpletestFpass)
{
  parser p;
  auto test = p.parse("test -f src/test.cpp&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestbracketFpass)
{
  parser p;
  auto test = p.parse("[ -f src/test.cpp ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(testinput_tests, simpletestFfail)
{
  parser p;
  auto test = p.parse("test -f src/test1.cpp|| echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestFfail)
{
  parser p;
  auto test = p.parse("[ -f src/test1.cpp ]|| echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestFfaildir)
{
  parser p;
  auto test = p.parse("[ -f src ]|| echo failed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(False)\nfailed\n", result.c_str());
}

TEST(squarebrac_tests, simpletestFpass)
{
  parser p;
  auto test = p.parse("[ -f src/parser.cpp ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletesthFpass)
{
  parser p;
  auto test = p.parse("[ -f src/parser.h ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(squarebrac_tests, simpletesthEpassFulldirect)
{
  parser p;
  auto test = p.parse("[ -e src/parser/parser.cpp ]&& echo passed");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("(True)\npassed\n", result.c_str());
}

TEST(invalidinput_tests, parenerror1)
{
  bool isValid = Util::isValid("(echo a");

  ASSERT_EQ(isValid, false);
}

TEST(invalidinput_tests, parenerror2)
{
  bool isValid = Util::isValid("(echo a)()(((");

  ASSERT_EQ(isValid, false);
}

TEST(invalidinput_tests, parenerror3)
{
  bool isValid = Util::isValid("(echo a(");

  ASSERT_EQ(isValid, false);
}

TEST(invalidinput_tests, parennoerror4)
{
  bool isValid = Util::isValid("(echo a)");

  ASSERT_EQ(isValid, true);
}

TEST(invalidinput_tests, parennoerror5)
{
  bool isValid = Util::isValid("(echo a)(echo b)");

  ASSERT_EQ(isValid, true);
}

TEST(paren_tests, simpletest1)
{
  parser p;
  auto test = p.parse("(echo a)");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\n", result.c_str());
}

TEST(paren_tests, simpletest2And)
{
  parser p;
  auto test = p.parse("(echo a) && (echo b)");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\n", result.c_str());
}

TEST(paren_tests, simpletest3Or)
{
  parser p;
  auto test = p.parse("(echo a) || (echo b)");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\n", result.c_str());
}

TEST(paren_tests, simpletest4Combine)
{
  parser p;
  auto test = p.parse("(echo a) && (echo b) || (echo c)");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\n", result.c_str());
}

TEST(paren_tests, testExample)
{
  parser p;
  auto test = p.parse("(echo a && echo b) || (echo c && echo d)");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\n", result.c_str());
}

TEST(paren_tests, testExampleextra)
{
  parser p;
  auto test = p.parse("(echo a && echo b) || (echo hi) && (echo c && echo d)");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\nc\nd\n", result.c_str());
}

TEST(paren_tests, testExampleextraparen)
{
  parser p;
  auto test = p.parse("(echo a && echo b) || (echo hi) && (echo c && echo d || (echo e))");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\nc\nd\n", result.c_str());
}

TEST(paren_tests, testExampleextraparen2)
{
  parser p;
  auto test = p.parse("((echo a && echo b) && (echo hi) && (echo c && echo d || (echo e)))");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\nhi\nc\nd\n", result.c_str());
}

TEST(paren_tests, testExampleextraparen3)
{
  parser p;
  auto test = p.parse("((echo a && echo b) && (echo hi) && (echo c || echo d || (echo e)))");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("a\nb\nhi\nc\n", result.c_str());
}

TEST(redirleft_tests, basictestecho)
{
  parser p;
  auto test = p.parse("echo hello > out.txt && cat out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\n", result.c_str());
}

TEST(redirleft_tests, secondarytestecho)
{
  parser p;
  auto test = p.parse("echo The fun dragon flies through the sky. > out.txt && cat out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("The fun dragon flies through the sky.\n", result.c_str());
}

TEST(redirleft_tests, secondarytestechodouble)
{
  parser p;
  auto test = p.parse("echo Testing > out.txt && echo The fun dragon. >> out.txt && cat out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Testing\nThe fun dragon.\n", result.c_str());
}

TEST(redirleft_tests, basictestechoduel)
{
  parser p;
  auto test = p.parse("echo Dragon > out.txt && cat < out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Dragon\n", result.c_str());
}

TEST(redirleft_tests, secondarytestechoduel)
{
  parser p;
  auto test = p.parse("echo Dragons run through the sky > out.txt && cat < out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Dragons run through the sky\n", result.c_str());
}

TEST(redirleft_tests, combotestechoduel)
{
  parser p;
  auto test = p.parse("echo Dragons run through the sky < out.txt && cat < out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Dragons run through the sky\nDragons run through the sky\n", result.c_str());
}

TEST(redirleft_tests, combotestecho2)
{
  parser p;
  auto test = p.parse("echo Dragons run through the sky > out.txt && echo Sky cat. >> out.txt && cat < out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Dragons run through the sky\nSky cat.\n", result.c_str());
}

TEST(redirleft_tests, combotestecho3)
{
  parser p;
  auto test = p.parse("echo Dragons run through the sky > out.txt && echo Sky cat. >> out.txt && echo Another line > out.txt && cat < out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Another line\n", result.c_str());
}

TEST(redirboth_tests, combotestechoboth)
{
  parser p;
  auto test = p.parse("echo Another line > out.txt && cat < out.txt > out2.txt && cat out2.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  e.execute();
  test = p.parse("cat out2.txt");
  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }
  
  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Another line\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe1)
{
  parser p;
  auto test = p.parse("echo another line > out.txt && cat out.txt | wc");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("      1       2      13\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe2)
{
  parser p;
  auto test = p.parse("echo The quick fox ran after the fast bird > out.txt && cat out.txt | wc");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("      1       8      38\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe3)
{
  parser p;
  auto test = p.parse("echo hello > out.txt && cat out.txt | grep hello");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe4)
{
  parser p;
  auto test = p.parse("echo hello, how are you today? > out.txt && cat out.txt | grep you");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello, how are you today?\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe5)
{
  parser p;
  auto test = p.parse("echo Hello, How Are You Today? > out.txt && cat out.txt | tr A-Z a-z");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("hello, how are you today?\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe6)
{
  parser p;
  auto test = p.parse("echo Hello, How Are You Today? > out.txt && cat out.txt | tr a-z A-Z");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("HELLO, HOW ARE YOU TODAY?\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe7)
{
  parser p;
  auto test = p.parse("cat out.txt | find -iname names.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("./names.txt\n", result.c_str());
}

TEST(pipebasic_tests, simplepipe8)
{
  parser p;
  auto test = p.parse("echo Sally Bob June Cat Dog Jelly Winter Summer Fun > out.txt && cat out.txt | sort out.txt");
  executor e;

  for (auto& entry : test){
    e.addCommand(entry.connector, entry.args, entry.depth);
  }

  testing::internal::CaptureStdout();
  e.execute();
  string result = testing::internal::GetCapturedStdout();

  ASSERT_STREQ("Sally Bob June Cat Dog Jelly Winter Summer Fun\n", result.c_str());
}