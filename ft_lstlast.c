/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 20:05:42 by aziati            #+#    #+#             */
/*   Updated: 2026/10/23 22:03:00 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int i;
	t_list	*result;
	
	result -> next =lst; 
	while (result->next)
	{
		result = result->next;
	}
	return (result);
}
