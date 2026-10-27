/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziati <aziati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:10:28 by aziati            #+#    #+#             */
/*   Updated: 2026/10/27 02:53:15 by aziati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == 0 || size == 0)
	{
		p = malloc (1);
		if (p == NULL)
			return (NULL);
		ft_bzero(p,1);
		return (p);
	}
	if (count  > (SIZE_MAX / size))
		return (NULL);
	p = malloc (count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>
// #include <limits.h>


// static void test_calloc(const char *name, size_t count, size_t size)
// {
//     void *real;
//     void *mine;
//     size_t total;
//     int ok;
//     int overflow;

//     overflow = (size != 0 && count > SIZE_MAX / size);
//     real = calloc(count, size);
//     mine = ft_calloc(count, size);
//     ok = 1;

//     if (overflow)
//         ok = (real == NULL && mine == NULL);
//     else if (count == 0 || size == 0)
//     {
//         /* Zero-size behavior can vary by implementation. */
//         ok = 1;
//     }
//     else
//     {
//         total = count * size;
//         if ((real == NULL) != (mine == NULL))
//             ok = 0;
//         else if (real != NULL && mine != NULL)
//         {
//             if (memcmp(real, mine, total) != 0)
//                 ok = 0;
//         }
//     }

//     printf("[%s] %s\n", ok ? "OK" : "FAIL", name);
//     free(real);
//     free(mine);
// }

// int main(void)
// {
//     test_calloc("1. Single integer", 1, sizeof(int));
//     test_calloc("2. Array of 10 integers", 10, sizeof(int));
//     test_calloc("3. Array of 100 integers", 100, sizeof(int));
//     test_calloc("4. Array of 50 chars", 50, sizeof(char));
//     test_calloc("5. Array of 10 doubles", 10, sizeof(double));
//     test_calloc("6. Large allocation", 100000, sizeof(int));

//     test_calloc("7. Zero count", 0, 10);
//     test_calloc("8. Zero size", 10, 0);
//     test_calloc("9. Both zero", 0, 0);

//     test_calloc("10. Overflow", SIZE_MAX, 2);
//     test_calloc("11. Overflow", SIZE_MAX / 2 + 1, 2);
//     test_calloc("12. Overflow", SIZE_MAX, SIZE_MAX);

//     test_calloc("13. One byte", 1, 1);
//     test_calloc("14. Odd size", 7, 3);
//     test_calloc("15. Many elements", 1024, 8);

//     return (0);
// }
