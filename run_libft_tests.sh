#!/usr/bin/env bash
# Run from inside your Libft source directory, or place this script there.
# bash run_libft_tests.sh [--mandatory] [--no-wrap] [--verbose]
set -euo pipefail
cd "$(dirname "$0")"
TEST="test_libft_all.c"
if [[ ! -f "$TEST" || ! -f libft.h ]]; then
  echo 'Put test_libft_all.c and run_libft_tests.sh in the same folder as libft.h and ft_*.c'
  exit 1
fi
FLAGS=(-Wall -Wextra -Werror -g -fno-omit-frame-pointer -fsanitize=address,undefined -I.)
LINKFLAGS=()
TESTFLAGS=()
VERBOSE=()
for arg in "$@"; do
  case "$arg" in
    --mandatory) TESTFLAGS+=(-DLIBFT_NO_BONUS) ;;
    --no-wrap) ;;
    --verbose) VERBOSE+=(--verbose) ;;
    *) echo "Unknown argument: $arg"; exit 1 ;;
  esac
done
if [[ " $* " != *" --no-wrap "* ]]; then
  TESTFLAGS+=(-DTEST_WRAP_MALLOC)
  LINKFLAGS+=(-Wl,--wrap=malloc)
fi
shopt -s nullglob
SOURCES=(ft_*.c)
if (( ${#SOURCES[@]} == 0 )); then
  echo 'No ft_*.c files found'; exit 1
fi
printf 'Compiling %d Libft source files...\n' "${#SOURCES[@]}"
cc "${FLAGS[@]}" "${TESTFLAGS[@]}" "$TEST" "${SOURCES[@]}" "${LINKFLAGS[@]}" -o libft_test
ASAN_OPTIONS="${ASAN_OPTIONS:-detect_leaks=1:allocator_may_return_null=1}" ./libft_test "${VERBOSE[@]}"
