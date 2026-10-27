#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BIG_N 1000
static int calls, deleted, checks, failures, fail_at, node_allocs;

#ifdef TEST_WRAP_MALLOC
void *__real_malloc(size_t n);
void *__wrap_malloc(size_t n)
{
    if (n == sizeof(t_list))
    {
        ++node_allocs;
        if (fail_at == node_allocs)
            return (NULL);
    }
    return (__real_malloc(n));
}
#endif

static void reset_counters(void)
{
    calls = 0;
    deleted = 0;
    fail_at = 0;
    node_allocs = 0;
}

static void check(const char *name, int ok)
{
    ++checks;
    if (!ok)
        ++failures;
    printf("%s %s\n", ok ? "PASS" : "FAIL", name);
}

static void *copy_int(void *p)
{
    int *n;
    ++calls;
    n = malloc(sizeof(*n));
    if (!n)
        return (NULL);
    *n = p ? *(int *)p : 0;
    return (n);
}

static void *negate_int(void *p)
{
    int *n;
    ++calls;
    n = malloc(sizeof(*n));
    if (!n)
        return (NULL);
    *n = -*(int *)p;
    return (n);
}

static void delete_int(void *p)
{
    ++deleted;
    free(p);
}

static void build(t_list *nodes, int *values, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        nodes[i].content = &values[i];
        nodes[i].next = i + 1 < n ? &nodes[i + 1] : NULL;
    }
}

static int matches(t_list *head, const int *expected, int n)
{
    int i = 0;
    while (head && i < n)
    {
        if (!head->content || *(int *)head->content != expected[i])
            return (0);
        head = head->next;
        ++i;
    }
    return (i == n && !head);
}

static int independent(t_list *out, t_list *original, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        if (!out || out == &original[i] || out->content == original[i].content)
            return (0);
        out = out->next;
    }
    return (!out);
}

static void normal_tests(void)
{
    int values[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN};
    int expected[] = {0, 1, -1, 42, -42, INT_MAX, INT_MIN};
    t_list original[7];
    t_list *out;
    t_list *walk;
    int i;
    int src_ok;

    reset_counters();
    out = ft_lstmap(NULL, copy_int, delete_int);
    check("NULL list returns NULL", out == NULL);
    check("NULL list never calls f or del", calls == 0 && deleted == 0);

    build(original, values, 7);
    reset_counters();
    out = ft_lstmap(original, copy_int, delete_int);
    check("7 nodes: zero, signs and INT limits", matches(out, expected, 7));
    check("f called once for each node", calls == 7);
    check("original nodes and contents unchanged", matches(original, expected, 7));
    check("new nodes and content addresses independent", independent(out, original, 7));
    src_ok = out != NULL;
    walk = out;
    for (i = 0; i < 7 && walk; ++i)
    {
        if (walk->next == walk)
            src_ok = 0;
        walk = walk->next;
    }
    check("no self-link and list ends at NULL", src_ok && walk == NULL);
    if (out)
    {
        *(int *)out->content = 777;
        check("mutating mapped value does not alter original", values[0] == 0);
    }
    else
        check("mutating mapped value does not alter original", 0);
    ft_lstclear(&out, delete_int);
    check("clear frees all 7 contents and resets head", deleted == 7 && out == NULL);
    check("original list usable after mapped list freed", matches(original, expected, 7));


}

static void focused_tests(void)
{
    int vals[] = {5, -6};
    int neg[] = {-5, 6};
    int zero = 0;
    t_list two[2], one;
    t_list *out;
    reset_counters();
    build(two, vals, 2);
    out = ft_lstmap(two, negate_int, delete_int);
    check("mapper transforms both values and preserves order", matches(out, neg, 2));
    check("negate mapper called exactly twice", calls == 2);
    ft_lstclear(&out, delete_int);
    check("two mapped values freed", deleted == 2);

    one.content = &zero;
    one.next = NULL;
    reset_counters();
    out = ft_lstmap(&one, copy_int, delete_int);
    check("single node maps correctly", matches(out, &zero, 1) && calls == 1);
    ft_lstclear(&out, delete_int);
    check("single mapped node cleaned", deleted == 1);

    one.content = NULL;
    reset_counters();
    out = ft_lstmap(&one, copy_int, delete_int);
    check("NULL content supported by NULL-aware callback", matches(out, &zero, 1));
    ft_lstclear(&out, delete_int);
}

static void large_test(void)
{
    int values[BIG_N];
    t_list nodes[BIG_N];
    t_list *out;
    int i;
    for (i = 0; i < BIG_N; ++i)
        values[i] = i;
    build(nodes, values, BIG_N);
    reset_counters();
    out = ft_lstmap(nodes, copy_int, delete_int);
    check("1000-node map order and data", matches(out, values, BIG_N));
    check("1000-node f call count", calls == BIG_N);
    ft_lstclear(&out, delete_int);
    check("1000-node cleanup", deleted == BIG_N && out == NULL);
}

static void allocation_tests(void)
{
#ifdef TEST_WRAP_MALLOC
    int nums[10], pos, i;
    t_list nodes[10], *out;
    char label[100];
    for (i = 0; i < 10; ++i)
        nums[i] = i + 1;
    build(nodes, nums, 10);
    for (pos = 1; pos <= 10; ++pos)
    {
        reset_counters();
        fail_at = pos;
        out = ft_lstmap(nodes, copy_int, delete_int);
        snprintf(label, sizeof(label), "malloc fails at node %d: returns NULL and frees %d contents", pos, pos);
        check(label, out == NULL && calls == pos && deleted == pos && node_allocs == pos);
        if (out)
        {
            fail_at = 0;
            ft_lstclear(&out, delete_int);
        }
    }
    reset_counters();
    fail_at = 11;
    out = ft_lstmap(nodes, copy_int, delete_int);
    check("malloc fail point beyond list: successful map", matches(out, nums, 10) && calls == 10);
    ft_lstclear(&out, delete_int);
#else
    puts("SKIP node malloc failures (add -DTEST_WRAP_MALLOC -Wl,--wrap=malloc)");
#endif
}

int main(void)
{
    normal_tests();
    focused_tests();
    large_test();
    allocation_tests();
    printf("\nRESULT: %d/%d passed\n", checks - failures, checks);
    return (failures != 0);
}
