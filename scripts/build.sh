#!/bin/bash
set -e

dir=$(dirname "$0")
root="$dir/.."
build="$root/build"

echo "🧹 Cleaning previous build..."
rm -rf "$build"

echo "⚙️  Configuring project with CMake..."
cmake -S "$root" -B "$build" -G Ninja

echo "🔨 Building project..."
cmake --build "$build"

echo "✅ Build completed."

echo "🧪 Running tests..."
cd "$build"
ctest --output-on-failure
