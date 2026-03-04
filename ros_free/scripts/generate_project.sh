#!/usr/bin/env bash
set -euo pipefail

# Generate local CMake project files for ros_free.
# Usage:
#   ./scripts/generate_project.sh [build_dir]
# Example:
#   ./scripts/generate_project.sh build

BUILD_DIR="${1:-build}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

cmake -S "${ROOT_DIR}" -B "${ROOT_DIR}/${BUILD_DIR}" \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo "[ok] project files generated in: ${ROOT_DIR}/${BUILD_DIR}"
echo "[ok] compile commands: ${ROOT_DIR}/${BUILD_DIR}/compile_commands.json"
