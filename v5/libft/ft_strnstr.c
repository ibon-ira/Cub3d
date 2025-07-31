/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:55:17 by iksaiz-m          #+#    #+#             */
/*   Updated: 2023/12/15 16:32:25 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	t;

	i = 0;
	if (needle[0] == '\0')
	{
		return ((char *) haystack);
	}
	while (haystack[i] != '\0' && i < len)
	{
		t = 0;
		while ((haystack[i + t] == needle[t] || needle[t] == '\0') \
		&& (i + t) < len)
		{
			t++;
			if (needle[t] == '\0')
			{
				return ((char *) &haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}
/*int main()
{
    char a[] = "aaaaabaaa";
    char b[] = "aaab";
    printf("%s\n", ft_strnstr(a, b, 6));
	printf("%s", strnstr(a, b, 6));
    return (0);
}*/