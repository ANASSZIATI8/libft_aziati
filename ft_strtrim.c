/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 23:32:40 by aziati            #+#    #+#             */
/*   Updated: 2026/10/19 13:20:58 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

size_t    ft_strlen(const char *str)
{
    size_t    i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
}

char    *ft_strchr(const char *s, int c)
{
    int    i;

    i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
        {
            return ((char *)&s[i]);
        }
        i++;
    }
    if (c == '\0')
        return ((char *)&s[i]);
    return (NULL);
}
size_t	ft_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set,s1[i]))
		i++;
	return (i);
}
size_t	ft_end(char const *s1, char const *set)
{
	size_t	size;

	size = ft_strlen(s1);
	while (size > 0 && ft_strchr(set,s1[size - 1]))
		size--;
	return (size);
}
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char *reseult;
	size_t	j;
	size_t	start;
	size_t	end;
	if (!s1 || !set)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start > end)
		end = start;
	reseult = malloc((end - start + 1) * sizeof(char));
	if (!reseult)
		return (NULL);
	i = ft_start(s1,set);
	j = 0;
	while (s1[i] && i < ft_end(s1, set))
		reseult[j++] = s1[i++];
	reseult[j] = '\0';
	return (reseult);
}
