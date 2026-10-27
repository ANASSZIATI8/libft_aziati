/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 10:02:48 by aziati            #+#    #+#             */
/*   Updated: 2026/10/19 14:16:00 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	const unsigned char	*p;
	unsigned char	*t;

	i = 0;
	p = (const unsigned char *) src;
	t = (unsigned char *) dst;
	if (len == 0 || dst == src)
		return (dst);
	if (p > t)
	{
		while (i < len)
		{
			t[i] = p[i];
			i++;
		}
	}
	else if (p < t)
	{
 	 	while (len > 0)
		{
			len--;
			t[len] = p[len];
		}
	}
	return (dst);
}
