/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/03 17:44:32 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//gcc -Werror -Wextra -Wall ./src/* ./libs/MLX42/libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"

static void	solve(t_data *d)
{
	t_tile	*tile;
	
	tile = find_tile(d->pc, d);
	if (tile->north && tile->north->flag_f < tile->flag_f)
		move_player(d, tile, 'N');
	else if (tile->east && tile->east->flag_f < tile->flag_f)
		move_player(d, tile, 'E');
	else if (tile->south && tile->south->flag_f < tile->flag_f)
		move_player(d, tile, 'S');
	else if (tile->west && tile->west->flag_f < tile->flag_f)
		move_player(d, tile, 'W');
	else
		printf("ai doesn't know where to move...\n");
}

//frees all the leftover data
static void	free_all(t_data *d)
{
	t_tile	*tile;
	int		i;

	i = -1;
	while (++i < d->board_s)
	{
		tile = d->tiles[i];
		if (tile->object)
			mlx_delete_image(d->window, tile->object);
		if (tile->floor)
			mlx_delete_image(d->window, tile->floor);
		free(tile->bc);
		free(tile);
	}
	free(d->tiles);
	i = -1;
	while (++i < d->asset_n)
		if (d->assets[i])
			mlx_delete_image(d->window, d->assets[i]);
	free(d->assets);
	if (d->player)
		mlx_delete_image(d->window, d->player);
}

//key hook used during the main loop
static void	hook(void *param)			//change to key_hook?
{
	t_data	*d;

	d = param;
	if (mlx_is_key_down(d->window, MLX_KEY_ESCAPE))
			mlx_close_window(d->window);
	if (!d->flag_r)
	{
		if (mlx_is_key_down(d->window, MLX_KEY_W))
			move_player(d, find_tile(d->pc, d), 'N');
		if (mlx_is_key_down(d->window, MLX_KEY_D))
			move_player(d, find_tile(d->pc, d), 'E');
		if (mlx_is_key_down(d->window, MLX_KEY_S))
			move_player(d, find_tile(d->pc, d), 'S');
		if (mlx_is_key_down(d->window, MLX_KEY_A))
			move_player(d, find_tile(d->pc, d), 'W');
		if (mlx_is_key_down(d->window, MLX_KEY_Q))
			solve(d);
	}
	else
		draw_board(d);
}

int	main(void)
{
	t_data	d; //METTRE LES NOMS DES FICHIERS DANS MAKEFILE
	
	initiate_data(&d);
	draw_board(&d);
	mlx_loop_hook(d.window, &hook, &d);
	mlx_loop(d.window);
	free_all(&d);
    mlx_terminate(d.window);
	return (EXIT_SUCCESS);
}
