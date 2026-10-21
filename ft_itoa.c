/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:19:04 by aziati            #+#    #+#             */
/*   Updated: 2026/10/21 15:52:50 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include<stdlib.h>
#include <stdio.h>

int	count_digits(long	n)
{
	int	i;
	long	l;
	l = n;
	i = 0;
	if (l == 0)
		return (1);
	if (l < 0)
		l = -l;
	while (l > 0)
	{
		l = l / 10;
		i++;
	}
	return (i);
}
char	*ft_itoa(int	n)
{
	int	signe;
	long	nb;
	char	*p;
	int	i;
	int	len;
	int	original_len;

	nb = n;
	len = count_digits(nb);
	original_len = len;
	signe = 0;
	i = 0;
	if (nb < 0)
		signe = 1;
	p = malloc((len + signe + 1) * sizeof(char));
	if (!p)
		return (NULL);
	if (nb == 0)
	{
		p[0] = '0';
		p[1] = '\0';
		return (p);
	}
	if (nb < 0)
	{
		p[0] = '-';
		nb = -nb;
		while (nb > 0)
		{
			p[len + signe - 1] = (nb % 10) + '0';
			nb = nb / 10;
			len--;
		}
		p[original_len + signe] = '\0';
	}
	else
	{
		while (nb > 0)
		{
			p[len - 1] = (nb % 10) + '0';
			nb = nb / 10;
			len--;
		}
	p[original_len] = '\0';
	}
	return (p);
}
