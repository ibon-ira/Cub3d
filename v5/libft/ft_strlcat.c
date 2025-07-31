/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:11:28 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/03 18:35:32 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	str;

	index = -1;
	while (++index < dstsize && *dst)
		dst++;
	str = ft_strlcpy(dst, src, dstsize - index);
	return (str + index);
}
/*int main()
{
	char dest[11] = "a";
    printf("Original: %zu", (ft_strlcat(dest, "lorem", 15)));
	return (0);
}*/