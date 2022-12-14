/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommy <celadia@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:19:46 by ctommy            #+#    #+#             */
/*   Updated: 2022/08/15 14:20:28 by ctommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

void	set_ceilfloor(const char *color_string, unsigned int *target,
																t_game *game)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (*target != -1U)
		terminate(game, ERR_PARSE, "Duplicated F/C color identifier");
	color_string++;
	if (*color_string != ' ')
		terminate(game, ERR_PARSE, "Add space after F/C identifier");
	color_string = atoi_limited(&r, color_string, UCHAR_MAX);
	if (color_string == NULL)
		terminate(game, ERR_PARSE, "F/C color Red is wrong (range: 0-255)");
	else if (*color_string++ != ',')
		terminate(game, ERR_PARSE, "F/C color format: 'F R,G,B'/'C R,G,B'");
	color_string = atoi_limited(&g, color_string, UCHAR_MAX);
	if (color_string == NULL)
		terminate(game, ERR_PARSE, "F/C color Green is wrong (range: 0-255)");
	else if (*color_string++ != ',')
		terminate(game, ERR_PARSE, "F/C color format: 'F R,G,B'/'C R,G,B'");
	color_string = atoi_limited(&b, color_string, UCHAR_MAX);
	if (color_string == NULL)
		terminate(game, ERR_PARSE, "F/C color Blue is wrong (range: 0-255)");
	else if (*color_string != '\0')
		terminate(game, ERR_PARSE, "F/C color line redundant symbols");
	*target = (r << 16) | (g << 8) | b;
}

void	set_textures(char *string, t_game *game)
{
	int	id;

	id = -1;
	if (string[0] == 'N' && string[1] == 'O')
		id = WALL_N;
	else if (string[0] == 'S' && string[1] == 'O')
		id = WALL_S;
	else if (string[0] == 'W' && string[1] == 'E')
		id = WALL_W;
	else if (string[0] == 'E' && string[1] == 'A')
		id = WALL_E;
	else
		terminate(game, ERR_PARSE, "Wrong texture setting. Valid: NO/SO/WE/EA");
	if (game->texture[id].ptr != NULL)
		terminate(game, ERR_PARSE, "Duplicated texture identifier");
	if (string[2] != ' ')
		terminate(game, ERR_PARSE, "Add space after texture identifier");
	string += 2;
	while (*string == ' ')
		string++;
	set_textures_import(string, &game->texture[id], game);
}

static void	*png_file_to_image(void *mlx, char *file, int *width, int *height)
{
	return (mlx_png_file_to_image(mlx, file, width, height));
}

void	set_textures_import(char *string, t_img *texture, t_game *game)
{
	int				n;
	const size_t	str_len = ft_strlen(string);

	if (str_len < 5)
		terminate(game, ERR_ARGS, "Can't identify texture format (.xpm/.png)");
	if (ft_memcmp(".xpm", string + str_len - 4, 5) == 0)
		texture->ptr = mlx_xpm_file_to_image(game->mlx, string, \
							(int *)&texture->size.x, (int *)&texture->size.y);
	else if (ft_memcmp(".png", string + str_len - 4, 5) == 0)
		texture->ptr = png_file_to_image(game->mlx, string, \
							(int *)&texture->size.x, (int *)&texture->size.y);
	else
		terminate(game, ERR_ARGS, "Can't identify texture format (.xpm/.png)");
	if (texture->ptr == NULL)
		terminate(game, ERR_PARSE, "Can't load texture file");
	texture->data = (unsigned int *)mlx_get_data_addr(texture->ptr, &n, &n, &n);
	texture->aspect = texture->size.x / texture->size.y;
}
