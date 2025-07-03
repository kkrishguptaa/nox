#include <gtest/gtest.h>
#include <cstdio>
#include <string>
#include <lexer.h>

// Utility

struct StdinRedirect
{
  int old_stdin_fd;
  FILE *tmp;
  StdinRedirect(const std::string &s)
  {
    // Create temporary file with padded input
    tmp = tmpfile();
    std::string padded = " " + s + " ";
    fwrite(padded.data(), 1, padded.size(), tmp);
    rewind(tmp);
    // Duplicate stdin fd and redirect to tmp
    old_stdin_fd = dup(fileno(stdin));
    dup2(fileno(tmp), fileno(stdin));
  }
  ~StdinRedirect()
  {
    // Restore original stdin fd
    fflush(stdin);
    dup2(old_stdin_fd, fileno(stdin));
    close(old_stdin_fd);
    fclose(tmp);
  }
};

// Helper to redirect stdin for get_token tests

TEST(lexer_test, Identifier)
{
  StdinRedirect redirect("myVar");
  EXPECT_EQ(get_token(), tok_identifier);
  EXPECT_EQ(IdentifierString, "myVar");
}

TEST(lexer_test, Keyword)
{
  StdinRedirect redirect("int8");
  EXPECT_EQ(get_token(), tok_int8);
}

TEST(lexer_test, BooleanLiterals)
{
  StdinRedirect redirect("true false");
  EXPECT_EQ(get_token(), tok_true);
  EXPECT_TRUE(BooleanValue);
  EXPECT_EQ(get_token(), tok_false);
  EXPECT_FALSE(BooleanValue);
}

TEST(lexer_test, NumberLiterals)
{
  StdinRedirect redirect("42 3.14");
  EXPECT_EQ(get_token(), tok_number);
  EXPECT_EQ(NumberValue, 42);
  EXPECT_EQ(get_token(), tok_number);
  EXPECT_EQ(NumberValue, 3.14);
}

TEST(lexer_test, StringLiterals)
{
  StdinRedirect redirect("\"hello\" 'A'");
  EXPECT_EQ(get_token(), tok_string_literal);
  EXPECT_EQ(StringValue, "hello");
  EXPECT_EQ(get_token(), tok_char_literal);
  EXPECT_EQ(CharValue, 'A');
}

TEST(lexer_test, SpecialOperators)
{
  StdinRedirect redirect("= := ~= .. ->");
  EXPECT_EQ(get_token(), tok_assign);
  EXPECT_EQ(get_token(), tok_assign_immutable);
  EXPECT_EQ(get_token(), tok_type_coerce);
  EXPECT_EQ(get_token(), tok_range);
  EXPECT_EQ(get_token(), tok_arrow);
}

TEST(lexer_test, MathematicalOperators)
{
  StdinRedirect redirect("+ - * / % ^");

  EXPECT_EQ(get_token(), tok_plus);
  EXPECT_EQ(get_token(), tok_minus);
  EXPECT_EQ(get_token(), tok_multiply);
  EXPECT_EQ(get_token(), tok_divide);
  EXPECT_EQ(get_token(), tok_modulo);
  EXPECT_EQ(get_token(), tok_exponent);
}

TEST(lexer_test, AssignmentOperators)
{
  StdinRedirect redirect("+= -= *= /= %=");

  EXPECT_EQ(get_token(), tok_plus_assign);
  EXPECT_EQ(get_token(), tok_minus_assign);
  EXPECT_EQ(get_token(), tok_multiply_assign);
  EXPECT_EQ(get_token(), tok_divide_assign);
  EXPECT_EQ(get_token(), tok_modulo_assign);
}

TEST(lexer_test, ComparisonOperators)
{
  StdinRedirect redirect("== != < > <= >=");

  EXPECT_EQ(get_token(), tok_equals);
  EXPECT_EQ(get_token(), tok_not_equals);
  EXPECT_EQ(get_token(), tok_left_angle);
  EXPECT_EQ(get_token(), tok_right_angle);
  EXPECT_EQ(get_token(), tok_less_equal);
  EXPECT_EQ(get_token(), tok_greater_equal);
}

TEST(lexer_test, LogicalOperators)
{
  StdinRedirect redirect("&& || !");

  EXPECT_EQ(get_token(), tok_logical_and);
  EXPECT_EQ(get_token(), tok_logical_or);
  EXPECT_EQ(get_token(), tok_logical_not);
}

TEST(lexer_test, Deconstruct)
{
  StdinRedirect redirect("~construct");

  EXPECT_EQ(get_token(), tok_destruct);
}

TEST(lexer_test, Punctuation)
{
  StdinRedirect redirect("() [] {} , ; : .");

  EXPECT_EQ(get_token(), tok_left_paren);
  EXPECT_EQ(get_token(), tok_right_paren);
  EXPECT_EQ(get_token(), tok_left_square);
  EXPECT_EQ(get_token(), tok_right_square);
  EXPECT_EQ(get_token(), tok_left_brace);
  EXPECT_EQ(get_token(), tok_right_brace);
  EXPECT_EQ(get_token(), tok_comma);
  EXPECT_EQ(get_token(), tok_semicolon);
  EXPECT_EQ(get_token(), tok_colon);
  EXPECT_EQ(get_token(), tok_dot);
}
