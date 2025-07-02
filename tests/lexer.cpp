#include <gtest/gtest.h>
#include <cstdio>
#include <string>
#include <lexer.h>

// Helper to redirect stdin for get_token tests
struct StdinRedirect
{
  FILE *old_stdin;
  FILE *tmp;
  StdinRedirect(const std::string &s)
  {
    old_stdin = stdin;
    tmp = tmpfile();
    fwrite(s.data(), 1, s.size(), tmp);
    rewind(tmp);
    stdin = tmp;
  }
  ~StdinRedirect()
  {
    fclose(tmp);
    stdin = old_stdin;
  }
};

TEST(LexerTest, NumberLiteral)
{
  StdinRedirect rd("42 ");

  int tok = get_token();
  EXPECT_EQ(tok, tok_number);
  EXPECT_DOUBLE_EQ(NumberValue, 42.0);
}

TEST(LexerTest, StringLiteral)
{
  StdinRedirect rd("\"hello world\" ");

  int tok = get_token();
  EXPECT_EQ(tok, tok_string_literal);
  EXPECT_EQ(StringValue, "hello world");
}
