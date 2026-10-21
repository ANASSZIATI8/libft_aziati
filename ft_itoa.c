/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:19:04 by aziati            #+#    #+#             */
/*   Updated: 2026/10/21 14:09:57 by aziati           ###   ########.fr       */
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
	char	*p;
	int	i;
	int	len;
	int	original_len;

	len = count_digits(n);
	original_len = len;
	signe = 0;
	i = 0;
	if (n < 0)
		signe = 1;
	p = malloc((len + signe + 1) * sizeof(char));
	if (!p)
		return (NULL);
	if (n == 0)
	{
		p[0] = '0';
		p[1] = '\0';
		return (p);
	}
	if (n < 0)
	{
		p[0] = '-';
		i++;
		while (n < 0)
		{
			p[i] = n % 10 + '0';
			n = n / 10;
			i++;
		}
		p[i] = '\0';
	}
	else
	{
		while (n > 0)
		{
			p[len - 1] = (n % 10) + '0';
			n = n / 10;
			len--;
		}
	p[original_len] = '\0';
	}
	return (p);
}
int  main()
{
	printf("%s",ft_itoa(123));
}