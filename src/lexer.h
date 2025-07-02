#pragma once
#include <string>

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token
{
  tok_eof = -1,        // End of file
  tok_identifier = -2, // Variable/function names

  // Signed integer types
  tok_int8 = -3,  // int8 type (8-bit signed)
  tok_int16 = -4, // int16 type (16-bit signed)
  tok_int32 = -5, // int32 type (32-bit signed, also default for 'int')
  tok_int64 = -6, // int64 type (64-bit signed)

  // Unsigned integer types
  tok_uint8 = -7,   // uint8 type (8-bit unsigned)
  tok_uint16 = -8,  // uint16 type (16-bit unsigned)
  tok_uint32 = -9,  // uint32 type (32-bit unsigned, also default for 'uint')
  tok_uint64 = -10, // uint64 type (64-bit unsigned)

  // Floating point types
  tok_float32 = -11, // float32 type (32-bit floating point, also default for 'float')
  tok_float64 = -12, // float64 type (64-bit floating point)

  tok_string = -13,         // string type
  tok_boolean = -14,        // bool type
  tok_byte = -15,           // byte type
  tok_character = -16,      // char type
  tok_void = -17,           // void type
  tok_null = -18,           // null keyword
  tok_number = -19,         // Number literal (e.g., 42, 3.14)
  tok_string_literal = -20, // String literal (e.g., "hello", "A")
  tok_true = -21,           // Boolean true literal
  tok_false = -22,          // Boolean false literal
  tok_char_literal = -23,   // Character literal (e.g., 'A', '\n')

  // loops
  tok_for = -24,      // for loop keyword
  tok_while = -25,    // while loop keyword
  tok_do = -26,       // do-while loop keyword
  tok_continue = -27, // continue statement
  tok_break = -28,    // break statement

  // conditionals
  tok_if = -29,      // if statement
  tok_else = -30,    // else statement
  tok_switch = -31,  // switch statement
  tok_case = -32,    // case in switch
  tok_default = -33, // default case in switch

  // functions
  tok_function = -34, // fn keyword for function definition
  tok_return = -35,   // return statement
  tok_async = -36,    // async keyword
  tok_await = -37,    // await keyword
  tok_throw = -38,    // throw statement

  // collection types
  tok_map = -39,      // Map type (key-value pairs)
  tok_set_type = -40, // Set type (unique values)

  // object-oriented
  tok_class = -41,     // Class definition keyword
  tok_construct = -42, // Constructor keyword
  tok_destruct = -43,  // Destructor keyword (~construct)
  tok_extends = -44,   // Inheritance keyword
  tok_this = -45,      // This reference keyword
  tok_super = -46,     // Super reference keyword
  tok_private = -47,   // Private access modifier
  tok_protected = -48, // Protected access modifier
  tok_public = -49,    // Public access modifier (default)
  tok_static = -50,    // Static modifier
  tok_get = -51,       // Getter method keyword
  tok_set = -52,       // Setter method keyword

  // advanced features
  tok_enum = -53,    // Enum definition keyword
  tok_promise = -54, // Promise type keyword
  tok_in = -55,      // in operator keyword
  tok_type = -56,    // type keyword for generics

  // import/export
  tok_import = -57, // Import statement
  tok_export = -58, // Export statement
  tok_from = -59,   // From keyword in import

  // operators and punctuation
  tok_assign_immutable = -60, // := immutable assignment operator
  tok_type_coerce = -61,      // ~= type coercion operator
  tok_arrow = -62,            // -> arrow operator (function return type)
  tok_range = -63,            // .. range operator (inclusive)
  tok_property_access = -64,  // . property access operator
  tok_union_type = -65,       // / union type operator

  // object and generic syntax
  tok_left_brace = -66,   // { left brace for objects/blocks
  tok_right_brace = -67,  // } right brace for objects/blocks
  tok_less_than = -68,    // < for generics and comparison
  tok_greater_than = -69, // > for generics and comparison
  tok_dollar = -70,       // $ for class property access
  tok_lsquare = -91,      // [ left bracket for arrays
  tok_rsquare = -92,      // ] right bracket for arrays

  // arithmetic operators
  tok_plus_assign = -71,     // += addition assignment
  tok_minus_assign = -72,    // -= subtraction assignment
  tok_multiply_assign = -73, // *= multiplication assignment
  tok_divide_assign = -74,   // /= division assignment
  tok_modulo_assign = -75,   // %= modulo assignment
  tok_increment = -76,       // ++ increment operator
  tok_decrement = -77,       // -- decrement operator

  // comparison operators
  tok_equals = -78,        // == equality operator
  tok_not_equals = -79,    // != inequality operator
  tok_less_equal = -80,    // <= less than or equal
  tok_greater_equal = -81, // >= greater than or equal

  // logical operators
  tok_logical_and = -82, // && logical AND
  tok_logical_or = -83,  // || logical OR
  tok_logical_not = -84, // ! logical NOT

  // bitwise operators
  tok_bitwise_and = -85, // & bitwise AND
  tok_bitwise_or = -86,  // | bitwise OR
  tok_bitwise_xor = -87, // ^ bitwise XOR
  tok_bitwise_not = -88, // ~ bitwise NOT (complement)
  tok_left_shift = -89,  // << left shift
  tok_right_shift = -90, // >> right shift
};

// Keyword lookup table for better performance
static std::unordered_map<std::string, int> keywords = {
    // Data types
    {"int", tok_int32},
    {"uint", tok_uint32},
    {"int8", tok_int8},
    {"int16", tok_int16},
    {"int32", tok_int32},
    {"int64", tok_int64},
    {"uint8", tok_uint8},
    {"uint16", tok_uint16},
    {"uint32", tok_uint32},
    {"uint64", tok_uint64},
    {"float", tok_float32},
    {"float32", tok_float32},
    {"float64", tok_float64},
    {"string", tok_string},
    {"bool", tok_boolean},
    {"byte", tok_byte},
    {"char", tok_character},
    {"void", tok_void},
    {"null", tok_null},

    // Boolean literals
    {"true", tok_true},
    {"false", tok_false},

    // Collection types
    {"map", tok_map},
    {"set", tok_set_type},

    // Object-oriented keywords
    {"class", tok_class},
    {"construct", tok_construct},
    {"extends", tok_extends},
    {"this", tok_this},
    {"super", tok_super},
    {"private", tok_private},
    {"protected", tok_protected},
    {"public", tok_public},
    {"static", tok_static},
    {"get", tok_get},
    {"set", tok_set},

    // Advanced features
    {"enum", tok_enum},
    {"Promise", tok_promise},
    {"in", tok_in},
    {"type", tok_type},

    // Import/Export
    {"import", tok_import},
    {"export", tok_export},
    {"from", tok_from},

    // Loops
    {"for", tok_for},
    {"while", tok_while},
    {"do", tok_do},
    {"continue", tok_continue},
    {"break", tok_break},

    // Conditionals
    {"if", tok_if},
    {"else", tok_else},
    {"switch", tok_switch},
    {"case", tok_case},
    {"default", tok_default},

    // Functions
    {"fn", tok_function},
    {"return", tok_return},
    {"async", tok_async},
    {"await", tok_await},
    {"throw", tok_throw}};

// Lexer output state exposed for testing
extern std::string IdentifierString;
extern std::string StringValue;
extern double NumberValue;
extern bool BooleanValue;
extern char CharValue;

// Lexing function
extern int get_token();
