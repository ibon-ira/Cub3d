/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:05:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/20 21:10:51 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_one_line(char *save)
{
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	return (ft_substr(save, 0, i + 1));
}

static char	*ft_get_rest_line(char *save)
{
	int		i;
	char	*new_save;

	new_save = NULL;
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (free(save), NULL);
	i++;
	// new_save = ft_substr(save, i, ft_strlen(save));
	// if (new_save == NULL)
	// 	return (free(save), NULL);
	free(save);
	return (new_save);
}

static char	*get_read_line(int fd, char *save)
{
	int		x;
	char	buffer[BUFFER_SIZE + 1];

	x = 1;
	while (x)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		if (x == 0)
		{
			if (!ft_strlen(save))
				return (free(save), NULL);
			else if (ft_strlen(save))
				return (save);
		}
		if (x == -1)
			return (free(save), NULL);
		buffer[x] = '\0';
		save = gnl_join(save, buffer);
		if (!save)
			return (NULL);
		if (ft_strchr(save, '\n'))
			return (save);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FD_OPEN];

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_OPEN < fd)
	{
		if (save[fd])
			free(save[fd]);
		return (NULL);
	}
	if (!save[fd])
	{
		save[fd] = malloc(sizeof(char));
		if (!save[fd])
			return (NULL);
		save[fd][0] = '\0';
	}
	save[fd] = get_read_line(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	line = ft_get_one_line(save[fd]);
	save[fd] = ft_get_rest_line(save[fd]);
	return (line);
}
/*int	main(void)
{
	int		fd;
	char	*string;

	fd = open ("test.txt", O_RDONLY);
	string = get_next_line(fd);
	while (string != NULL)
	{
		printf("%s", string);
		free(string);
		string = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/