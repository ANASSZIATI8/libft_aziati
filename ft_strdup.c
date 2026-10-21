/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 21:40:07 by aziati            #+#    #+#             */
/*   Updated: 2026/10/16 16:17:55 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
char	*ft_strdup(const char *s1)
{
	int	i;
	int	size;
	char *str;

	i = 0;
	size = 0;
	while (s1[i])
	{
		i++;
		size++;
	}
	str = malloc ((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
