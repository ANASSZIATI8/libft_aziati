/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:35:48 by aziati            #+#    #+#             */
/*   Updated: 2026/10/26 23:05:58 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lstsize(t_list *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	i++;
	return (i);
}
