/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:53:16 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/04/14 19:24:09 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	dst_ptr = (unsigned char *) dst;
	src_ptr = (unsigned char *) src;
	if ((!dst) && (!src))
		return (NULL);
	if (src_ptr < dst_ptr)
	{
		while (len--)
			dst_ptr[len] = src_ptr[len];
	}
	else
	{
		return (ft_memcpy(dst, src, len));
	}
	return (dst);
}
/*int main ()
{
	char src[] = "jaime";
	char dst[] = "paco";
	printf("original: %s", memmove(dst, src, 5));
	printf("ft: %s", ft_memmove(dst, src, 5));
	return (0);
}*/