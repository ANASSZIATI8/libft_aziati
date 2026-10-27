#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

static int g_calls;
static int g_deleted;
static int g_fail_node_at;
static int g_nodes_allocated;

#ifdef TEST_WRAP_MALLOC
void *__real_malloc(size_t size);
void *__wrap_malloc(size_t size)
{
    if (size == sizeof(t_list))
    {
        ++g_nodes_allocated;
        if (g_fail_node_at == g_nodes_allocated)
            return NULL;
    }
    return __real_malloc(size);
}
#endif

static void *double_copy(void *ptr)
{
    int *out;
    ++g_calls;
    out = malloc(sizeof(*out));
    if (!out)
        return NULL;
    *out = *(int *)ptr * 2;
    return out;
}

static void *identity_copy(void *ptr)
{
    int *out;
    ++g_calls;
    out = malloc(sizeof(*out));
    if (!out)
        return NULL;
    *out = *(int *)ptr;
    return out;
}

static void count_free(void *ptr)
{
    ++g_deleted;
    free(ptr);
}

static void reset(void)
{
    g_calls = 0;
    g_deleted = 0;
    g_fail_node_at = 0;
    g_nodes_allocated = 0;
}

static int check_values(t_list *list, const int *expected, size_t n)
{
    size_t i = 0;
    while (list && i < n)
    {
        if (!list->content || *(int *)list->content != expected[i])
            return 0;
        list = list->next;
        ++i;
    }
    return i == n && list == NULL;
}

static void report(const char *label, int pass)
{
    printf("%s %s\n", pass ? "PASS" : "FAIL", label);
}

static void run_normal_tests(void)
{
    int xs[5] = {5, 6, 0, -7, INT_MAX / 2};
    int doubled[5] = {10, 12, 0, -14, (INT_MAX / 2) * 2};
    t_list a[5];
    t_list *out;
    t_list *walk;
    size_t i;
    int independent;

    reset();
    out = ft_lstmap(NULL, double_copy, count_free);
    report("NULL input returns NULL", out == NULL && g_calls == 0);

    for (i = 0; i < 5; ++i)
    {
        a[i].content = &xs[i];
        a[i].next = i + 1 < 5 ? &a[i + 1] : NULL;
    }
    reset();
    out = ft_lstmap(&a[0], double_copy, count_free);
    report("5 nodes: values, negatives, zero and order", check_values(out, doubled, 5));
    report("f called exactly once per node", g_calls == 5);
    report("original list unchanged", xs[0] == 5 && xs[1] == 6 && xs[2] == 0 && xs[3] == -7 && xs[4] == INT_MAX / 2
        && a[0].next == &a[1] && a[4].next == NULL);
    independent = 1;
    walk = out;
    for (i = 0; i < 5 && walk; ++i)
    {
        if (walk == &a[i] || walk->content == a[i].content)
            independent = 0;
        walk = walk->next;
    }
    report("new nodes and content are independent", out != NULL && independent);
    ft_lstclear(&out, count_free);
    report("cleanup frees 5 transformed contents", g_deleted == 5 && out == NULL);

    reset();
    out = ft_lstmap(&a[0], identity_copy, count_free);
    report("identity mapper preserves all values", check_values(out, xs, 5));
    ft_lstclear(&out, count_free);

    reset();
    out = ft_lstmap(&a[4], double_copy, count_free);
    report("single node", check_values(out, &doubled[4], 1) && g_calls == 1);
    ft_lstclear(&out, count_free);
}

static void run_allocation_failure_tests(void)
{
#ifdef TEST_WRAP_MALLOC
    int nums[3] = {1, 2, 3};
    t_list a[3];
    t_list *out;
    int pos;
    size_t i;
    for (i = 0; i < 3; ++i)
    {
        a[i].content = &nums[i];
        a[i].next = i + 1 < 3 ? &a[i + 1] : NULL;
    }
    for (pos = 1; pos <= 3; ++pos)
    {
        reset();
        g_fail_node_at = pos;
        out = ft_lstmap(&a[0], double_copy, count_free);
        printf("%s allocation failure at node %d (f calls=%d, del calls=%d)\n",
            out == NULL && g_deleted == pos ? "PASS" : "FAIL",
            pos, g_calls, g_deleted);
        if (out)
        {
            g_fail_node_at = 0;
            ft_lstclear(&out, count_free);
        }
    }
#else
    printf("SKIP malloc failure injection: compile with -DTEST_WRAP_MALLOC -Wl,--wrap=malloc\n");
#endif
}

int main(void)
{
    run_normal_tests();
    run_allocation_failure_tests();
    return 0;
}
