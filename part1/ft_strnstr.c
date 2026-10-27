/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 13:43:32 by aziati            #+#    #+#             */
/*   Updated: 2026/10/27 02:44:05 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	
	if (needle[0] == '\0')
		return ((char *)&haystack[0]);
	while (i < len && haystack[i])
	{
		j = 0;
		while (i + j < len && haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}


#include <stdio.h>
#include <string.h>
#include <stddef.h>

// char *ft_strnstr(const char *haystack, const char *needle, size_t len);

// void test(const char *haystack, const char *needle, size_t len)
// {
//     char *expected = strnstr(haystack, needle, len);
//     char *actual = ft_strnstr(haystack, needle, len);

//     printf("haystack=\"%s\" | needle=\"%s\" | len=%zu\n",
//         haystack, needle, len);

//     printf("Expected: %s\n", expected ? expected : "NULL");
//     printf("Actual:   %s\n", actual ? actual : "NULL");

//     if (actual == expected)
//         printf("✅ OK\n");
//     else
//         printf("❌ KO\n");

//     printf("-----------------------------\n");
// }

// int main(void)
// {
//    char str[] = "NULL";
//    //char need[] = "lkk";
//    printf("%s\n",strnstr(str,NULL,6));
   

//     return (0);
// }
