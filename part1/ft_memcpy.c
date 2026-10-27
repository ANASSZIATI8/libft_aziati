/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 20:20:35 by aziati            #+#    #+#             */
/*   Updated: 2026/10/15 19:58:53 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p;
	const unsigned char	*t;

	i = 0;
	p = (unsigned char *) dst;
	t = (const unsigned char *) src;
	while (i < n)
	{
		p[i] = t[i];
		i++;
	}
	return (p);
}
