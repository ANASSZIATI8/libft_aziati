/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:10:28 by aziati            #+#    #+#             */
/*   Updated: 2026/10/28 20:38:58 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*p;
	size_t		total;

	if (size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	total = count * size;
	if (total == 0)
		total = 1;
	p = malloc (total);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}
