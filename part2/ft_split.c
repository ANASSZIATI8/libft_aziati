/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 13:28:27 by aziati            #+#    #+#             */
/*   Updated: 2026/10/27 11:44:08 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static int	ft_count_words(char const *s, char c)
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

static int	ft_end(char const *s, char c, int i)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_free_fun(char **p, size_t pos)
{
	size_t	i;

	i = 0;
	while (i < pos)
		free(p[i++]);
	free(p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		end;
	int		i;
	int		pos;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	p = malloc((count + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < count)
	{
		while (s[pos] && s[pos] == c)
			pos++;
		end = ft_end(s, c, pos) - pos;
		p[i] = ft_substr(s, pos, end);
		if (!p[i])
		{
			ft_free_fun(p, i);
			return (NULL);
		}
		pos += end;
		i++;
	}
	p[i] = NULL;
	return (p);
}
