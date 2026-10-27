42 / 1337 LIBFT TEST SUITE
=========================

This is an independently built Libft test suite. It is NOT official Moulinette,
and it cannot guarantee any secret Moulinette test or Norminette compliance.

Files:
- test_libft_all.c      C source test harness for 34 mandatory and 9 bonus functions
- run_libft_tests.sh   Bash runner, compiles directly from ft_*.c (no Makefile)

Install:
1) Extract or copy both files into the folder with libft.h and ft_*.c
2) From that folder, run:

   bash run_libft_tests.sh

Optional:
   bash run_libft_tests.sh --mandatory    # omit linked-list test cases
   bash run_libft_tests.sh --no-wrap      # skip simulated malloc failures
   bash run_libft_tests.sh --verbose      # show individual PASS messages

The runner enables AddressSanitizer and UndefinedBehaviorSanitizer and, by
default, simulates malloc failures with GNU ld's --wrap=malloc option (Linux).

What it checks:
- Character functions: all c from EOF (-1) through 255
- Strings and memory: randomized lengths, byte comparisons, overlaps, edges
- atoi/itoa: in-range numbers, INT_MIN/INT_MAX, many randomized values
- calloc: zero-initialization, multiplication overflow, zero-sized allocations
- split/substr/strjoin/trim/strmapi/striteri: correctness, boundaries, ownership
- *_fd: exact bytes through pipes, including negative and extreme integers
- Bonus: linked-list creation, appending, traversal, deletion, map and cleanup
- Simulated malloc failures: cleanup of partial allocations, including ft_split

Limits:
- Private 42 tests and exact edge-case requirements are unavailable.
- Some inputs (e.g. invalid pointers or overflowing atoi) have undefined or
  implementation-dependent C behavior and are intentionally excluded.
- Passing functional tests does not prove Norminette or Makefile correctness.
- Compilation requires all required function prototypes in libft.h.

When a check fails, the group and source-line marker identify the assertion.
A sanitizer crash reports the faulty function and address when possible.
