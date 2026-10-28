/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 11:42:22 by aziati            #+#    #+#             */
/*   Updated: 2026/10/28 21:58:07 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curent;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	curent = *lst;
	while (curent)
	{
		tmp = curent->next;
		ft_lstdelone(curent, del);
		curent = tmp;
	}
	*lst = NULL;
}
