#include <string>
#include <cctype>
#include <cstdio>
#include <unordered_map>
#include "lexer.h"

// Reserve bucket count on first use for performance
static bool __keywordsReserved = []()
{ keywords.reserve(128); return true; }();

// Helper function to peek at the next character without consuming it
static int peekChar()
{
  int c = getchar();
  if (c != EOF)
  {
    ungetc(c, stdin);
  }
  return c;
}

std::string IdentifierString;
std::string StringValue;
double NumberValue;
bool BooleanValue;
char CharValue;

/// get_token - Return the next token from standard input.
int get_token()
{
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar) || LastChar == '_')
  { // identifier: [a-zA-Z_][a-zA-Z0-9_]*
    IdentifierString = LastChar;
    while (isalnum((LastChar = getchar())) || LastChar == '_')
      IdentifierString += LastChar;

    // Use keyword lookup table for better performance
    auto it = keywords.find(IdentifierString);
    if (it != keywords.end())
    {
      // Handle boolean literals specially to set BooleanValue
      if (IdentifierString == "true")
      {
        BooleanValue = true;
      }
      else if (IdentifierString == "false")
      {
        BooleanValue = false;
      }
      return it->second;
    }

    // If none of the keywords matched, it's an identifier
    return tok_identifier;
  }

  // Handle numbers (including floats)
  if (isdigit(LastChar))
  {
    std::string NumberString;
    NumberString.reserve(32);
    bool hasDecimal = false;

    while (isdigit(LastChar) || LastChar == '.')
    {
      if (LastChar == '.')
      {
        // Look ahead to see if this is a range operator (..) or decimal point
        int NextChar = peekChar();
        if (NextChar == '.')
        {
          // This is a range operator, stop number parsing
          break;
        }
        else if (NextChar != EOF && isdigit(NextChar))
        {
          // This is a decimal point followed by a digit
          if (hasDecimal)
          {
            // Second decimal point, stop parsing
            break;
          }
          hasDecimal = true;
        }
        else
        {
          // Decimal point not followed by digit, stop parsing
          break;
        }
      }
      NumberString += LastChar;
      LastChar = getchar();
    }

    NumberValue = strtod(NumberString.c_str(), 0);
    return tok_number;
  }

  // Handle string and character literals
  if (LastChar == '"' || LastChar == '\'')
  {
    char quote = LastChar;
    std::string LitValue;
    LitValue.reserve(32);
    LastChar = getchar(); // Skip opening quote

    while (LastChar != quote && LastChar != EOF)
    {
      if (LastChar == '\\')
      {
        LastChar = getchar();
        if (LastChar == EOF)
          break;
        switch (LastChar)
        {
        case 'n':
          LitValue += '\n';
          break;
        case 't':
          LitValue += '\t';
          break;
        case 'r':
          LitValue += '\r';
          break;
        case '\\':
          LitValue += '\\';
          break;
        case '"':
          LitValue += '"';
          break;
        case '\'':
          LitValue += '\'';
          break;
        case '0':
          LitValue += '\0';
          break;
        case 'a':
          LitValue += '\a';
          break;
        case 'b':
          LitValue += '\b';
          break;
        case 'f':
          LitValue += '\f';
          break;
        case 'v':
          LitValue += '\v';
          break;
        default:
          LitValue += LastChar;
          break;
        }
      }
      else
      {
        LitValue += LastChar;
      }
      LastChar = getchar();
    }
    if (LastChar == quote)
      LastChar = getchar(); // Skip closing quote

    if (LitValue.size() == 1)
    {
      CharValue = LitValue[0];
      return tok_char_literal;
    }
    StringValue = LitValue;
    return tok_string_literal;
  }

  // Operators and punctuation dispatch
  int c = LastChar;
  LastChar = getchar();

  switch (c)
  {
  case ':':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_assign_immutable;
    }
    return ':';
  case '~':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_type_coerce;
    }
    if (isalpha(LastChar))
    {
      // ~construct destructor
      std::string potential;
      potential += LastChar;
      int ch;
      while (isalnum(ch = getchar()))
      {
        potential += ch;
      }
      if (potential == "construct")
      {
        LastChar = ch;
        return tok_destruct;
      }
      ungetc(ch, stdin);
      for (int i = potential.size() - 1; i >= 0; --i)
        ungetc(potential[i], stdin);
    }
    return tok_bitwise_not;
  case '-':
    if (LastChar == '>')
    {
      LastChar = getchar();
      return tok_arrow;
    }
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_minus_assign;
    }
    if (LastChar == '-')
    {
      LastChar = getchar();
      return tok_decrement;
    }
    return '-';
  case '+':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_plus_assign;
    }
    if (LastChar == '+')
    {
      LastChar = getchar();
      return tok_increment;
    }
    return '+';
  case '*':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_multiply_assign;
    }
    return '*';
  case '/':
    if (LastChar == '/')
    {
      do
      {
        LastChar = getchar();
      } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
      return get_token();
    }
    if (LastChar == '*')
    {
      LastChar = getchar();
      while (LastChar != EOF)
      {
        if (LastChar == '*')
        {
          LastChar = getchar();
          if (LastChar == '/')
          {
            LastChar = getchar();
            return get_token();
          }
        }
        else
        {
          LastChar = getchar();
        }
      }
      return tok_eof;
    }
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_divide_assign;
    }
    return tok_union_type;
  case '%':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_modulo_assign;
    }
    return '%';
  case '=':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_equals;
    }
    return '=';
  case '!':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_not_equals;
    }
    return tok_logical_not;
  case '<':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_less_equal;
    }
    if (LastChar == '<')
    {
      LastChar = getchar();
      return tok_left_shift;
    }
    return tok_less_than;
  case '>':
    if (LastChar == '=')
    {
      LastChar = getchar();
      return tok_greater_equal;
    }
    if (LastChar == '>')
    {
      LastChar = getchar();
      return tok_right_shift;
    }
    return tok_greater_than;
  case '&':
    if (LastChar == '&')
    {
      LastChar = getchar();
      return tok_logical_and;
    }
    return tok_bitwise_and;
  case '|':
    if (LastChar == '|')
    {
      LastChar = getchar();
      return tok_logical_or;
    }
    return tok_bitwise_or;
  case '^':
    return tok_bitwise_xor;
  case '.':
    if (LastChar == '.')
    {
      LastChar = getchar();
      return tok_range;
    }
    return tok_property_access;
  case '{':
    return tok_left_brace;
  case '}':
    return tok_right_brace;
  case '$':
    return tok_dollar;
  case '[':
    return tok_lsquare;
  case ']':
    return tok_rsquare;
  case EOF:
    return tok_eof;
  default:
    return c;
  }
}
