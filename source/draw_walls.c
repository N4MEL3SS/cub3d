/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:19:19 by celadia           #+#    #+#             */
/*   Updated: 2022/08/15 14:19:19 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

void	img_ceilfloor_fill_rgb(t_img *img, int ceil, int floor)
{
	const int	full_screen = img->size.x * img->size.y;
	const int	half_screen = full_screen / 2;
	int			i;

	i = 0;
	while (i < half_screen)
		img->data[i++] = ceil;
	while (i < full_screen)
		img->data[i++] = floor;
}

unsigned int	draw_wall_check(t_img *game_img, t_img *src_img, struct \
	s_column *column, unsigned int *error)
{
	*error = (column->height - game_img->size.y) * src_img->size.y / 2;
	src_img->src_y = *error / column->height;
	*error = *error % column->height;
	return (game_img->size.y);
}

void	draw_wall_scaled2(t_img *game_img, t_img *src_img, \
	struct s_column *column, unsigned int x)
{
	unsigned int		dst_y;
	unsigned int		max_y;
	unsigned int		error;

	src_img->src_y = 0;
	src_img->src_x = column->texture_pos * src_img->size.x;
	src_img->offset = src_img->src_x * src_img->size.y;
	dst_y = ft_max(0, ((int)game_img->size.y - (int)column->height) / 2);
	max_y = dst_y + column->height;
	error = src_img->size.y / 2;
	if (column->height > game_img->size.y)
		max_y = draw_wall_check(game_img, src_img, column, &error);
	while (dst_y < max_y)
	{
		while (error >= column->height && ++src_img->src_y)
			error -= column->height;
		game_img->data[game_img->size.x * dst_y++ + x] = \
			src_img->data[src_img->offset + src_img->src_y];
		error += src_img->size.y;
	}
}

void	draw_walls(t_game *game)
{
	unsigned int	ray;
	unsigned int	texture_id;
	const char		*textures = "NSWE";

	ray = 0;
	while (ray < game->img.size.x)
	{
		texture_id = ft_strchr(textures, game->column[ray].dir) - textures;
		if (game->test)
			draw_wall_scaled2(&game->img, &game->texture[texture_id], \
						&game->column[ray], ray);
		else
			draw_wall_scaled(&game->img, &game->texture[texture_id], \
						&game->column[ray], ray);
		ray++;
	}
}

void	draw_wall_scaled(t_img *game_img, const t_img *src_img, \
							const struct s_column *column, unsigned int x)
{
	const unsigned int	src_x = column->texture_pos * src_img->size.x;
	unsigned int		src_y;
	unsigned int		dst_y;
	unsigned int		max_y;
	unsigned int		error;

	src_y = 0;
	dst_y = ft_max(0, ((int)game_img->size.y - (int)column->height) / 2);
	max_y = dst_y + column->height;
	error = src_img->size.y / 2;
	if (column->height > game_img->size.y)
	{
		error = (column->height - game_img->size.y) * src_img->size.y / 2;
		src_y = error / column->height;
		error = error % column->height;
		max_y = game_img->size.y;
	}
	while (dst_y < max_y)
	{
		while (error >= column->height && ++src_y)
			error -= column->height;
		game_img->data[game_img->size.x * dst_y++ + x] = \
			src_img->data[src_y * src_img->size.x + src_x];
		error += src_img->size.y;
	}
}
