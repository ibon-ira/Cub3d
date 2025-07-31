/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:22:49 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/16 18:48:48 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cutstring;
	size_t	i;
	size_t	k;

	i = 0;
	k = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (i == k)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[k]))
		k--;
	cutstring = ft_substr(s1, i, k - i + 1);
	if (!cutstring)
		return (NULL);
	return (cutstring);
}
/*int main()
{
printf("%s", ft_strtrim(s1, set));
return (0);
}
char const *s1 = str = "Hola mundo holaohhhhh";
char const *set = "Hoh";
*/
//mi programa entre: la mundo hola
