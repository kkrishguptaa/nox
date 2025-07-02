# Nox Programming Language

Nox is a statically typed object-oriented programming language designed for simplicity and performance. It features a clean syntax, strong type system, and powerful concurrency support.

> ⚠️ **Work in Progress**: This language is currently under development. The syntax and features described below are planned and may change in future versions.

## Table of Contents

- [Language Features](#language-features)
- [Syntax Overview](#syntax-overview)
- [Comments](#comments)
- [Variables and Constants](#variables-and-constants)
- [Data Types](#data-types)
- [Classes and Objects](#classes-and-objects)
- [Functions](#functions)
- [Control Flow](#control-flow)
- [Modules and Imports](#modules-and-imports)

## Language Features

- **Strict Static Typing**: Variables must be declared with types, ensuring complete type safety at compile time with no nullable types
- **Object-Oriented**: Full support for classes, inheritance, and encapsulation
- **Memory Safe**: Automatic memory management with garbage collection
- **Concurrency**: Built-in async/await support for concurrent programming
- **Clean Syntax**: Inspired by modern languages with readable, intuitive syntax

## Syntax Overview

### Comments

Nox supports both single-line and multi-line comments:

```nox
// This is a single-line comment
// Use these for brief explanations or notes

/*
   This is a multi-line comment
   Useful for longer descriptions or
   temporarily disabling code blocks
*/
```

### Variables and Constants

Nox distinguishes between mutable variables and immutable constants:

```nox
// Immutable/Constant variable - cannot be reassigned after initialization
// The `:=` operator creates a constant with type inference
x := 10         // x is inferred as int and cannot be changed
name := "Nox"   // name is inferred as string and cannot be changed

// Mutable variable - can be reassigned
// Explicit type declaration with assignment operator `=`
int y = 20       // y is a mutable integer
y = 25           // Valid: y can be reassigned

// Multiple variable declaration in one line
int a, b = 30, 40    // Declares two integers: a=30, b=40
string title = "Nox" // String variable with explicit type
```

**Key Points:**

- `:=` creates immutable variables (constants) with type inference
- `=` creates mutable variables with explicit type declaration
- Multiple variables can be declared and initialized in one statement

### Data Types

Nox provides a rich type system with primitive types, collections, and user-defined types:

#### Primitive Types

```nox
// Numeric types with explicit bit widths
int8 a = 127           // 8-bit signed integer (-128 to 127)
int16 b = 32767        // 16-bit signed integer (-32,768 to 32,767)
int32 c = 2147483647   // 32-bit signed integer (-2^31 to 2^31-1)
int64 d = 9223372036854775807  // 64-bit signed integer (-2^63 to 2^63-1)

uint8 e = 255          // 8-bit unsigned integer (0 to 255)
uint16 f = 65535       // 16-bit unsigned integer (0 to 65,535)
uint32 g = 4294967295  // 32-bit unsigned integer (0 to 2^32-1)
uint64 h = 18446744073709551615  // 64-bit unsigned integer (0 to 2^64-1)

// Default numeric types (equivalent to 32-bit versions)
int i = 5              // Default signed integer (same as int32)
uint j = 10            // Default unsigned integer (same as uint32)

// Floating-point types
float k = 3.14         // Default floating-point (same as float32)
float32 l = 3.14       // 32-bit floating-point number
float64 m = 2.71828    // 64-bit double-precision floating-point

// Character and text types
char n = 'A'           // Single character (Unicode) using single quotes
char m = "B"         // Single character using double quotes
string o = "Hello"     // UTF-8 string of characters using double quotes
string p = 'World'     // UTF-8 string of characters using single quotes
```

#### Collection Types

```nox
// Arrays - ordered collections of elements of the same type
// Note: There is no 'array' keyword - use type[] syntax
int[] numbers = [1, 2, 3, 4, 5]           // Dynamic array
int[5] fixedNumbers = [1, 2, 3, 4, 5]     // Fixed-size array with 5 elements

// Multi-dimensional arrays
int[][] matrix = [[1, 2], [3, 4]]         // 2D dynamic array
int[3][3] grid = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]  // Fixed 3x3 matrix

// Maps (Dictionaries) - key-value pairs
map[string, int] ages = {               // Map with string keys and int values
  "Krish": 16, // Yes, I was this years old when I made nox.
  "Owlman": 30,
  "Catgirl": 35
}

// Sets - unique collections without duplicates
set[int] uniqueNumbers = {1, 2, 3, 2, 1}  // Results in {1, 2, 3}
set[string] colors = {"red", "green", "blue"}

// Tuples - fixed-size collections with defined types for each position
// Note: Tuples are arrays with defined length and specific types per element
[string, int, bool] person = ["Alice", 25, true]  // Name, age, active status
[float64, float64] point = [3.14, 2.71]           // 2D coordinate point
```

#### Enumerations

```nox
// Enums define a set of named constants
enum Color {
  RED,     // Automatically assigned value 0
  GREEN,   // Automatically assigned value 1
  BLUE     // Automatically assigned value 2
}

// Enums with explicit values
enum Status {
  PENDING = 0,
  ACTIVE = 1,
  INACTIVE = 2,
  DELETED = 99
}

// Using enum values
Color favorite = Color.RED
Status userStatus = Status.ACTIVE

// Enums in switch statements
switch (favorite) {
  case Color.RED:
    print("You like red!")
    break
  case Color.GREEN:
    print("Green is nice!")
    break
  case Color.BLUE:
    print("Blue is cool!")
    break
}
```

#### Generic Types

```nox
// Generic functions
fn identity<T>(T value) -> T {
  return value
}

// Generic classes
class Container<T> {
  T value

  construct(T initialValue) {
    $value = initialValue
  }

  fn getValue() -> T {
    return $value
  }

  fn setValue(T newValue) -> void {
    $value = newValue
  }
}

// Using generics
string text = identity<string>("Hello")
int number = identity<int>(42)

Container<string> stringContainer = Container<string>("Hello")
Container<int> intContainer = Container<int>(100)
```

#### Type Coercion

```nox
// Explicit type conversion using the coercion operator `~=`
int num = 10
float f ~= num      // Convert int to float: f becomes 10.0
string str ~= num   // Convert int to string: str becomes "10"
bool flag ~= num    // Convert int to bool: flag becomes true (non-zero)

// Type coercion is explicit and safe - no implicit conversions
```

**Important Notes:**

- All variables must be explicitly typed or use type inference
- Arrays can be dynamic `type[]` or fixed-size `type[size]`
- Maps require both key and value types to be specified
- Sets automatically handle uniqueness - duplicates are ignored
- Type coercion is explicit using `~=` to prevent accidental conversions

### Classes and Objects

Nox supports full object-oriented programming with classes, inheritance, polymorphism and encapsulation:

#### Basic Class Definition

```nox
// Define a class with properties and methods
class Person {
  // Class properties (fields)
  string name     // Public property by default
  int age         // Public property by default

  construct(string name, int age) {
    $name = name  // Use $ to refer to class properties
    $age = age
  }

  ~construct() {
    // Destructor - called when object is no longer needed
    print("Person " + $name + " is being destroyed")
  }

  get name() -> string {
    return $name  // Getter method for name
  }

  set name(string newName) -> void {
    $name = newName  // Setter method for name
  }

  // Instance method
  fn greet() -> void {
    print("Hello, my name is " + $name)
  }

  // Method with return value
  fn getAgeInMonths() -> int {
    return $age * 12
  }
}

// Creating instances
Person alice = Person("Alice", 25)  // Call constructor
alice.greet()                       // Call method: "Hello, my name is Alice"
int months = alice.getAgeInMonths() // Get age in months: 300
```

#### Classes Without Constructors

```nox
// Classes can have default values and be created with object literal syntax
class Animal {
  string species = "cat"    // Default value
  string sound = "meow"     // Default value

  fn speak() -> void {
    print("The " + $species + " says " + $sound)
  }
}

// Creating instances with default values
Animal cat = Animal()                           // Uses all defaults
Animal dog = Animal({ species: "dog", sound: "woof" })  // Override specific properties

cat.speak()  // Output: "The cat says meow"
dog.speak()  // Output: "The dog says woof"
```

#### Required vs Optional Properties

```nox
class Car {
  string make = "Toyota"    // Optional: has default value
  string model              // Required: no default value
  int year = 2024          // Optional: has default value
  string color             // Required: no default value
  engine := "Y6" // Cannot be changed ever, is a static property
}

// Valid instantiations
Car car1 = Car({ model: "Corolla", color: "red" })           // Provide required fields
Car car2 = Car({ model: "Camry", color: "blue", year: 2023 }) // Override optional field

// Invalid - missing required fields
// Car car3 = Car()  // Error: model and color are required
```

#### Inheritance and Access Modifiers

```nox
class Vehicle {
  protected string engineType = "V6"    // Protected: accessible by subclasses
  private int serialNumber = 12345      // Private: only accessible within this class
  string brand = "Generic"       // Public: accessible everywhere (default)

  // Static properties belong to the all instances of the class, it is same for all instances
  totalVehicles := 0

  construct(string brand) {
    $brand = brand
    Vehicle.totalVehicles += 1  // Access static property
  }

  // Protected method
  protected fn startEngine() void {
    print("Engine starting...")
  }

  // Public method
  fn getInfo() string {
    return $brand + " vehicle"
  }
}

// Inheritance using 'extends' keyword
class ToyotaCar extends Vehicle {
  string model             // Additional property
  string color = "white"   // Property with default

  construct(string model, string color) {
    super("Toyota")        // Call parent constructor
    $model = model
    $color = color
  }

  // Override parent method
  fn getInfo() -> string {
    return $brand + " " + $model + " (" + $color + ")"
  }

  // Use protected method from parent
  fn start() -> void {
    $startEngine()     // Can access protected method
    print($model + " is ready to drive")
  }
}

// Using inheritance
ToyotaCar myCar = ToyotaCar("Prius", "blue")
myCar.start()    // Output: "Engine starting..." then "Prius is ready to drive"
print(myCar.getInfo())  // Output: "Toyota Prius (blue)"
```

#### Access Modifiers Summary

- **`default`**: You do not need to mark this syntactically. Accessible everywhere (public)
- **`protected`**: Accessible within the class and its subclasses
- **`private`**: Accessible only within the defining class

#### Key Concepts

- **Constructor**: Special method `construct()` called when creating instances
- **Destructor**: Special method `~construct()` called when an object is destroyed
- **`this`**: Reference to the current instance
- **`super()`**: Call parent class constructor
- **Inheritance**: Use `extends` to create subclasses
- **Method Overriding**: Subclasses can redefine parent methods
- **Static Members**: Shared across all instances of a class

### Functions

Functions in Nox are defined using the `fn` keyword and support various features:

#### Basic Function Definition

```nox
// Function with parameters and return type
fn add(int a, int b) -> int {
  return a + b
}

// Function without return value (void)
fn greet(string name) -> void {
  print("Hello, " + name + "!")
}

// Calling functions
int result = add(5, 10)  // result = 15
greet("Alice")           // Output: "Hello, Alice"
```

#### Default Parameters

```nox
// Functions can have default parameter values
fn createUser(string name, int age = 18, bool active = true) -> void {
  print("User: " + name + ", Age: " + age + ", Active: " + active)
}

// Different ways to call with defaults
createUser("Bob")                    // Uses defaults: age=18, active=true
createUser("Carol", 25)              // Override age, use default active=true
createUser("Dave", 30, false)        // Override both age and active
```

#### Function Overloading / Polymorphism

This also works in classes, but here is a simple example of function overloading:

```nox
// Multiple functions with same name but different parameters
fn calculate(int a, int b) -> int {
  return a + b
}

fn calculate(float32 a, float32 b) -> float32 {
  return a + b
}

fn calculate(string a, string b) -> string {
  return a + " " + b
}

// The compiler chooses the right function based on parameter types
int intResult = calculate(5, 10)           // Calls int version
float32 floatResult = calculate(3.14, 2.86)  // Calls float32 version
string stringResult = calculate("Hello", "World")  // Calls string version
```

#### Higher-Order Functions

```nox
// Functions can take other functions as parameters
// Function type syntax: fn(paramTypes) -> returnType
fn applyOperation(int a, int b, fn(int, int) -> int operation) -> int {
  return operation(a, b)
}

// Define operation functions
fn multiply(int x, int y) -> int {
  return x * y
}

fn subtract(int x, int y) -> int {
  return x - y
}

// Use higher-order function
int product = applyOperation(6, 4, multiply)   // result = 24
int difference = applyOperation(10, 3, subtract)  // result = 7

// Function variables
fn(int, int) -> int mathOp = add  // Store function in variable
int result = mathOp(5, 3)         // Call stored function
```

#### Async Functions and Concurrency

```nox
// Async function that can be awaited
async fn fetchData(string url) -> string {
  // Simulate network request
  await delay(1000)  // Wait 1 second
  return "Data from " + url
}

// Function that uses async operations
async fn processMultipleUrls() -> void {
  // Await async function
  string data1 = await fetchData("https://api1.com")
  string data2 = await fetchData("https://api2.com")

  print("Received: " + data1)
  print("Received: " + data2)
}

// Concurrent execution
async fn processUrlsConcurrently() -> void {
  // Start both operations concurrently
  Promise[string] promise1 = fetchData("https://api1.com")
  Promise[string] promise2 = fetchData("https://api2.com")

  // Wait for both to complete
  string data1 = await promise1
  string data2 = await promise2

  print("All data received concurrently")
}
```

#### Function Types and Arrow Operator

The `->` operator is used to define function types and lambda expressions:

#### Function Type Declarations

```nox
// Function type syntax: fn(parameterTypes) -> returnType
fn(int, int) -> int mathOperation = add     // Variable that holds a function
fn(string) -> void logger = print           // Function variable for logging
fn() -> string generator = getText          // Function with no parameters

// Using function type variables
result := mathOperation(5, 3)               // Call stored function
logger("Hello World")                       // Call logging function
text := generator()                         // Call generator function
```

#### Function Parameters with Types

```nox
// Functions that accept other functions as parameters
fn processData(int[] data, fn(int) -> int processor) int[] {
  result := []
  for (item in data) {
    result.append(processor(item))
  }
  return result
}

// Lambda expressions using arrow operator
doubled := processData([1, 2, 3], (int x) -> x * 2)        // [2, 4, 6]
squared := processData([1, 2, 3], (int x) -> x * x)        // [1, 4, 9]
```

#### Return Type Annotations

```nox
// Explicit return type using arrow operator (alternative syntax)
fn calculateArea(float radius) -> float {
  return 3.14159 * radius * radius
}

// Multiple return types (tuples)
fn divideWithRemainder(int dividend, int divisor) -> [int, int] {
  quotient := dividend / divisor
  remainder := dividend % divisor
  return [quotient, remainder]
}
```

#### Multiple Return Types

```nox
// Functions can have multiple return types
fn getSomething() -> float/int {
  if (someCondition) {
    return 3.14 // Returns float
  } else {
    return 42   // Returns int
  }
}

// Using the function with multiple return types
result := getSomething()

switch (type(result)) {
  case float:
    print("Received a float: " + result)
    break
  case int:
    print("Received an int: " + result)
    break
}
```

#### Higher-Order Function Examples

```nox
// Function that returns a function
fn createMultiplier(int factor) -> fn(int) -> int {
  return (int x) -> x * factor
}

// Using the function factory
double := createMultiplier(2)      // Returns a function that doubles
triple := createMultiplier(3)      // Returns a function that triples

result1 := double(5)               // 10
result2 := triple(4)               // 12
```

#### Async Function Types

```nox
// Async function types
fn(string) -> Promise[string] asyncFetcher = fetchData
fn() -> Promise[void] asyncTask = processInBackground

// Using async function types
data := await asyncFetcher("https://api.example.com")
await asyncTask()
```

**Key Points about the `->` operator:**

- **Function Types**: Defines the signature of function variables and parameters
- **Lambda Expressions**: Creates anonymous functions with explicit return types
- **Return Annotations**: Alternative syntax for specifying function return types
- **Type Safety**: Ensures function signatures match at compile time
- **Higher-Order Functions**: Enables functions that work with other functions
- **Async Support**: Works with Promise types for asynchronous operations

### Control Flow

Nox provides standard control flow constructs for decision making and iteration:

#### Conditional Statements

```nox
// Basic if statement
int age = 20
if (age >= 18) {
  print("You are an adult")
}

// If-else statement
if (age >= 65) {
  print("Senior citizen")
} else if (age >= 18) {
  print("Adult")
} else {
  print("Minor")
}


// Switch statement for multiple conditions

enum Grade {
  A, B, C, D, F
}

string grade = Grade.A

switch (grade) {
  case Grade.A:
    print("Excellent!")
    break
  case Grade.B:
    print("Good job!")
    break
  case Grade.C:
    print("Average")
    break
  default:
    print("Needs improvement")
}
```

#### Loops

```nox
// For loop with range
for (int i = 0; i < 10; i++) {
  print("Count: " + i)
}

// For-each loop for collections
int[] numbers = [1, 2, 3, 4, 5]
for (int num in numbers) {
  print("Number: " + num)
}

// While loop
int count = 0
while (count < 5) {
  print("Count: " + count)
  count++
}

// Do-while loop (executes at least once)
int input
do {
  input = readUserInput()
  print("You entered: " + input)
} while (input != 0)
```

#### Loop Control

```nox
// Break and continue in loops
for (int i = 0; i < 10; i++) {
  if (i == 3) {
    continue  // Skip iteration when i equals 3
  }
  if (i == 7) {
    break     // Exit loop when i equals 7
  }
  print("i = " + i)  // Prints: 0, 1, 2, 4, 5, 6
}
```

### Modules and Imports

Nox supports modular programming through import/export statements:

#### Exporting from a Module

```nox
// math.nox - A math utility module

// Export individual functions and classes
export fn add(int a, int b) int {
  return a + b
}

export fn multiply(int a, int b) int {
  return a * b
}

export class Calculator {
  fn calculate(string operation, int a, int b) int {
    switch (operation) {
      case "add": return add(a, b)
      case "multiply": return multiply(a, b)
      default: return 0
    }
  }
}

// Export constants
export int PI_APPROXIMATION = 3

// Alternative export syntax - export at the end
fn subtract(int a, int b) int {
  return a - b
}

fn divide(int a, int b) float {
  return a / b
}

// Export multiple items
export {
  subtract,
  divide,
  PI_APPROXIMATION
}
```

#### Importing Modules

```nox
// main.nox - Using the math module

// Import specific functions and classes
import {
  add,
  multiply,
  Calculator
} from "math.nox"

// Import with alias to avoid naming conflicts
import {
  subtract as mathSubtract,
  divide as mathDivide
} from "math.nox"

// Import everything from a module
import * as MathUtils from "math.nox"

// Using imported functions
int sum = add(5, 10)                    // Direct use
int product = multiply(3, 4)            // Direct use
int difference = mathSubtract(10, 3)    // Using alias

// Using imported classes
Calculator calc = Calculator()
int result = calc.calculate("add", 8, 2)

// Using namespace import
int quotient = MathUtils.divide(10, 2)
```

#### Module Organization

```nox
// Standard library imports (hypothetical)
import {
  HttpClient,
  JsonParser
} from "std:http"

import {
  FileSystem,
  Path
} from "std:io"

// Local module imports
import { DatabaseConnection } from "./database/connection.nox"
import { UserModel } from "./models/user.nox"

// Third-party package imports (hypothetical package manager)
import { Logger } from "pkg:logging"
import { Validator } from "pkg:validation"
```

#### Export Types

- **Named Exports**: Export specific functions, classes, or variables by name
- **Default Exports**: Each module can have one default export
- **Re-exports**: Modules can export items from other modules
- **Namespace Exports**: Import entire module under a namespace

**Key Points:**

- Modules help organize code into reusable components
- Use explicit imports to control what enters your namespace
- Aliases help avoid naming conflicts
- Circular dependencies should be avoided
- Module paths can be relative (`./path`) or absolute (`pkg:name`)

### Operators and Expressions

Nox provides a comprehensive set of operators for various operations:

#### Arithmetic Operators

```nox
// Basic arithmetic
a := 10 + 5    // Addition: 15
b := 20 - 8    // Subtraction: 12
c := 6 * 7     // Multiplication: 42
d := 15 / 3    // Division: 5
e := 17 % 5    // Modulo: 2

// Compound assignment operators
int x = 10
x += 5    // x = x + 5, result: 15
x -= 3    // x = x - 3, result: 12
x *= 2    // x = x * 2, result: 24
x /= 4    // x = x / 4, result: 6
x %= 4    // x = x % 4, result: 2

// Increment and decrement
int i = 5
i++       // Post-increment: expression value is 6, then i becomes 7
i--       // Post-decrement: expression value is 6, then i becomes 5
```

#### Comparison Operators

```nox
a := 10
b := 20

bool equal = (a == b)        // Equality: false
bool notEqual = (a != b)     // Inequality: true
bool less = (a < b)          // Less than: true
bool lessEqual = (a <= b)    // Less than or equal: true
bool greater = (a > b)       // Greater than: false
bool greaterEqual = (a >= b) // Greater than or equal: false
```

#### Logical Operators

```nox
bool p = true
bool q = false

bool andResult = p && q      // Logical AND: false
bool orResult = p || q       // Logical OR: true
bool notResult = !p          // Logical NOT: false

// Short-circuit evaluation
bool result = (a > 0) && (b / a > 5)  // b/a only evaluated if a > 0
```

#### Bitwise Operators

```nox
int a = 12    // Binary: 1100
int b = 10    // Binary: 1010

int bitwiseAnd = a & b      // Bitwise AND: 8 (1000)
int bitwiseOr = a | b       // Bitwise OR: 14 (1110)
int bitwiseXor = a ^ b      // Bitwise XOR: 6 (0110)
int bitwiseNot = ~a         // Bitwise NOT: -13 (two's complement)

// Bit shifting
int leftShift = a << 2      // Left shift: 48 (110000)
int rightShift = a >> 1     // Right shift: 6 (0110)
```

#### Assignment Operators

```nox
// Basic assignment
int x = 42              // Mutable assignment
y := 42                 // Immutable assignment (type inferred)

// Type coercion assignment
int num = 10
float f ~= num          // Type coercion: f becomes 10.0
string str ~= num       // Type coercion: str becomes "10"
```

#### Special Operators

```nox
// Range operator
range := 1..10     // Range from 1 to 10 (inclusive)

// Arrow operator for function types
fn(int, int) -> int mathOperation = add

// Type coercion assignment
int num = 10
float f ~= num          // Type coercion: f becomes 10.0
string str ~= num       // Type coercion: str becomes "10"

// `in` operator for membership testing
int[] arr = [1, 2, 3, 4, 5]
bool contains = 3 in arr   // Checks if 3 is in the array: true

map[string, int] ages = { "Alice": 30, "Bob": 25 }
bool hasAlice = "Alice" in ages  // Checks if "Alice" is a key
```

#### Operator Precedence (highest to lowest)

1. **Primary**: `()` `[]` `.`
2. **Unary**: `!` `~` `++` `--` `+` `-` (unary)
3. **Multiplicative**: `*` `/` `%`
4. **Additive**: `+` `-`
5. **Shift**: `<<` `>>`
6. **Relational**: `<` `<=` `>` `>=`
7. **Equality**: `==` `!=`
8. **Bitwise AND**: `&`
9. **Bitwise XOR**: `^`
10. **Bitwise OR**: `|`
11. **Logical AND**: `&&`
12. **Logical OR**: `||`
13. **Assignment**: `=` `+=` `-=` `*=` `/=` `%=` `:=` `~=`

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Contact

- **Author**: Krishna Gupta
- **GitHub**: [@kkrishguptaa](https://github.com/kkrishguptaa)
- **Repository**: [nox](https://github.com/kkrishguptaa/nox)

---

**Note**: This is an educational project exploring programming language design and implementation. The syntax and features are subject to change as development progresses.
