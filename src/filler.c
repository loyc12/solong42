/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/07 12:26:03 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"


void	fill_test(t_data *d, t_tile *tile, int *flag_n, int *flag_e)
{
	if (tile == NULL || tile->flag_f != 0)
		return ;

	tile->flag_f = 1;
	if (tile->type == TYPE_FLAG)
		*flag_n += 1;
	if (tile->type == TYPE_END || is_on_edge(d, tile->bc))
		*flag_e += 1;

	printf("tile (%i,%i) verified!\n", tile->bc->x, tile->bc->y);							//REMOVE ME

	fill_test(d, tile->north, flag_n, flag_e);
	fill_test(d, tile->east, flag_n, flag_e);
	fill_test(d, tile->south, flag_n, flag_e);
	fill_test(d, tile->west, flag_n, flag_e);
}

void	fill_tile_dist(t_data *d, t_tile *tile, int dist)
{
	if (tile == NULL || tile->flag_f <= dist) 
		return ;
	tile->flag_f = dist;

	fill_tile_dist(d, tile->north, dist + 1);
	fill_tile_dist(d, tile->east, dist + 1);
	fill_tile_dist(d, tile->south, dist + 1);
	fill_tile_dist(d, tile->west, dist + 1);
}
