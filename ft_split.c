/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 13:28:27 by aziati            #+#    #+#             */
/*   Updated: 2026/10/19 21:16:13 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
char	*ft_substr(char const *s, unsigned int start, size_t len);

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

int	ft_end(char const *s, char c, int	i)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
char	*ft_malloc(int start, int end)
{
	char *p;

	p = malloc((end - start + 1) * sizeof(char));
	if (!p)
		return (NULL);
	return (p);
}
void	ft_free_fun(char **p, size_t pos)
{
	size_t	i;
	i = 0;
	while (i < pos)
		free(p[--i]);
	free(p);
}
char	**ft_split(char const *s, char c)
{
	char **p;

	int	end;
	int	i;
	int pos;
	if (!s)
		return (NULL);
	p = malloc (((ft_count_words(s, c) + 1) * sizeof(char *) + 1));
	if (!p)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < ft_count_words(s, c))
	{
		while (s[pos] && s[pos] == c)
			pos++;
		end = ft_end(s, c, pos) - pos;
		printf("%d\n",end);
		p[i] = ft_substr(s,pos , end);
		if (!p[i])
		{
			ft_free_fun(p, i);
			return (NULL);
		}
			
		pos += end;
		i++;
	}
	p[ft_count_words(s, c)] = NULL;

	return (p);
}
