/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:40:47 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/26 19:34:37 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*b;

	b = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!b)
		return (NULL);
	ft_strlcpy(b, s1, ft_strlen(s1) + 1);
	return (b);
}

/*int main()
{
	char *a = "amigos";
	
	//printf("Original: %s\n", strdup(a));
	printf("ft: %s", ft_strdup(a));
	return (0);
}*/