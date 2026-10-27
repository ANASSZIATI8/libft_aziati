/*
 * 42 / 1337 LIBFT INDEPENDENT TEST SUITE
 * Tests the usual mandatory (34) and bonus (9) libft functions.
 * This is NOT the private 42 Moulinette, and cannot guarantee every hidden case.
 *
 * Compile using the companion run_libft_tests.sh (no Makefile needed).
 * Direct compile example:
 *   cc -Wall -Wextra -Werror -g -fsanitize=address,undefined \
 *     -DTEST_WRAP_MALLOC test_libft_all.c ft_*.c \
 *     -Wl,--wrap=malloc -o libft_test && ./libft_test
 * For mandatory only, add -DLIBFT_NO_BONUS (and don't include bonus sources).
 */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>
#include <locale.h>
#include <unistd.h>
#include <errno.h>

static int g_total;
static int g_pass;
static int g_group_total;
static int g_group_pass;
static int g_verbose;
static const char *g_group;
static unsigned int g_seed = 0x42C0FFEEu;

static unsigned int rnd(void)
{
    unsigned int x = g_seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return (g_seed = x);
}

static void check(int good, const char *label, int line)
{
    ++g_total;
    ++g_group_total;
    if (good)
    {
        ++g_pass;
        ++g_group_pass;
        if (g_verbose)
            printf("  PASS %s\n", label);
    }
    else
        printf("  FAIL line %-4d %s\n", line, label);
}
#define CHECK(cond, label) check(!!(cond), (label), __LINE__)

static void group(const char *name)
{
    if (g_group)
        printf("[%s] %d/%d passed\n", g_group, g_group_pass, g_group_total);
    g_group = name;
    g_group_total = 0;
    g_group_pass = 0;
    printf("\n-- %s --\n", name);
}

static int sign_of(int v)
{
    return ((v > 0) - (v < 0));
}

static int streq(const char *a, const char *b)
{
    return (a && b && strcmp(a, b) == 0);
}

static void fill(unsigned char *p, size_t n)
{
    size_t i;
    for (i = 0; i < n; ++i)
        p[i] = (unsigned char)rnd();
}

static void rand_string(char *s, size_t len)
{
    size_t i;
    for (i = 0; i < len; ++i)
        s[i] = (char)('a' + rnd() % 26);
    s[len] = '\0';
}

/* Linux GNU ld only: deliberately fail a particular malloc call in user code. */
#ifdef TEST_WRAP_MALLOC
extern void *__real_malloc(size_t n);
static long g_fail_at;
static long g_malloc_calls;
void *__wrap_malloc(size_t n)
{
    ++g_malloc_calls;
    if (g_fail_at > 0 && g_malloc_calls == g_fail_at)
        return (NULL);
    return (__real_malloc(n));
}
static void fail_malloc_at(long nth)
{
    g_malloc_calls = 0;
    g_fail_at = nth;
}
static void restore_malloc(void)
{
    g_fail_at = 0;
    g_malloc_calls = 0;
}
#ifndef LIBFT_NO_BONUS
static void *unwrapped_malloc(size_t n)
{
    return (__real_malloc(n));
}
#endif
#else
#ifndef LIBFT_NO_BONUS
static void *unwrapped_malloc(size_t n)
{
    return (malloc(n));
}
#endif
#endif

static void test_characters(void)
{
    int c;
    group("Character classifiers and case conversion (ft_is*, ft_to*)");
    for (c = -1; c <= 255; ++c)
    {
        CHECK(!!ft_isalpha(c) == !!isalpha(c), "ft_isalpha vs libc");
        CHECK(!!ft_isdigit(c) == !!isdigit(c), "ft_isdigit vs libc");
        CHECK(!!ft_isalnum(c) == !!isalnum(c), "ft_isalnum vs libc");
        CHECK(!!ft_isprint(c) == !!isprint(c), "ft_isprint vs libc");
        CHECK(!!ft_isascii(c) == (c >= 0 && c <= 127), "ft_isascii ASCII bounds");
        CHECK(ft_toupper(c) == toupper(c), "ft_toupper vs libc");
        CHECK(ft_tolower(c) == tolower(c), "ft_tolower vs libc");
    }
}

static void test_strlen(void)
{
    char s[4097];
    size_t n;
    group("ft_strlen");
    CHECK(ft_strlen("") == 0, "empty string");
    CHECK(ft_strlen("a") == 1, "one character");
    CHECK(ft_strlen("hello world") == 11, "normal string");
    CHECK(ft_strlen("a\0hidden") == 1, "embedded null terminator");
    for (n = 0; n <= 4096; n = n < 32 ? n + 1 : n * 2)
    {
        rand_string(s, n);
        CHECK(ft_strlen(s) == strlen(s), "variable length");
    }
    CHECK(ft_strlen(s + 17) == strlen(s + 17), "pointer inside string");
}

static void test_memory(void)
{
    unsigned char a[128], b[128], x[128], y[128];
    size_t len, start, n;
    int c, k;
    group("ft_memset, ft_bzero, ft_memcpy, ft_memmove");
    for (k = 0; k < 300; ++k)
    {
        fill(a, sizeof(a));
        memcpy(b, a, sizeof(a));
        start = rnd() % 80;
        len = rnd() % 49;
        c = (int)rnd();
        CHECK(ft_memset(a + start, c, len) == a + start &&
            !memcmp(a, (memset(b + start, c, len), b), sizeof(a)),
            "memset bytes, return pointer, and boundaries");
        memcpy(a, b, sizeof(a));
        memcpy(x, b, sizeof(x));
        memset(x + start, 0, len);
        ft_bzero(a + start, len);
        CHECK(!memcmp(a, x, sizeof(a)), "bzero range and sentinels");

        fill(a, sizeof(a));
        fill(b, sizeof(b));
        memcpy(x, a, sizeof(x));
        memcpy(y, b, sizeof(y));
        start = rnd() % 64;
        len = rnd() % 65;
        CHECK(ft_memcpy(a + start, b + start, len) == a + start &&
            (memcpy(x + start, y + start, len), !memcmp(a, x, sizeof(a))),
            "memcpy binary data, n=0, unaligned pointers");
        fill(a, sizeof(a));
        memcpy(x, a, sizeof(x));
        start = rnd() % 64;
        n = rnd() % 64;
        len = rnd() % 64;
        CHECK(ft_memmove(a + start, a + n, len) == a + start &&
            (memmove(x + start, x + n, len), !memcmp(a, x, sizeof(a))),
            "memmove overlaps forward/backward and no overlap");
    }
    fill(a, sizeof(a));
    memcpy(b, a, sizeof(a));
    CHECK(ft_memmove(a, a, sizeof(a)) == a && !memcmp(a, b, sizeof(a)),
          "memmove identical src and dst");
    CHECK(ft_memmove(a, a + 3, 0) == a, "memmove zero length");
}

/* Portable references: strlcpy, strlcat and strnstr are not universally in libc. */
static size_t reference_strlcpy(char *dst, const char *src, size_t size)
{
    size_t sl = strlen(src), i = 0;
    if (size)
    {
        while (i + 1 < size && src[i])
        {
            dst[i] = src[i];
            ++i;
        }
        dst[i] = '\0';
    }
    return (sl);
}

static size_t reference_strlcat(char *dst, const char *src, size_t size)
{
    size_t dl = 0, sl = strlen(src), i = 0;
    while (dl < size && dst[dl])
        ++dl;
    if (dl == size)
        return (size + sl);
    while (dl + i + 1 < size && src[i])
    {
        dst[dl + i] = src[i];
        ++i;
    }
    dst[dl + i] = '\0';
    return (dl + sl);
}

static char *reference_strnstr(const char *hay, const char *needle, size_t n)
{
    size_t i, j;
    if (!needle[0])
        return ((char *)hay);
    for (i = 0; i < n && hay[i]; ++i)
    {
        j = 0;
        while (needle[j] && i + j < n && hay[i + j] == needle[j])
            ++j;
        if (!needle[j])
            return ((char *)(hay + i));
    }
    return (NULL);
}

static void test_strl(void)
{
    char a[128], b[128], src[90], dest[100];
    size_t n, r1, r2, dl, sl;
    int k;
    group("ft_strlcpy and ft_strlcat");
    for (k = 0; k < 500; ++k)
    {
        sl = rnd() % 85;
        rand_string(src, sl);
        n = rnd() % 129;
        memset(a, 0x5A, sizeof(a));
        memset(b, 0x5A, sizeof(b));
        r1 = ft_strlcpy(a, src, n);
        r2 = reference_strlcpy(b, src, n);
        CHECK(r1 == r2 && !memcmp(a, b, sizeof(a)),
              "strlcpy return length, termination and untouched bytes");

        dl = rnd() % 50;
        rand_string(dest, dl);
        memset(a, 0x5A, sizeof(a));
        memset(b, 0x5A, sizeof(b));
        memcpy(a, dest, dl + 1);
        memcpy(b, dest, dl + 1);
        n = rnd() % 129;
        r1 = ft_strlcat(a, src, n);
        r2 = reference_strlcat(b, src, n);
        CHECK(r1 == r2 && !memcmp(a, b, sizeof(a)),
              "strlcat return length, size <= dst length, boundaries");
    }
}

static void test_strchr_family(void)
{
    char s[130];
    int c, k;
    size_t n;
    group("ft_strchr, ft_strrchr, ft_strncmp, ft_strnstr");
    for (k = 0; k < 400; ++k)
    {
        n = rnd() % 120;
        rand_string(s, n);
        c = (int)(rnd() % 256);
        CHECK(ft_strchr(s, c) == strchr(s, c), "strchr found/missing/NUL/bytes");
        CHECK(ft_strrchr(s, c) == strrchr(s, c), "strrchr last occurrence");
    }
    strcpy(s, "abcabc");
    CHECK(ft_strchr(s, 'b') == s + 1, "strchr first occurrence");
    CHECK(ft_strrchr(s, 'b') == s + 4, "strrchr last occurrence");
    CHECK(ft_strchr(s, '\0') == s + 6, "strchr terminator");
    CHECK(ft_strrchr(s, '\0') == s + 6, "strrchr terminator");
    CHECK(ft_strncmp("abc", "xyz", 0) == 0, "strncmp n=0");
    CHECK(sign_of(ft_strncmp("\xff", "\x01", 1)) ==
          sign_of(strncmp("\xff", "\x01", 1)), "strncmp unsigned char");
    CHECK(sign_of(ft_strncmp("abc", "abcd", 5)) ==
          sign_of(strncmp("abc", "abcd", 5)), "strncmp shorter first string");
    for (k = 0; k < 500; ++k)
    {
        char a[80], b[80];
        rand_string(a, rnd() % 70);
        rand_string(b, rnd() % 70);
        n = rnd() % 90;
        CHECK(sign_of(ft_strncmp(a, b, n)) == sign_of(strncmp(a, b, n)),
              "strncmp random sign/length/terminator");
    }
    strcpy(s, "aabaabaac");
    CHECK(ft_strnstr(s, "", 0) == s, "strnstr empty needle and n=0");
    CHECK(ft_strnstr(s, "baa", 0) == NULL, "strnstr nonempty needle and n=0");
    CHECK(ft_strnstr(s, "baac", 8) == NULL, "strnstr match beyond n");
    CHECK(ft_strnstr(s, "baac", 9) == s + 5, "strnstr match at boundary");
    for (k = 0; k < 400; ++k)
    {
        char hay[80], needle[40];
        char *p, *q;
        rand_string(hay, rnd() % 70);
        rand_string(needle, rnd() % 30);
        n = rnd() % 90;
        p = ft_strnstr(hay, needle, n);
        q = reference_strnstr(hay, needle, n);
        CHECK(p == q, "strnstr randomized, partial match and bounds");
    }
}

static void test_memsearch(void)
{
    unsigned char a[128], b[128];
    size_t n;
    int k, c;
    group("ft_memchr and ft_memcmp");
    for (k = 0; k < 700; ++k)
    {
        fill(a, sizeof(a));
        fill(b, sizeof(b));
        n = rnd() % 129;
        c = (int)(rnd() & 255u);
        CHECK(ft_memchr(a, c, n) == memchr(a, c, n),
              "memchr random bytes including NUL, n=0");
        CHECK(sign_of(ft_memcmp(a, b, n)) == sign_of(memcmp(a, b, n)),
              "memcmp sign with binary data");
        memcpy(b, a, sizeof(a));
        CHECK(ft_memcmp(a, b, n) == 0, "memcmp identical binary data");
    }
    {
        unsigned char buf[] = {'a', 0, 'b', 255, 0};
        CHECK(ft_memchr(buf, 'b', 4) == buf + 2, "memchr past embedded null");
        CHECK(ft_memchr(buf, 255, 4) == buf + 3, "memchr 0xFF");
        CHECK(ft_memchr(buf, 'b', 2) == NULL, "memchr respects length");
        CHECK(sign_of(ft_memcmp("\x01", "\xff", 1)) == -1,
              "memcmp compares unsigned bytes");
    }
}

static void test_atoi(void)
{
    static const char *cases[] = {
        "", "0", "-0", "+0", "1", "-1", "+1", "42", "-42",
        "2147483647", "-2147483648", "000001234", "   5", "\t\n\r\v\f  -56",
        "  +00123words", "123abc", "--4", "++4", "+-3", "-+3",
        "  000", "99 77", "-2147483647", "2147483646", "\n+7",
        "   +", "  -", "0x10", "07", "-00012", "\t 12\n",
        "1-2", "1+2", "  0000000008", "00000000-5"
    };
    size_t i;
    int k;
    char s[100];
    group("ft_atoi (defined int-range behavior)");
    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i)
        CHECK(ft_atoi(cases[i]) == atoi(cases[i]), "atoi whitespace/sign/leading zeros/suffix");
    for (k = 0; k < 500; ++k)
    {
        int v = (int)(rnd() % 2000000001u) - 1000000000;
        snprintf(s, sizeof(s), " \t%+011dtext", v);
        CHECK(ft_atoi(s) == atoi(s), "atoi randomized in-range numbers");
    }
    /* atoi() on out-of-int-range inputs has implementation-dependent or
       undefined behavior: such tests are intentionally not asserted. */
}

static void test_calloc_strdup(void)
{
    size_t n;
    unsigned char *p;
    char s[2048], *dup;
    int k;
    group("ft_calloc and ft_strdup");
    for (k = 0; k < 100; ++k)
    {
        n = (size_t)(rnd() % 1000 + 1);
        p = (unsigned char *)ft_calloc(n, 1);
        CHECK(p != NULL, "calloc successful allocation");
        if (p)
        {
            size_t j;
            int zero = 1;
            for (j = 0; j < n; ++j)
                if (p[j] != 0)
                    zero = 0;
            CHECK(zero, "calloc initializes all bytes to zero");
            memset(p, 0x5A, n);
            free(p);
        }
    }
    p = (unsigned char *)ft_calloc(0, 8);
    CHECK(1, "calloc nmemb=0 does not crash (NULL or freeable pointer)");
    free(p);
    p = (unsigned char *)ft_calloc(8, 0);
    CHECK(1, "calloc size=0 does not crash (NULL or freeable pointer)");
    free(p);
    p = (unsigned char *)ft_calloc(SIZE_MAX, 2);
    CHECK(p == NULL, "calloc detects size_t multiplication overflow");
    free(p);
    for (k = 0; k < 250; ++k)
    {
        rand_string(s, rnd() % (sizeof(s) - 1));
        dup = ft_strdup(s);
        CHECK(streq(dup, s), "strdup content including empty and long");
        CHECK(dup && dup != s, "strdup separate allocation");
        if (dup)
        {
            if (s[0])
            {
                char first = s[0];
                dup[0] = '#';
                CHECK(s[0] == first, "strdup doesn't alias original");
            }
            free(dup);
        }
    }
}

static void test_substr(void)
{
    struct item { const char *s; unsigned int start; size_t len; const char *expected; };
    static const struct item tests[] = {
        {"hello", 0, 5, "hello"}, {"hello", 0, 0, ""},
        {"hello", 1, 3, "ell"}, {"hello", 4, 5, "o"},
        {"hello", 5, 20, ""}, {"hello", 8, 2, ""},
        {"", 0, 30, ""}, {"", 5, 1, ""},
        {"abc", 1, SIZE_MAX, "bc"}, {"abc", UINT_MAX, 4, ""},
        {"abcdef", 2, 100, "cdef"}, {"a", 0, 2, "a"}
    };
    size_t i;
    char *p;
    group("ft_substr");
    for (i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i)
    {
        p = ft_substr(tests[i].s, tests[i].start, tests[i].len);
        CHECK(streq(p, tests[i].expected), "substring start/len/out of range");
        free(p);
    }
}

static void test_strjoin_trim(void)
{
    static const char *pairs[][3] = {
        {"", "", ""}, {"a", "", "a"}, {"", "b", "b"},
        {"hello", " world", "hello world"}, {"abc", "xyz", "abcxyz"},
        {" ", " ", "  "}, {"\n", "x", "\nx"}
    };
    static const char *trims[][3] = {
        {"", " ", ""}, {"hello", " ", "hello"},
        {"  hello  ", " ", "hello"}, {" ", " ", ""},
        {"ababa", "ab", ""}, {"abcHELLOcba", "abc", "HELLO"},
        {"..hi..", ".", "hi"}, {"...hi.. ", " .", "hi"},
        {"hello", "", "hello"}, {"abc", "xyz", "abc"},
        {"xy xy xy", "xy", " xy "}
    };
    char *p, a[2048], b[2048];
    size_t i;
    int k;
    group("ft_strjoin and ft_strtrim");
    for (i = 0; i < sizeof(pairs) / sizeof(pairs[0]); ++i)
    {
        p = ft_strjoin(pairs[i][0], pairs[i][1]);
        CHECK(streq(p, pairs[i][2]), "strjoin empty/normal strings");
        free(p);
    }
    for (i = 0; i < sizeof(trims) / sizeof(trims[0]); ++i)
    {
        p = ft_strtrim(trims[i][0], trims[i][1]);
        CHECK(streq(p, trims[i][2]), "strtrim ends/all/none/multiple set chars");
        free(p);
    }
    for (k = 0; k < 120; ++k)
    {
        size_t la = rnd() % 900, lb = rnd() % 900;
        rand_string(a, la);
        rand_string(b, lb);
        p = ft_strjoin(a, b);
        CHECK(p && strlen(p) == la + lb &&
              !memcmp(p, a, la) && !memcmp(p + la, b, lb + 1),
              "strjoin randomized long strings");
        free(p);
    }
}

static int split_matches(char **parts, const char *const *want, size_t count)
{
    size_t i;
    if (!parts)
        return (0);
    for (i = 0; i < count; ++i)
        if (!parts[i] || !streq(parts[i], want[i]))
            return (0);
    return (parts[count] == NULL);
}

static void free_split(char **parts)
{
    size_t i;
    if (!parts)
        return ;
    /* Only used on well-formed results in this test suite. */
    for (i = 0; parts[i] && i < 10000; ++i)
        free(parts[i]);
    free(parts);
}

static void split_case(const char *input, char delimiter,
                       const char *const *expected, size_t count, const char *label)
{
    char **parts = ft_split(input, delimiter);
    int okay = split_matches(parts, expected, count);
    CHECK(okay, label);
    free_split(parts);
}

static void test_split(void)
{
    const char *empty[] = {NULL};
    const char *one[] = {"hello"};
    const char *two[] = {"hello", "world"};
    const char *three[] = {"a", "b", "c"};
    const char *lines[] = {"a", "b", "c"};
    char s[4096];
    char **parts;
    int i, okay;
    group("ft_split");
    split_case("", ' ', empty, 0, "empty input");
    split_case("    ", ' ', empty, 0, "only delimiters");
    split_case("hello", ' ', one, 1, "one word");
    split_case("  hello ", ' ', one, 1, "leading and trailing delimiters");
    split_case("hello world", ' ', two, 2, "two words");
    split_case("  hello   world  ", ' ', two, 2, "consecutive delimiters");
    split_case("a,b,c", ',', three, 3, "comma delimiter");
    split_case(",,a,,b,c,,,", ',', three, 3, "consecutive commas");
    split_case("a\nb\nc", '\n', lines, 3, "newline delimiter");
    split_case("hello", '\0', one, 1, "zero delimiter");
    split_case("aaa", 'a', empty, 0, "all characters are delimiter");
    for (i = 0; i < 200; ++i)
    {
        size_t at = 0;
        int k;
        const char *want[4] = {"word0", "word1", "word2", "word3"};
        for (k = 0; k < 4; ++k)
        {
            int n = (int)(rnd() % 8) + (k != 0);
            while (n--)
                s[at++] = ':';
            memcpy(s + at, want[k], 5);
            at += 5;
        }
        s[at] = '\0';
        parts = ft_split(s, ':');
        okay = split_matches(parts, want, 4);
        CHECK(okay, "random repeated separators and order");
        free_split(parts);
    }
}

static void test_itoa(void)
{
    static const int nums[] = {
        0, 1, -1, 10, -10, 99, -99, 100, -100,
        INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1,
        1000000000, -1000000000, 214748364, -214748364
    };
    char expected[64], *actual;
    size_t i;
    int k;
    group("ft_itoa");
    for (i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i)
    {
        snprintf(expected, sizeof(expected), "%d", nums[i]);
        actual = ft_itoa(nums[i]);
        CHECK(streq(actual, expected), "itoa zero, signed bounds, powers of ten");
        free(actual);
    }
    for (k = 0; k < 600; ++k)
    {
        int value = (int)rnd();
        snprintf(expected, sizeof(expected), "%d", value);
        actual = ft_itoa(value);
        CHECK(streq(actual, expected), "itoa randomized full int range");
        free(actual);
    }
}

static unsigned int g_map_calls;
static unsigned int g_iter_calls;
static char map_rotate(unsigned int i, char c)
{
    ++g_map_calls;
    return ((char)(c + (int)(i % 3u)));
}
static void iter_rotate(unsigned int i, char *c)
{
    ++g_iter_calls;
    *c = (char)(*c + (int)(i % 3u));
}
static void test_strmap_iter(void)
{
    char s[] = "abcde";
    char empty[] = "";
    char *out;
    group("ft_strmapi and ft_striteri");
    g_map_calls = 0;
    out = ft_strmapi(s, map_rotate);
    CHECK(streq(out, "acedf"), "strmapi uses index and returns new string");
    CHECK(g_map_calls == 5, "strmapi calls f exactly once per char");
    CHECK(streq(s, "abcde"), "strmapi does not modify original string");
    CHECK(out != s, "strmapi allocates separate string");
    free(out);
    g_map_calls = 0;
    out = ft_strmapi("", map_rotate);
    CHECK(streq(out, "") && g_map_calls == 0, "strmapi empty input");
    free(out);
    g_iter_calls = 0;
    ft_striteri(s, iter_rotate);
    CHECK(streq(s, "acedf"), "striteri changes original chars using index");
    CHECK(g_iter_calls == 5, "striteri calls callback once per character");
    g_iter_calls = 0;
    ft_striteri(empty, iter_rotate);
    CHECK(!empty[0] && !g_iter_calls, "striteri empty input");
}

/* fd tests: pipe captures exact bytes; no invalid fd undefined assumptions. */
static int capture_fd(void (*writer)(int), const char *expected, size_t expected_len)
{
    int p[2];
    unsigned char buf[4096];
    size_t used = 0;
    ssize_t got;
    if (pipe(p) != 0)
        return (0);
    writer(p[1]);
    close(p[1]);
    while (used < sizeof(buf) && (got = read(p[0], buf + used, sizeof(buf) - used)) > 0)
        used += (size_t)got;
    close(p[0]);
    return (used == expected_len && !memcmp(buf, expected, expected_len));
}
static void wr_char(int fd) { ft_putchar_fd('X', fd); }
static void wr_nul(int fd) { ft_putchar_fd('\0', fd); }
static void wr_str(int fd) { ft_putstr_fd("hello", fd); }
static void wr_empty(int fd) { ft_putstr_fd("", fd); }
static void wr_endl(int fd) { ft_putendl_fd("hello", fd); }
static void wr_emptyendl(int fd) { ft_putendl_fd("", fd); }
static void wr_zero(int fd) { ft_putnbr_fd(0, fd); }
static void wr_negative(int fd) { ft_putnbr_fd(-12345, fd); }
static void wr_min(int fd) { ft_putnbr_fd(INT_MIN, fd); }
static void wr_max(int fd) { ft_putnbr_fd(INT_MAX, fd); }
static void wr_large(int fd) { ft_putnbr_fd(1000000000, fd); }
static void test_fd(void)
{
    group("ft_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd");
    CHECK(capture_fd(wr_char, "X", 1), "putchar_fd one byte");
    CHECK(capture_fd(wr_nul, "\0", 1), "putchar_fd can write NUL byte");
    CHECK(capture_fd(wr_str, "hello", 5), "putstr_fd exact bytes");
    CHECK(capture_fd(wr_empty, "", 0), "putstr_fd empty string");
    CHECK(capture_fd(wr_endl, "hello\n", 6), "putendl_fd includes newline");
    CHECK(capture_fd(wr_emptyendl, "\n", 1), "putendl_fd empty string is newline");
    CHECK(capture_fd(wr_zero, "0", 1), "putnbr_fd zero");
    CHECK(capture_fd(wr_negative, "-12345", 6), "putnbr_fd negative");
    CHECK(capture_fd(wr_min, "-2147483648", 11), "putnbr_fd INT_MIN");
    CHECK(capture_fd(wr_max, "2147483647", 10), "putnbr_fd INT_MAX");
    CHECK(capture_fd(wr_large, "1000000000", 10), "putnbr_fd large positive");
}

#ifndef LIBFT_NO_BONUS
static int g_deleted;
static int g_iterated;
static int g_transformed;
static void count_del(void *p)
{
    ++g_deleted;
    free(p);
}
static void no_op_del(void *p) { (void)p; }
static void increment_content(void *p)
{
    ++g_iterated;
    if (p)
        ++*(int *)p;
}
static void *double_copy(void *p)
{
    int *v;
    ++g_transformed;
    v = (int *)unwrapped_malloc(sizeof(int));
    if (v)
        *v = p ? *(int *)p * 2 : -42;
    return (v);
}
static void test_lstnew(void)
{
    int value = 42;
    t_list *p;
    group("ft_lstnew");
    p = ft_lstnew(&value);
    CHECK(p != NULL, "lstnew allocates a node");
    if (p)
    {
        CHECK(p->content == &value, "lstnew stores content pointer unchanged");
        CHECK(p->next == NULL, "lstnew next initialized NULL");
        free(p);
    }
    p = ft_lstnew(NULL);
    CHECK(p != NULL, "lstnew NULL content creates a node");
    if (p)
    {
        CHECK(p->content == NULL && p->next == NULL, "lstnew NULL content and next");
        free(p);
    }
}

static void test_lstadd(void)
{
    int a = 1, b = 2, c = 3;
    t_list *head = NULL, *n1, *n2, *n3;
    group("ft_lstadd_front, ft_lstadd_back, ft_lstsize, ft_lstlast");
    CHECK(ft_lstsize(NULL) == 0, "lstsize NULL = 0");
    CHECK(ft_lstlast(NULL) == NULL, "lstlast NULL = NULL");
    n1 = ft_lstnew(&a);
    n2 = ft_lstnew(&b);
    n3 = ft_lstnew(&c);
    if (!n1 || !n2 || !n3)
    {
        CHECK(0, "test setup node allocations");
        free(n1); free(n2); free(n3);
        return ;
    }
    ft_lstadd_back(&head, n2);
    CHECK(head == n2 && ft_lstsize(head) == 1, "add_back to empty list");
    ft_lstadd_front(&head, n1);
    CHECK(head == n1 && n1->next == n2, "add_front updates head and next");
    ft_lstadd_back(&head, n3);
    CHECK(n2->next == n3 && n3->next == NULL, "add_back appends last node");
    CHECK(ft_lstsize(head) == 3, "lstsize of 3 nodes");
    CHECK(ft_lstlast(head) == n3, "lstlast of 3 nodes");
    ft_lstclear(&head, no_op_del);
    CHECK(head == NULL, "lstclear after add operations");
}

static void test_lstdelclear(void)
{
    int *v1, *v2, *v3;
    t_list *first, *second, *third, *head;
    group("ft_lstdelone and ft_lstclear");
    g_deleted = 0;
    ft_lstdelone(NULL, count_del);
    CHECK(g_deleted == 0, "lstdelone NULL does nothing");
    head = NULL;
    ft_lstclear(&head, count_del);
    CHECK(head == NULL, "lstclear empty list");
    ft_lstclear(NULL, count_del);
    CHECK(1, "lstclear NULL double-pointer does not crash");
    v1 = (int *)malloc(sizeof(int));
    v2 = (int *)malloc(sizeof(int));
    v3 = (int *)malloc(sizeof(int));
    if (!v1 || !v2 || !v3)
    {
        free(v1); free(v2); free(v3);
        CHECK(0, "test setup content allocations");
        return ;
    }
    *v1 = 5; *v2 = 6; *v3 = 7;
    first = ft_lstnew(v1);
    second = ft_lstnew(v2);
    third = ft_lstnew(v3);
    if (!first || !second || !third)
    {
        CHECK(0, "test setup node allocations");
        free(first); free(second); free(third);
        free(v1); free(v2); free(v3);
        return ;
    }
    first->next = second;
    second->next = third;
    g_deleted = 0;
    ft_lstdelone(first, count_del);
    CHECK(g_deleted == 1, "lstdelone deletes exactly one content");
    CHECK(second->content == v2 && second->next == third && *(int *)v2 == 6,
          "lstdelone preserves subsequent nodes");
    head = second;
    ft_lstclear(&head, count_del);
    CHECK(head == NULL, "lstclear sets head pointer NULL");
    CHECK(g_deleted == 3, "lstclear frees all remaining contents once");
}

static void test_lstiter(void)
{
    int values[] = {5, -1, 0, 7};
    t_list nodes[4];
    size_t i;
    group("ft_lstiter");
    for (i = 0; i < 4; ++i)
    {
        nodes[i].content = &values[i];
        nodes[i].next = i == 3 ? NULL : &nodes[i + 1];
    }
    g_iterated = 0;
    ft_lstiter(nodes, increment_content);
    CHECK(g_iterated == 4, "lstiter calls callback exactly 4 times");
    CHECK(values[0] == 6 && values[1] == 0 && values[2] == 1 && values[3] == 8,
          "lstiter changes each content correctly");
    g_iterated = 0;
    ft_lstiter(NULL, increment_content);
    CHECK(g_iterated == 0, "lstiter NULL list does nothing");
}

static void test_lstmap(void)
{
    int values[] = {3, -5, 0, INT_MAX / 2, 17};
    int original[] = {3, -5, 0, INT_MAX / 2, 17};
    t_list nodes[5];
    t_list *mapped, *p;
    size_t i;
    int correct = 1, independent = 1;
    group("ft_lstmap: copies, order, ownership and callbacks");
    for (i = 0; i < 5; ++i)
    {
        nodes[i].content = &values[i];
        nodes[i].next = i == 4 ? NULL : &nodes[i + 1];
    }
    g_deleted = 0;
    g_transformed = 0;
    mapped = ft_lstmap(NULL, double_copy, count_del);
    CHECK(mapped == NULL, "lstmap NULL list returns NULL");
    CHECK(g_transformed == 0, "lstmap NULL doesn't call f");
    mapped = ft_lstmap(nodes, double_copy, count_del);
    CHECK(mapped != NULL, "lstmap creates a mapped list");
    CHECK(g_transformed == 5, "lstmap calls f once per node");
    CHECK(ft_lstsize(mapped) == 5, "lstmap preserves list size");
    p = mapped;
    for (i = 0; i < 5; ++i)
    {
        if (!p || !p->content)
        {
            correct = 0;
            independent = 0;
            break ;
        }
        if (*(int *)p->content != values[i] * 2)
            correct = 0;
        if (p == &nodes[i] || p->content == nodes[i].content)
            independent = 0;
        p = p->next;
    }
    CHECK(correct && p == NULL, "lstmap content and order correct");
    CHECK(independent, "lstmap allocates independent nodes and contents");
    CHECK(!memcmp(values, original, sizeof(values)), "lstmap doesn't change original contents");
    ft_lstclear(&mapped, count_del);
    CHECK(mapped == NULL, "lstmap result can be cleared");
    CHECK(g_deleted == 5, "lstmap cleanup calls del once per content");
    g_deleted = 0;
    g_transformed = 0;
    mapped = ft_lstmap(&nodes[4], double_copy, count_del);
    CHECK(mapped && mapped->content && *(int *)mapped->content == 34 &&
          mapped->next == NULL, "lstmap single node");
    ft_lstclear(&mapped, count_del);
    CHECK(g_deleted == 1 && g_transformed == 1, "lstmap single node lifecycle");
    /* NULL content is legal when callback knows how to handle it. */
    {
        t_list empty_content;
        empty_content.content = NULL;
        empty_content.next = NULL;
        mapped = ft_lstmap(&empty_content, double_copy, count_del);
        CHECK(mapped && mapped->content && *(int *)mapped->content == -42,
              "lstmap callback handles NULL content");
        ft_lstclear(&mapped, count_del);
    }
}
#endif

#ifdef TEST_WRAP_MALLOC
static void test_malloc_failures(void)
{
    int n;
    char **split;
    char *text;
    void *p;
    group("Injected malloc failures (GNU ld --wrap=malloc)");
    fail_malloc_at(1);
    p = ft_calloc(2, 8);
    restore_malloc();
    CHECK(p == NULL, "calloc returns NULL when malloc fails");
    free(p);
    fail_malloc_at(1);
    text = ft_strdup("hello");
    restore_malloc();
    CHECK(text == NULL, "strdup returns NULL when malloc fails");
    free(text);
    fail_malloc_at(1);
    text = ft_substr("hello", 1, 3);
    restore_malloc();
    CHECK(text == NULL, "substr returns NULL when malloc fails");
    free(text);
    fail_malloc_at(1);
    text = ft_strjoin("a", "b");
    restore_malloc();
    CHECK(text == NULL, "strjoin returns NULL when malloc fails");
    free(text);
    fail_malloc_at(1);
    text = ft_strtrim(" abc ", " ");
    restore_malloc();
    CHECK(text == NULL, "strtrim returns NULL when malloc fails");
    free(text);
    fail_malloc_at(1);
    text = ft_itoa(INT_MIN);
    restore_malloc();
    CHECK(text == NULL, "itoa returns NULL when malloc fails");
    free(text);
    fail_malloc_at(1);
    text = ft_strmapi("abc", map_rotate);
    restore_malloc();
    CHECK(text == NULL, "strmapi returns NULL when malloc fails");
    free(text);
    /* Split should free previously allocated words if any allocation fails. */
    for (n = 1; n <= 12; ++n)
    {
        long calls;
        fail_malloc_at(n);
        split = ft_split("red:green:blue", ':');
        calls = g_malloc_calls;
        restore_malloc();
        if (calls < n)
        {
            CHECK(split != NULL, "split success when no failure was injected");
            free_split(split);
            break ;
        }
        CHECK(split == NULL, "split returns NULL and releases partial allocations");
        free_split(split);
    }
#ifndef LIBFT_NO_BONUS
    {
        int v = 100;
        t_list *node, *mapped;
        t_list source[3];
        size_t i;
        fail_malloc_at(1);
        node = ft_lstnew(&v);
        restore_malloc();
        CHECK(node == NULL, "lstnew returns NULL on allocation failure");
        free(node);
        for (i = 0; i < 3; ++i)
        {
            source[i].content = &v;
            source[i].next = i == 2 ? NULL : &source[i + 1];
        }
        for (n = 1; n <= 3; ++n)
        {
            g_deleted = 0;
            g_transformed = 0;
            fail_malloc_at(n);
            mapped = ft_lstmap(source, double_copy, count_del);
            restore_malloc();
            CHECK(mapped == NULL, "lstmap returns NULL when node malloc fails");
            CHECK(g_transformed == n, "lstmap stops mapping at failed node");
            CHECK(g_deleted == n, "lstmap deletes failed content and prior list");
            if (mapped)
                ft_lstclear(&mapped, count_del);
        }
    }
#endif
}
#endif

int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "--verbose"))
        g_verbose = 1;
    setlocale(LC_ALL, "C");
    printf("42/1337 LIBFT INDEPENDENT TEST SUITE (not official Moulinette)\n");
    test_characters();
    test_strlen();
    test_memory();
    test_strl();
    test_strchr_family();
    test_memsearch();
    test_atoi();
    test_calloc_strdup();
    test_substr();
    test_strjoin_trim();
    test_split();
    test_itoa();
    test_strmap_iter();
    test_fd();
#ifndef LIBFT_NO_BONUS
    test_lstnew();
    test_lstadd();
    test_lstdelclear();
    test_lstiter();
    test_lstmap();
#endif
#ifdef TEST_WRAP_MALLOC
    test_malloc_failures();
#else
    printf("\n[Allocation-failure tests skipped: compile with -DTEST_WRAP_MALLOC and -Wl,--wrap=malloc]\n");
#endif
    if (g_group)
        printf("[%s] %d/%d passed\n", g_group, g_group_pass, g_group_total);
    printf("\n====================================\n");
    printf("RESULT: %d/%d checks passed (%d failed)\n",
           g_pass, g_total, g_total - g_pass);
    printf("====================================\n");
    return (g_pass == g_total ? 0 : 1);
}
