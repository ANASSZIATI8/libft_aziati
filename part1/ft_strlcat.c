/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:05:52 by aziati            #+#    #+#             */
/*   Updated: 2026/10/19 17:25:56 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlcat(char *dst,
	const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srcsize;

	i = 0;
	dstlen = 0;
	srcsize = 0;

	while (src[i])
	{
		srcsize++;
		i++;
	}
	i = 0;
	if (dstsize == 0)
		return (srcsize);
	i = 0;
	while (i < dstsize && dst[i])
	{
		dstlen++;
		i++;
	}
	if (dstlen == dstsize)
		return (dstsize + srcsize);
	i = 0;
	while (src[i] && i < dstsize - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srcsize);
}
