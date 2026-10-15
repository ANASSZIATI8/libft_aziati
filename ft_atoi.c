/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:09:08 by aziati            #+#    #+#             */
/*   Updated: 2026/10/15 16:39:43 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int results;
	char *s;

	results = 0;
	signe = 1;
	i = 0;
	s = (char *)str;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if ( str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		results = results * 10 + (s[i] - '0');
		i++;
	}
	return (signe * results);
}
int main()
{
	printf("INT_MAX: %d\n", ft_atoi("2147483647"));
printf("INT_MIN: %d\n", ft_atoi("-2147483648"));
printf("LONG_MAX: %d\n", ft_atoi("9223372036854775807"));
printf("LONG_MIN: %d\n", ft_atoi("-9223372036854775808"));
printf("HUGE: %d\n", ft_atoi("999999999999999999999"));
//-------------------------------------------------------
printf("INT_MAX: %d\n", atoi("2147483647"));
printf("INT_MIN: %d\n", atoi("-2147483648"));
printf("LONG_MAX: %d\n", atoi("9223372036854775807"));
printf("LONG_MIN: %d\n", atoi("-9223372036854775808"));
printf("HUGE: %d\n", atoi("999999999999999999999"));
}