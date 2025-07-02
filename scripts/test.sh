#!/bin/bash
set -e

dir=$(dirname "$0")
root="$dir/.."
build="$root/build"

sh "$root/scripts/build.sh"

echo "🧪 Running tests..."
cd "$build"
ctest --output-on-failure
