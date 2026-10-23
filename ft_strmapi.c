/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 15:53:55 by aziati            #+#    #+#             */
/*   Updated: 2026/10/23 21:04:56 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*results;
	unsigned int	 i;
	
	if (!s || !f)
		return ;
	results = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!results)
		return (NULL);
	i = 0;
	while (s[i])
	{
		results[i] = f(i, s[i]);
		i++;
	}
	results[i] = '\0';
	return (results);
}
