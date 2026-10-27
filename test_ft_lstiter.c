#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int g_calls;
static int g_failures;
static int g_sequence[128];
static int g_sequence_len;

#define CHECK(cond, msg) do { \
    if (cond) printf("[PASS] %s\n", msg); \
    else { printf("[FAIL] %s (line %d)\n", msg, __LINE__); g_failures++; } \
} while (0)

static void count_call(void *content)
{
    (void)content;
    g_calls++;
}

static void add_ten(void *content)
{
    if (content)
        *(int *)content += 10;
    g_calls++;
}

static void record_integer(void *content)
{
    if (content && g_sequence_len < 128)
        g_sequence[g_sequence_len++] = *(int *)content;
    g_calls++;
}

static void uppercase_ascii(void *content)
{
    char *s = (char *)content;
    size_t i = 0;
    if (!s)
        return;
    while (s[i])
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = (char)(s[i] - 'a' + 'A');
        i++;
    }
}

static void noop(void *content)
{
    (void)content;
}

/* Creates a node with borrowed content. No heap allocation for content. */
static t_list *make_node(void *content)
{
    t_list *n = (t_list *)malloc(sizeof(*n));
    if (!n)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->content = content;
    n->next = NULL;
    return n;
}

static void free_nodes_only(t_list *head)
{
    while (head)
    {
        t_list *next = head->next;
        free(head);
        head = next;
    }
}

static void test_null_and_empty(void)
{
    int x = 1;
    t_list *one = make_node(&x);
    g_calls = 0;
    ft_lstiter(NULL, count_call);
    CHECK(g_calls == 0, "NULL list: callback not called");
    ft_lstiter(NULL, NULL);
    CHECK(g_calls == 0, "NULL list + NULL callback: no crash");
    ft_lstiter(one, NULL);
    CHECK(g_calls == 0 && one->content == &x && one->next == NULL,
          "NULL callback: no call, no mutation");
    free_nodes_only(one);
}

static void test_one_node(void)
{
    int x = 5;
    t_list *one = make_node(&x);
    g_calls = 0;
    ft_lstiter(one, add_ten);
    CHECK(x == 15, "one node: changes content");
    CHECK(g_calls == 1, "one node: callback called exactly once");
    CHECK(one->content == &x && one->next == NULL, "one node: structure unchanged");
    free_nodes_only(one);
}

static void test_many_nodes_and_order(void)
{
    int values[] = {1, 2, 3, 4, 5};
    t_list *nodes[5];
    int i;
    for (i = 0; i < 5; i++)
        nodes[i] = make_node(&values[i]);
    for (i = 0; i < 4; i++)
        nodes[i]->next = nodes[i + 1];
    g_calls = 0;
    g_sequence_len = 0;
    ft_lstiter(nodes[0], record_integer);
    CHECK(g_calls == 5, "five nodes: visits every node including last");
    CHECK(g_sequence_len == 5 && memcmp(g_sequence, values, sizeof(values)) == 0,
          "five nodes: callback visits nodes in order");
    CHECK(nodes[0]->next == nodes[1] && nodes[1]->next == nodes[2]
          && nodes[2]->next == nodes[3] && nodes[3]->next == nodes[4]
          && nodes[4]->next == NULL, "five nodes: links unchanged");
    free_nodes_only(nodes[0]);
}

static void test_repeated_calls(void)
{
    int a = 0, b = -10;
    t_list *first = make_node(&a);
    first->next = make_node(&b);
    g_calls = 0;
    ft_lstiter(first, add_ten);
    ft_lstiter(first, add_ten);
    CHECK(a == 20 && b == 10, "two calls: mutations accumulate");
    CHECK(g_calls == 4, "two calls: two nodes visited twice");
    free_nodes_only(first);
}

static void test_null_content(void)
{
    int x = 3;
    t_list *first = make_node(NULL);
    first->next = make_node(&x);
    g_calls = 0;
    ft_lstiter(first, count_call);
    CHECK(g_calls == 2, "NULL content: callback still invoked for node");
    g_calls = 0;
    ft_lstiter(first, add_ten);
    CHECK(g_calls == 2 && x == 13, "NULL-aware callback: skips data safely");
    free_nodes_only(first);
}

static void test_strings(void)
{
    char a[] = "hello", b[] = "42 network", c[] = "";
    t_list *first = make_node(a);
    first->next = make_node(b);
    first->next->next = make_node(c);
    ft_lstiter(first, uppercase_ascii);
    CHECK(strcmp(a, "HELLO") == 0, "mutable string: uppercase first");
    CHECK(strcmp(b, "42 NETWORK") == 0, "mutable string: uppercase second");
    CHECK(strcmp(c, "") == 0, "empty string stays empty");
    free_nodes_only(first);
}

static void test_noop_and_head(void)
{
    int x = 123, y = 456;
    t_list *first = make_node(&x);
    t_list *second = make_node(&y);
    t_list *head;
    first->next = second;
    head = first;
    ft_lstiter(head, noop);
    CHECK(head == first && head->next == second && second->next == NULL,
          "no-op: head and links unchanged");
    CHECK(x == 123 && y == 456, "no-op: content unchanged");
    free_nodes_only(first);
}

static void test_large_list(void)
{
    enum { N = 10000 };
    t_list *head = NULL;
    t_list *tail = NULL;
    int i;
    g_calls = 0;
    for (i = 0; i < N; i++)
    {
        t_list *new_node = make_node(NULL);
        if (tail)
            tail->next = new_node;
        else
            head = new_node;
        tail = new_node;
    }
    ft_lstiter(head, count_call);
    CHECK(g_calls == N, "10,000 nodes: correct number of visits");
    CHECK(tail->next == NULL, "10,000 nodes: tail unchanged");
    free_nodes_only(head);
}

int main(void)
{
    puts("=== ft_lstiter tests ===");
    test_null_and_empty();
    test_one_node();
    test_many_nodes_and_order();
    test_repeated_calls();
    test_null_content();
    test_strings();
    test_noop_and_head();
    test_large_list();
    if (g_failures)
        printf("\n%d test(s) FAILED\n", g_failures);
    else
        puts("\nALL TESTS PASSED");
    return (g_failures != 0);
}
