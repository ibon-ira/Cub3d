/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:27:16 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/11 16:16:35 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	b;

	i = 0;
	result = 0;
	b = 0;
	while ((str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\t' || str[i] == '\v' || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			b = 1;
		i++;
	}
	while ((ft_isdigit(str[i])))
	{
		result = result * 10 +(str[i] - '0');
		i++;
	}
	if (b == 1)
		return (result * (-(1)));
	return (result);
}
/*int main()
{
	int i;
	char *s;
	int a;
 
	s = "a444a";
	i = atoi(s);
	a = ft_atoi(s);
	printf("Original: %d", i);
	printf("ft: %d", a);
	return (0);
}*/
//((str[i] <= '9' && str[i] >= '0') || (str[i] == '-') || (str[i] == '+'))