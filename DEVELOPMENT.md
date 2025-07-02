# Development

## Setting Up the Development Environment

To set up the development environment for the project, follow these steps:

1. **Clone the Repository**:
   Clone the repository to your local machine using Git.

   ```sh
   git clone https://github.com/kkrishguptaa/nox.git
    cd nox
    ```

2. **Install LLVM Clang**:
    Ensure you have LLVM Clang installed on your machine. You can install it using a package manager like `apt`, `brew`, or download it from the [LLVM website](https://llvm.org/).

    For example, on macOS, you can use Homebrew:

    ```sh
    brew install llvm
    ```

3. **Install Bazel**:
    Ensure you have Bazel installed on your machine. You can download it from the [Bazel website](https://bazel.build/).

    For example, on macOS, you can use Homebrew:

    ```sh
    brew install bazel
    ```

    Then, make sure to get VSCode to recognize the Bazel paths:

    ```sh
    bazel run @hedron_compile_commands//:refresh_all
    ```

4. **Develop!!!**:
    You can now start developing the project.
