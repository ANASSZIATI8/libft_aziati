/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 16:46:30 by aziati            #+#    #+#             */
/*   Updated: 2026/10/13 10:49:50 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *p, int c, size_t len)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)p;
	while (i < len)
	{
		b[i] = c;
		i++;
	}
	return (p);
}
