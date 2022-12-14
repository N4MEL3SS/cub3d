/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:16:45 by celadia           #+#    #+#             */
/*   Updated: 2022/08/15 14:16:45 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	errno = 0;
	game = (t_game){0};
	if (argc < 2)
		terminate(&game, ERR_ARGS, "Please specify scene filename");
	else if (argc > 2)
		terminate(&game, ERR_ARGS, "Too many arguments");
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		terminate(&game, ERR_MLX, strerror(errno));
	parse(argv[1], &game);
	initialize_game(&game);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.win, 2, (1L << 0), hook_key_press, &game);
	mlx_hook(game.win, 3, (1L << 1), hook_key_release, &game);
	mlx_hook(game.win, 17, (1L << 17), hook_exit, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}

void	player_set_fov(t_game *game, float fov, bool reset)
{
	if (reset)
		fov = ((game->img.aspect >= 1.77) - (game->img.aspect < 1.77)) * \
			sqrt(fabs(M_PI_4 * (game->img.aspect - 1.77) / 2)) + M_PI_2;
	game->col_step = tanf(fov / (float)(game->img.size.x - 1));
	game->col_center = (float)game->img.size.x / 2;
	game->col_scale = 1 / game->col_step;
	printf("Real FOV: %.0f\n", 114 * atan(game->col_step * game->col_center));
	if (reset == true || (M_PI_4 / 4 < fov && fov < PI2))
		game->fov = fov;
}

int	game_loop(t_game *game)
{
	player_control(game);
	ray_cast(game);
	img_ceilfloor_fill_rgb(&game->img, game->color_ceil, game->color_floor);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}
