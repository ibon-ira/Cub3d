/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:54:16 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/17 16:30:59 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
/*int main()
{
   char str[11] = "Hello World";
    printf("%s", ft_strchr(str, '\0'));
	printf("%s", strchr(str, '\0'));
    return(0);
}*/
//STRCHR -> "ME GUARDE" STR DESDE LA PRIMERA O 
//ENCONTRAR DIRECCIÓN DE MEMORIA DE LA PRIMERA 'O' 
//PARA DEVOLVERME EL RESTO DEL STR

//HOLA JUANTXO COMO ESTAS 
//O
//= OLA JUANTXO COMO ESTAS 

//STRRCHR 
//HOLA JUANTXO COMO ESTAS
//O ESTAS

//UNA ALOJA LA DIRECCIÓN DE MEMORIA DEL PRIMER CARATCER 
//Y LA OTRA ALOJA LA DIRECCIÓN DE MEMORIA DEL ULTIMO