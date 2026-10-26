/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 13:59:12 by aziati            #+#    #+#             */
/*   Updated: 2026/10/25 11:10:02 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_lstdelone(t_list *lst, void(*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	del(lst->next);
	lst->content = NULL;
}
