/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:09:08 by aziati            #+#    #+#             */
/*   Updated: 2026/10/28 21:25:13 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	check_
int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	int		degits;
	long	results;

	results = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		degits = str[i] + '0';
		if (results > (LONG_MAX - degits) / 10)
			return (-1);
		results = results * 10 + (str[i] - '0');
		i++;
	}
	return (signe * results);
}
