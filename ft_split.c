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

static	int	ft_start(char *str,	char c, int i)
{
	while (str[i] && str[i] == c)
		i++;
	return (i);
}
static	int	ft_end(char *str, char c, int i)
{
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
static	int	ft_wordlen(char *str, char c, int i)
{
	int	start;
	int	end;
	start = ft_start(str, c, i);
	end = ft_end(str, c, i);
	return (end - start);
}
static int	count_words(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;

	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			while (str[i] && str[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}
static char *ft_extract_word(const char *s, int start, int len)
{
	char *word;
	
	int	i;
	i = 0;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (s[start] && i < len)
	{
		word[i++] = s[start++];
	}
	word[i] = '\0';
	return (word);
}
static	void	ft_free(char **p, int	j)
{
	while (j > 0)
	{
		j--;
		free(p[j]);
	}
	free(p);
}
char	**ft_split(char const *s, char c)
{
	int	i;
	char **p;
	int start;
	int	len;
	int	j;
	if (!s)
		return (NULL);
	p = malloc((count_words(s,c) + 1) * (sizeof(char*)));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		len = i - start;
		p[j] = ft_extract_word(s, start, len);
		if (!p[j])
		{
			ft_free(p, j);
			return(NULL);
		}
		j++;
	}
	p[j] = NULL;
	return (p);
}
int main()
{
	char tab[] = "    hello world hello";
	int results = count_words(tab, ' ');
	printf("%d",results);
}
