/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:02:15 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/17 16:30:49 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] != (char )c)
			i--;
		else
		{
			return ((char *)&s[i]);
		}
	}
	return (NULL);
}
/*int main()
{
   char str[11] = "Hello World";
    printf("%s", ft_strrchr(str, '\0'));
    return(0);
}*/