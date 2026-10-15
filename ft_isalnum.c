/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 15:35:02 by aziati            #+#    #+#             */
/*   Updated: 2026/10/12 17:07:10 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(char c);
int	ft_isdigit(char c);

int	ft_isalnum(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
