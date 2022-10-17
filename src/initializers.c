/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/10/17 10:08:26 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//puts harcoded data into the d struct (prints the board)
void	initiate_data(t_data *d)
{
	d->max_wx = 2048;	//window width				ALL HARDCODED FOR NOW
	d->max_wy = 1024;	//window height
	d->window = mlx_init(d->max_wx, d->max_wy, "Test Window", true);	//the window itself

	d->max_bx = 16;	//board width
	d->max_by = 32;	//board height
	//d->board ...

	d->asset_size = 64;	//asset resolution (static)
}

void	initiate_window(t_data *d)
{
	mlx_image_t	*image;
		
	image = mlx_new_image(d->window, d->max_wx, d->max_wy);
	memset(image->pixels, 128, image->width * image->height * sizeof(int32_t));
	mlx_image_to_window(d->window, image, 0, 0);
	mlx_image_to_window(d->window, mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Tittle.png")), 0, 0); //MOVE ME
}

//puts the player on the board
void	initiate_player(t_data *d, t_entity *p)
{

	p->image = mlx_texture_to_image(d->window, mlx_load_png("./Assets/Misc/Ball.png"));
	p->type = 1;
	p->bc->x = 4;	//hardocded (temp)
	p->bc->y = 2;	//hardocded (temp)
	p->bc->z = 0;	//hardocded (temp)
}
