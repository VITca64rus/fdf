/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:42:53 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/07 16:42:54 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static int	ft_get_height(char *file_name)
{
	char	*line;
	int		fd;
	int		height;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	height = 0;
	while (line)
	{
		free(line);
		line = NULL;
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int	ft_get_width(char *file_name)
{
	char	*line;
	int		fd;
	int		width;
	char	**numbers;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	close(fd);
	numbers = ft_split(line, ' ');
	free(line);
	width = 0;
	while (numbers[width])
	{
		free(numbers[width]);
		width++;
	}
	free(numbers);
	return (width);
}

static void	ft_create_matrix(char *file_name, t_fdf *data)
{
	int		fd;
	char	*line;
	char	**numbers;
	int		i;
	int		j;

	data->matrix = (int **)malloc(sizeof(int *) * data->height);
	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return ;
	i = 0;
	while (i < data->height)
	{
		line = get_next_line(fd);
		numbers = ft_split(line, ' ');
		data->matrix[i] = (int *)malloc(sizeof(int) * data->width);
		j = 0;
		while (j < data->width)
		{
			data->matrix[i][j] = ft_atoi(numbers[j]);
			free(numbers[j]);
			j++;
		}
		free(line);
		line = NULL;
		free(numbers);
		i++;
	}
	close(fd);
}

void	ft_read_file(char *file_name, t_fdf *data)
{
	data->height = ft_get_height(file_name);
	data->width = ft_get_width(file_name);
	ft_create_matrix(file_name, data);
}