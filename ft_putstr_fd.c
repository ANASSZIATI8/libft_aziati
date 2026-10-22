/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 21:57:07 by aziati            #+#    #+#             */
/*   Updated: 2026/10/21 22:49:50 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
void	ft_putchar(char c, int fd);
void	ft_putstr_fd(char *s, int fd)
{
	int i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i], fd);
		i++;
	}
	
}
