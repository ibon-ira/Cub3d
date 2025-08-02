/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:05:32 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/04/20 17:15:53 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
}

char	*gnl_join(char *s1, char *s2)
{
	char	*joinstring;
	size_t	i;
	size_t	k;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	joinstring = (char *)malloc((i + k + 1) * sizeof(char));
	if (!joinstring)
		return (free (s1), NULL);
	gnl_memcpy(joinstring, s1, i);
	gnl_memcpy(joinstring + i, s2, k);
	joinstring[i + k] = '\0';
	free(s1);
	return (joinstring);
}
