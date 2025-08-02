/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:35:12 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/01/15 19:49:24 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;
	t_list	*first;
	int		i;
	int		t;

	i = 0;
	first = lst;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	t = i - 1;
	while (t > 0)
	{
		t--;
		first = first->next;
	}
	last = first;
	return (last);
}
