/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:53:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/04 16:04:13 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *) b)[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
/*int main()
{
	char buffer[] = "Girona";
   ft_memset( buffer, '_', 9);
   printf( "After:  %s\n", buffer );
   //memset(buffer, '_', 8);
   printf( "After:  %s\n", buffer );
   return (0);
}*/