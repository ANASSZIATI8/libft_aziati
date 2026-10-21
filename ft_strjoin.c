/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 21:05:47 by aziati            #+#    #+#             */
/*   Updated: 2026/10/18 23:30:39 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;
	size_t	j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	p = malloc((s1_size + s2_size + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < s1_size && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
