/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:54:38 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/04/14 19:22:13 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	a = (unsigned char *) dst;
	b = (unsigned char *) src;
	if (!a && !b)
		return (dst);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}

/*int main()
{
	const char src[] = "jaimi";
	char dst[10] = "poledance";
	printf("Original: %s", memcpy(dst , src, 6));
	printf("\nft: %s", ft_memcpy(dst , src, 6));
	return(0);
}*/