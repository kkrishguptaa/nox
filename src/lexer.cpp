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

  // Handle multi-character operators
  if (LastChar == ':')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();        // Consume the '='
      return tok_assign_immutable; // :=
    }
    LastChar = NextChar;
    return ':';
  }

  if (LastChar == '~')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();   // Consume the '='
      return tok_type_coerce; // ~=
    }
    else if (isalpha(NextChar))
    {
      // Check if this is ~construct (destructor)
      // Read the word after ~ to see if it's "construct"
      std::string PotentialKeyword;
      PotentialKeyword += NextChar;

      int ReadChar;
      while (isalnum(ReadChar = getchar()))
      {
        PotentialKeyword += ReadChar;
      }

      if (PotentialKeyword == "construct")
      {
        LastChar = ReadChar; // Set LastChar to the character after "construct"
        return tok_destruct; // ~construct
      }
      else
      {
        // Not a destructor, put back all characters we read
        ungetc(ReadChar, stdin);
        for (int i = PotentialKeyword.length() - 1; i >= 0; i--)
        {
          ungetc(PotentialKeyword[i], stdin);
        }
        LastChar = getchar();   // Re-read the next character
        return tok_bitwise_not; // ~
      }
    }
    else
    {
      LastChar = NextChar;
      return tok_bitwise_not; // ~
    }
  }

  if (LastChar == '-')
  {
    int NextChar = getchar();
    if (NextChar == '>')
    {
      LastChar = getchar(); // Consume the '>'
      return tok_arrow;     // ->
    }
    else if (NextChar == '=')
    {
      LastChar = getchar();    // Consume the '='
      return tok_minus_assign; // -=
    }
    else if (NextChar == '-')
    {
      LastChar = getchar(); // Consume the second '-'
      return tok_decrement; // --
    }
    LastChar = NextChar;
    return '-';
  }

  if (LastChar == '+')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();   // Consume the '='
      return tok_plus_assign; // +=
    }
    else if (NextChar == '+')
    {
      LastChar = getchar(); // Consume the second '+'
      return tok_increment; // ++
    }
    LastChar = NextChar;
    return '+';
  }

  if (LastChar == '*')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();       // Consume the '='
      return tok_multiply_assign; // *=
    }
    LastChar = NextChar;
    return '*';
  }

  if (LastChar == '/')
  {
    int NextChar = getchar();
    if (NextChar == '/')
    {
      // Single-line comment, skip until end of line
      do
      {
        LastChar = getchar();
      } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

      if (LastChar != EOF)
        return get_token(); // Recursively get next token
      else
        return tok_eof; // Reached EOF while in comment
    }
    else if (NextChar == '*')
    {
      // Multi-line comment, skip until */
      LastChar = getchar(); // Skip '*'
      while (LastChar != EOF)
      {
        if (LastChar == '*')
        {
          LastChar = getchar();
          if (LastChar == '/')
          {
            LastChar = getchar(); // Skip '/'
            return get_token();   // Recursively get next token
          }
        }
        else
        {
          LastChar = getchar();
        }
      }
      // If we reach here, comment was not properly closed but we reached EOF
      return tok_eof;
    }
    else if (NextChar == '=')
    {
      LastChar = getchar();     // Consume the '='
      return tok_divide_assign; // /=
    }
    else
    {
      LastChar = NextChar;
      return tok_union_type; // / for union types like float/int
    }
  }

  if (LastChar == '%')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();     // Consume the '='
      return tok_modulo_assign; // %=
    }
    LastChar = NextChar;
    return '%';
  }

  if (LastChar == '=')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar(); // Consume the second '='
      return tok_equals;    // ==
    }
    LastChar = NextChar;
    return '=';
  }

  if (LastChar == '!')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();  // Consume the '='
      return tok_not_equals; // !=
    }
    LastChar = NextChar;
    return tok_logical_not; // !
  }

  if (LastChar == '<')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();  // Consume the '='
      return tok_less_equal; // <=
    }
    else if (NextChar == '<')
    {
      LastChar = getchar();  // Consume the second '<'
      return tok_left_shift; // <<
    }
    LastChar = NextChar;
    return tok_less_than; // <
  }

  if (LastChar == '>')
  {
    int NextChar = getchar();
    if (NextChar == '=')
    {
      LastChar = getchar();     // Consume the '='
      return tok_greater_equal; // >=
    }
    else if (NextChar == '>')
    {
      LastChar = getchar();   // Consume the second '>'
      return tok_right_shift; // >>
    }
    LastChar = NextChar;
    return tok_greater_than; // >
  }

  if (LastChar == '&')
  {
    int NextChar = getchar();
    if (NextChar == '&')
    {
      LastChar = getchar();   // Consume the second '&'
      return tok_logical_and; // &&
    }
    LastChar = NextChar;
    return tok_bitwise_and; // &
  }

  if (LastChar == '|')
  {
    int NextChar = getchar();
    if (NextChar == '|')
    {
      LastChar = getchar();  // Consume the second '|'
      return tok_logical_or; // ||
    }
    LastChar = NextChar;
    return tok_bitwise_or; // |
  }

  if (LastChar == '^')
  {
    LastChar = getchar();
    return tok_bitwise_xor; // ^
  }

  // Handle range operator and property access
  if (LastChar == '.')
  {
    int NextChar = getchar();
    if (NextChar == '.')
    {
      LastChar = getchar(); // Consume the second '.'
      return tok_range;     // ..
    }
    LastChar = NextChar;
    return tok_property_access; // .
  }

  // Handle object literals and blocks
  if (LastChar == '{')
  {
    LastChar = getchar();
    return tok_left_brace; // {
  }

  if (LastChar == '}')
  {
    LastChar = getchar();
    return tok_right_brace; // }
  }

  // Handle class property access
  if (LastChar == '$')
  {
    LastChar = getchar();
    return tok_dollar; // $
  }

  // Handle array notation
  if (LastChar == '[')
  {
    LastChar = getchar();
    return '[';
  }

  if (LastChar == ']')
  {
    LastChar = getchar();
    return ']';
  }

  // Handle EOF
  if (LastChar == EOF)
    return tok_eof;

  // Otherwise, just return the character as is (operators, punctuation, etc.)
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}
