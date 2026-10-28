/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:19:04 by aziati            #+#    #+#             */
/*   Updated: 2026/10/28 20:47:18 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(unsigned int n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	size_t			len;
	char			*p;

	nb = n;
	if (n < 0)
		nb = 0U - nb;
	len = count_digits(nb) + (n < 0);
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	p[len] = '\0';
	if (n < 0)
		p[0] = '-';
	while (len > (size_t)(n < 0))
	{
		p[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (p);
}
