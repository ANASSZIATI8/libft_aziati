/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 15:53:55 by aziati            #+#    #+#             */
/*   Updated: 2026/10/21 21:41:44 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*results;
	unsigned int	i;
	
	if (!s || !f)
		return (NULL);
	results = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!results)
		return (NULL);
	i = 0;
	while (s[i])
	{
		results[i] = f(i, s[i]);
		i++;
	}
	results[i] = '\0';
	return (results);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char	to_upper(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static char	to_lower(unsigned int i, char c)
{
	(void)i;
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

static char	replace_even(unsigned int i, char c)
{
	if (i % 2 == 0)
		return ('X');
	return (c);
}

static char	replace_odd(unsigned int i, char c)
{
	if (i % 2 != 0)
		return ('Z');
	return (c);
}

static char	identity(unsigned int i, char c)
{
	(void)i;
	return (c);
}

static char	shift_by_index(unsigned int i, char c)
{
	return (c + i);
}

static char	make_null(unsigned int i, char c)
{
	(void)c;
	if (i == 1)
		return ('\0');
	return ('A');
}

static void	test(char *name, const char *s,
		char (*f)(unsigned int, char), const char *expected)
{
	char	*result;

	result = ft_strmapi(s, f);
	if (!result)
	{
		printf("FAIL | %s | returned NULL\n", name);
		return ;
	}
	if (strcmp(result, expected) == 0)
		printf("PASS | %s | got: \"%s\"\n", name, result);
	else
		printf("FAIL | %s | expected: \"%s\" | got: \"%s\"\n",
			name, expected, result);
	free(result);
}

int	main(void)
{
	char		*result;
	char		original[] = "hello";

	printf("\n===== UPPERCASE =====\n");
	test("basic", "hello", to_upper, "HELLO");
	test("mixed", "HeLLo42", to_upper, "HELLO42");
	test("symbols", "hi! 42?", to_upper, "HI! 42?");

	printf("\n===== LOWERCASE =====\n");
	test("basic", "HELLO", to_lower, "hello");
	test("mixed", "HeLLo", to_lower, "hello");

	printf("\n===== INDEX CALLBACK =====\n");
	test("even", "hello", replace_even, "XeXlX");
	test("odd", "hello", replace_odd, "hZlZo");
	test("single", "a", replace_even, "X");
	test("shift", "aaaa", shift_by_index, "abcd");

	printf("\n===== EDGE CASES =====\n");
	test("empty", "", to_upper, "");
	test("one char", "z", to_upper, "Z");
	test("spaces", "   ", identity, "   ");
	test("digits", "12345", identity, "12345");
	test("unchanged", "libft", identity, "libft");

	printf("\n===== ORIGINAL STRING =====\n");
	result = ft_strmapi(original, to_upper);
	if (result && strcmp(original, "hello") == 0
		&& strcmp(result, "HELLO") == 0 && result != original)
		printf("PASS | original unchanged and new memory\n");
	else
		printf("FAIL | original string / allocation\n");
	free(result);

	printf("\n===== EMBEDDED NULL =====\n");
	result = ft_strmapi("hello", make_null);
	if (result && result[0] == 'A' && result[1] == '\0'
		&& result[2] == 'A' && result[3] == 'A'
		&& result[4] == 'A' && result[5] == '\0')
		printf("PASS | callback returns null character\n");
	else
		printf("FAIL | callback returns null character\n");
	free(result);

	printf("\n===== NULL INPUTS =====\n");
	result = ft_strmapi(NULL, to_upper);
	printf("%s | NULL string\n", result == NULL ? "PASS" : "FAIL");
	free(result);

	result = ft_strmapi("hello", NULL);
	printf("%s | NULL callback\n", result == NULL ? "PASS" : "FAIL");
	free(result);

	result = ft_strmapi(NULL, NULL);
	printf("%s | both NULL\n", result == NULL ? "PASS" : "FAIL");
	free(result);

	return (0);
}
