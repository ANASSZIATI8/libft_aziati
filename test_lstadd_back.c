
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int g_pass = 0;
static int g_fail = 0;

static void	check(int condition, const char *name)
{
	if (condition)
	{
		printf("PASS | %s\n", name);
		g_pass++;
	}
	else
	{
		printf("FAIL | %s\n", name);
		g_fail++;
	}
}

/*
** Verifies exact node addresses and their order.
** Also checks that the last node points to NULL.
** Stops safely if a wrong node is encountered.
*/
static int	check_chain(t_list *head, t_list **expected, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!head || head != expected[i])
			return (0);
		head = head->next;
		i++;
	}
	return (head == NULL);
}

static void	test_empty_list(void)
{
	t_list	*head;
	t_list	*a;
	t_list	*expected[1];

	head = NULL;
	a = ft_lstnew("A");
	if (!a)
		exit(1);
	expected[0] = a;
	ft_lstadd_back(&head, a);
	check(check_chain(head, expected, 1), "Empty list + A");
	check(head == a, "Head points to A");
	check(a->next == NULL, "A->next is NULL");
	free(a);
}

static void	test_one_node(void)
{
	t_list	*head;
	t_list	*a;
	t_list	*b;
	t_list	*expected[2];

	a = ft_lstnew("A");
	b = ft_lstnew("B");
	if (!a || !b)
		exit(1);
	head = a;
	expected[0] = a;
	expected[1] = b;
	ft_lstadd_back(&head, b);
	check(check_chain(head, expected, 2), "A -> B -> NULL");
	check(head == a, "Original head preserved");
	check(a->next == b, "A->next points to B");
	check(b->next == NULL, "B->next is NULL");
	free(a);
	free(b);
}

static void	test_multiple_nodes(void)
{
	t_list	*head;
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*d;
	t_list	*expected[4];

	a = ft_lstnew("A");
	b = ft_lstnew("B");
	c = ft_lstnew("C");
	d = ft_lstnew("D");
	if (!a || !b || !c || !d)
		exit(1);
	a->next = b;
	b->next = c;
	head = a;
	expected[0] = a;
	expected[1] = b;
	expected[2] = c;
	expected[3] = d;
	ft_lstadd_back(&head, d);
	check(check_chain(head, expected, 4),
		"A -> B -> C -> D -> NULL");
	check(head == a, "Multi-node head preserved");
	check(c->next == d, "C connected to D");
	check(d->next == NULL, "D is last");
	free(a);
	free(b);
	free(c);
	free(d);
}

static void	test_null_arguments(void)
{
	t_list	*head;
	t_list	*a;

	head = NULL;
	ft_lstadd_back(NULL, NULL);
	check(head == NULL, "Both arguments NULL");

	ft_lstadd_back(&head, NULL);
	check(head == NULL, "new is NULL, empty head");

	a = ft_lstnew("A");
	if (!a)
		exit(1);
	head = a;
	ft_lstadd_back(&head, NULL);
	check(head == a && a->next == NULL,
		"new is NULL, existing list unchanged");

	ft_lstadd_back(NULL, a);
	check(head == a && a->next == NULL,
		"lst is NULL, existing node unchanged");
	free(a);
}

static void	test_sequential_insertions(void)
{
	t_list	*head;
	t_list	*nodes[10];
	int		i;
	int		ok;

	head = NULL;
	i = 0;
	while (i < 10)
	{
		nodes[i] = ft_lstnew("1337");
		if (!nodes[i])
			exit(1);
		ft_lstadd_back(&head, nodes[i]);
		i++;
	}
	ok = check_chain(head, nodes, 10);
	check(ok, "10 sequential insertions");
	check(head == nodes[0], "First node remains head");
	check(nodes[9]->next == NULL, "Tenth node is last");
	i = 0;
	while (i < 10)
		free(nodes[i++]);
}

static void	test_existing_chain(void)
{
	t_list	*head;
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*d;
	t_list	*expected[4];

	a = ft_lstnew("A");
	b = ft_lstnew("B");
	c = ft_lstnew("C");
	d = ft_lstnew("D");
	if (!a || !b || !c || !d)
		exit(1);
	a->next = b;
	c->next = d;
	head = a;
	expected[0] = a;
	expected[1] = b;
	expected[2] = c;
	expected[3] = d;
	ft_lstadd_back(&head, c);
	check(check_chain(head, expected, 4),
		"Append chain C -> D to A -> B");
	check(c->next == d, "Existing chain preserved");
	free(a);
	free(b);
	free(c);
	free(d);
}

static void	test_chain_into_empty(void)
{
	t_list	*head;
	t_list	*a;
	t_list	*b;
	t_list	*expected[2];

	a = ft_lstnew("A");
	b = ft_lstnew("B");
	if (!a || !b)
		exit(1);
	a->next = b;
	head = NULL;
	expected[0] = a;
	expected[1] = b;
	ft_lstadd_back(&head, a);
	check(check_chain(head, expected, 2),
		"Append A -> B into empty list");
	check(a->next == b, "Chain link preserved");
	free(a);
	free(b);
}

int	main(void)
{
	printf("\n===== EMPTY LIST =====\n");
	test_empty_list();

	printf("\n===== ONE NODE =====\n");
	test_one_node();

	printf("\n===== MULTIPLE NODES =====\n");
	test_multiple_nodes();

	printf("\n===== NULL ARGUMENTS =====\n");
	test_null_arguments();

	printf("\n===== SEQUENTIAL INSERTIONS =====\n");
	test_sequential_insertions();

	printf("\n===== EXISTING CHAIN =====\n");
	test_existing_chain();

	printf("\n===== CHAIN INTO EMPTY LIST =====\n");
	test_chain_into_empty();

	printf("\n============================\n");
	printf("PASSED: %d\n", g_pass);
	printf("FAILED: %d\n", g_fail);
	printf("TOTAL:  %d\n", g_pass + g_fail);
	printf("============================\n");
	return (g_fail != 0);
}
