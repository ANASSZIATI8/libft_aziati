/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 18:38:48 by aziati            #+#    #+#             */
/*   Updated: 2026/10/27 10:59:31 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int len;

	len = 0;
	i = 0;
	while (s[i])
	{
		len++;
		i++;
	}
	while (len > 0)
	{
		len --;
		if (s[len] == (char)c)
			return ((char *)&s[len]);
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
