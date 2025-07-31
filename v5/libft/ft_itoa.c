/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:14:23 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/17 15:41:20 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getnums(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count += 1;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	nums;
	char	*str;

	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nums = getnums(n);
	str = ft_calloc(nums + 1, (sizeof(char)));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = (-1) * n;
		i++;
	}
	while (n)
	{
		str[--nums] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
/* int main(void)
{
	char *str;
	str = ft_itoa(-2147483648);
	printf("\nresultado :%s", str);
} */