/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:58:17 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/09/12 17:41:24 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Asignar memoria para palabras:
static char	*ft_strndup(const char *s1, size_t n)
{
	char	*b;

	b = ft_calloc((n + 1), sizeof(char));
	if (!b)
		return (NULL);
	ft_strlcpy(b, s1, n + 1);
	return (b);
}

// Escribe palabras:
static char	*ft_get_word(char *s, char c, size_t *i)
{
	char	*result;
	size_t	len;

	len = 0;
	while (s[*i + len] != '\0' && s[*i + len] != c)
		len++;
	result = ft_strndup(&s[*i], len);
	*i += len;
	while (s[*i] != '\0' && s[*i] == c)
		*i += 1;
	return (result);
}

// Contar palabras
static size_t	ft_num_word(char const *s, char c)
{
	size_t	num_word;
	size_t	i;

	i = 0;
	num_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			num_word++;
		i++;
	}
	return (num_word);
}

// Resetear memorias:
static void	ft_free(char **a)
{
	size_t	t;

	t = 0;
	while (a[t] != NULL)
	{
		free(a[t]);
		t++;
	}
	free(a);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	t;
	char	**a;

	if (s == NULL)
		return (NULL);
	a = (char **)ft_calloc((ft_num_word(s, c) + 1), sizeof(char *));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i += 1;
	t = 0;
	while (s[i] != '\0')
	{
		a[t] = ft_get_word((char *)s, c, &i);
		if (!a[t])
			return (ft_free(a), NULL);
		t++;
	}
	return (a);
}

/*int	main(void)
{
	char	**result;

	result = ft_split("     Hola Mundo", ' ');
	for(int x = 0; result[x] != NULL; x++)
		printf("%s\n", result[x]);
	ft_free(result);
	return (0);
}*/