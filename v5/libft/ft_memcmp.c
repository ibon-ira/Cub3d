/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:15:08 by iksaiz-m          #+#    #+#             */
/*   Updated: 2023/12/20 13:24:53 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s1)[i]) != ((unsigned char *)s2)[i])
		{
			return ((((unsigned char *)s1)[i]) - ((unsigned char *)s2)[i]);
		}
		i++;
	}
	return (0);
}
/*int main()
{
	const char s1[] = "abcdefghij";
	const char s2[] = "abcdefgxyz";
	printf("ft: %d\n", ft_memcmp(s1, s2, 5));
	printf("original: %d", memcmp(s1, s2, 7));
	return(0);
}*/