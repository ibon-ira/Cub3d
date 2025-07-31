/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:01:59 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/11 15:42:42 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while ((src[i] && src[i] != '\0') && i < dstsize - 1 && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
	{
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*int main()
{
	int	n = 100;
	
    char src[] = "lorem ipsum";
    char dst[] = "aaaaaaaaaaaaaaaaaaaaaaaa";
	
    printf("ft: 		%lu\n", ft_strlcpy(dst, src, n));
	ft_strlcpy(dst, src, n);
	printf("%s\n", dst);

	char src2[] = "lorem ipsum";
    char dst2[] = "aaaaaaaaaaaaaaaaaaaaaaaa";
	printf("original: 	%lu\n", strlcpy(dst2, src2, n));
	strlcpy(dst2, src2, n);
	
	printf("%s", dst2);
    return(0);
}*/