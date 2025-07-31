/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:01:18 by iksaiz-m          #+#    #+#             */
/*   Updated: 2023/12/21 15:27:44 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*int main()
{
	char mem[] = "mem";
	memset(mem, 'e', 5);
    ft_bzero(mem, 5);
    write(1, mem, 5);
	bzero(mem, 5);
	write(1, mem, 5);
	return (0);
}*/