/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 09:33:19 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/13 06:48:26 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

char			*join_first_image_colors(unsigned size, t_vars const *v)
{
	char		*join;
	unsigned	i_join;
	int			i;
	unsigned	j;

	join = malloc(sizeof(char) * (size));
	i = v->res.y - 1;
	i_join = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < v->res.x)
		{
			join[i_join++] = v->first_image_colors[i][j].bgr.blue;
			join[i_join++] = v->first_image_colors[i][j].bgr.green;
			join[i_join++] = v->first_image_colors[i][j].bgr.red;
			j++;
		}
		while (j++ % 4)
			join[i_join++] = '\0';
		i--;
	}
	return (join);
}

static unsigned	write_headers(int const fd, t_vars const *v)
{
	t_bmp_field file_size;
	t_bmp_field	width_then_height;

	write(fd, "BM", 2);
	file_size.full = 54 + 3 * v->res.x * v->res.y;
	if (v->res.x % 4)
		file_size.full += v->res.y * abs((int)v->res.x % 4 - 4);
	write(fd, file_size.str, 4);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	width_then_height.full = v->res.x;
	write(fd, width_then_height.str, 4);
	width_then_height.full = v->res.y;
	write(fd, width_then_height.str, 4);
	write(fd, "\x1\0\x18\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
			28);
	return (file_size.full - 54);
}

int				write_bmp(t_vars const *v)
{
	char	*pixel_data;
	int		size;
	int		fd;

	if ((fd = open("save.bmp", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXU))
			== -1)
		error("save.bmp", (t_vars *)v, PERROR);
	size = write_headers(fd, v);
	pixel_data = join_first_image_colors(size, v);
	write(fd, pixel_data, size);
	free(pixel_data);
	if (close(fd) == -1)
		error("save.bmp", (t_vars *)v, PERROR);
	return (0);
}
