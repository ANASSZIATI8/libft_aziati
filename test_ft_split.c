#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

char **ft_split(char const *s, char c);

static int total = 0;
static int passed = 0;
static int quiet = 0;

static void free_result(char **parts)
{
    size_t i = 0;
    if (!parts) return;
    while (parts[i]) free(parts[i++]);
    free(parts);
}

static void show_bytes(const char *s)
{
    size_t i;
    putchar('"');
    for (i = 0; s[i]; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (c == '\n') fputs("\\n", stdout);
        else if (c == '\t') fputs("\\t", stdout);
        else if (c == '\r') fputs("\\r", stdout);
        else if (c == '\\') fputs("\\\\", stdout);
        else if (c == '"') fputs("\\\"", stdout);
        else if (c >= 32 && c < 127) putchar(c);
        else printf("\\x%02X", c);
    }
    putchar('"');
}

static int expected_count(const char *s, char delim)
{
    int result = 0;
    size_t i = 0;
    while (s[i]) {
        while (s[i] && s[i] == delim) i++;
        if (!s[i]) break;
        result++;
        while (s[i] && s[i] != delim) i++;
    }
    return result;
}

static int compare_one(const char *s, char delim, char **parts, int verbose)
{
    size_t i = 0;
    size_t j = 0;
    size_t start;
    size_t len;
    int n = expected_count(s, delim);
    if (!parts) {
        if (verbose) puts("  ft_split returned NULL");
        return 0;
    }
    while (s[i]) {
        while (s[i] && s[i] == delim) i++;
        if (!s[i]) break;
        start = i;
        while (s[i] && s[i] != delim) i++;
        len = i - start;
        if (!parts[j]) {
            if (verbose) printf("  word[%zu] missing (expected length %zu)\n", j, len);
            return 0;
        }
        /* Compare bytes only after checking observed word length. */
        if (strlen(parts[j]) != len || memcmp(parts[j], s + start, len) != 0) {
            if (verbose) {
                printf("  word[%zu]: expected ", j);
                printf("%.*s", (int)len, s + start);
                printf(" | got "); show_bytes(parts[j]); putchar('\n');
            }
            return 0;
        }
        j++;
    }
    if (parts[j] != NULL) {
        if (verbose) printf("  expected NULL terminator at result[%zu] (expected words %d)\n", j, n);
        return 0;
    }
    return 1;
}

static void check(const char *name, const char *s, char delim)
{
    char **result;
    int ok;
    total++;
    result = ft_split(s, delim);
    ok = compare_one(s, delim, result, 1);
    if (!quiet || !ok)
    {
    printf("%s | %s | delimiter=", ok ? "PASS" : "FAIL", name);
    if (delim == '\0') printf("\\0");
    else if (delim == '\n') printf("\\n");
    else if (delim == '\t') printf("\\t");
    else if (delim == ' ') printf("space");
    else printf("'%c'", delim);
    printf(" | input="); show_bytes(s);
    printf(" | words=%d\n", expected_count(s, delim));
    }
    if (ok) passed++;
    free_result(result);
}

static void generated_tests(void)
{
    const char alphabet[] = {'a', ',', 'b'};
    char s[9];
    int len, combinations, k, v, i;
    char name[80];
    quiet = 1;
    for (len = 0; len <= 8; ++len) {
        combinations = 1;
        for (i = 0; i < len; ++i) combinations *= 3;
        for (k = 0; k < combinations; ++k) {
            v = k;
            for (i = 0; i < len; ++i) {
                s[i] = alphabet[v % 3];
                v /= 3;
            }
            s[len] = '\0';
            snprintf(name, sizeof(name), "generated_%d_%d", len, k);
            check(name, s, ',');
        }
    }
    quiet = 0;
}

int main(int argc, char **argv)
{
    char large[20002];
    size_t i;
    const char *const label = "\n===== FT_SPLIT TESTS =====";
    puts(label);
    check("empty", "", ' ');
    check("one_word", "hello", ' ');
    check("two_words", "hello world", ' ');
    check("three_words", "hello world 42", ' ');
    check("only_spaces", "     ", ' ');
    check("leading_spaces", "   hello", ' ');
    check("trailing_spaces", "hello   ", ' ');
    check("both_sides", "   hello   ", ' ');
    check("many_spaces", "  a    b      c  ", ' ');
    check("one_delimiter", ",", ',');
    check("only_delimiters", ",,,,,", ',');
    check("leading_delimiters", ",,,hello", ',');
    check("trailing_delimiters", "hello,,,", ',');
    check("consecutive_delimiters", ",,hello,,,world,,42,", ',');
    check("no_delimiter", "hello world", ',');
    check("different_delimiters", "a,b c,d", ',');
    check("delimiter_nul", "abc", '\0');
    check("delimiter_nul_empty", "", '\0');
    check("newline", "\na\n\nb\n", '\n');
    check("tab", "\ta\t\tb\t", '\t');
    check("digits", "11223344", '2');
    check("same_as_word", "aaaaa", 'a');
    check("mixed_symbols", "/a///b//c/", '/');
    check("punctuation", "...abc...def...", '.');
    check("utf8_bytes", "caf\303\251 caf\303\251", ' ');
    check("single_character", "a", ',');
    check("single_char_delimiter", "a", 'a');
    check("spaces_not_delimiter", " a b ", ',');
    check("embedded_other_whitespace", "a\tb\nc\rd", ' ');
    for (i = 0; i < sizeof(large) - 2; i++) large[i] = i % 3 == 0 ? ',' : 'A';
    large[sizeof(large) - 2] = 'Z';
    large[sizeof(large) - 1] = '\0';
    check("large_many_words", large, ',');
    if (argc > 1 && strcmp(argv[1], "--exhaustive") == 0)
        generated_tests();
    printf("\nFINAL: %d/%d tests passed\n", passed, total);
    return passed == total ? 0 : 1;
}
