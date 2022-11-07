/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:57:05 by llord             #+#    #+#             */
/*   Updated: 2022/11/07 12:29:04 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	set_default_values(t_data *d)
{
	d->flag_n = 0;		//flags left flag				(default)
	d->flag_r = 0;		//re_rendering flag				(default)
	d->flag_c = 0;		//asset cleaning flag			(default)
	d->flag_m = 0;		//move number flag				(default)

	d->max_bx = 0;		//board width					(uninitialized)
	d->max_by = 0;		//board height					(uninitialized)
	d->board_s = 0;		//tile amount					(uninitialized)

	d->asset_n = 7;		//number of assets				(constant)
	d->asset_s = 64;	//asset resolution				(constant)

	d->old = NULL;		//previously used assets		(uninitialized)
}

//initialises the data struct used throughout the program
void	initiate_data(t_data *d)
{
	set_default_values(d);

	//d->tiles = load_board(d, "1111\n1P01\n10E1\n1111");
	//d->tiles = load_board(d, "1111111\n1000001\n10P0001\n100C001\n1000E01\n1000001\n1111111\n\n");
	//d->tiles = load_board(d, "1111111111111111\n1000000000000001\n10P0000000000001\n10000000000C0001\n1000000011000001\n100000001C000001\n1000000000000001\n1000000000000001\n10000C1000000001\n1101001100000001\n100000001000C001\n100000001000CC01\n1000000000111001\n10E0000000000001\n1000000000000001\n1111111111111111\n");
	d->tiles = load_board(d, "111111111111111\n1P0000000000001\n111111111111101\n100000000000001\n101111111111111\n100000000000001\n111111111111101\n100000000000001\n101111111111111\n100000000000001\n111111111111101\n100000000000001\n101111111111111\n1000000000000E1\n111111111111111\n");
	//d->tiles = load_board(d, "1111111111111111111111111111111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C00100000000000000000000C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1110111111111110111110111111111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100000000000000000100C00100C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111110111111111111111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100000000000000P001000000000001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1110111110111110111110111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C001000001000000000001000001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111110111111111110111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C00000000100E00000000100C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111111111111111111111111111\n");
	connect_grid(d);

	d->max_wx = (d->max_bx + d->max_by + 3) * d->asset_s / 2;		//window width
	d->max_wy = (d->max_bx + d->max_by + 5) * d->asset_s / 4;		//window height
	d->window = mlx_init(d->max_wx, d->max_wy, "So Round", true);	//the window itself

	d->assets = load_assets(d);
}

/*
1111111\n1000001\n10P0001\n100C001\n1000E01\n1000001\n1111111

-----

111111111111111\n
1P0000000000001\n
111111111111101\n
100000000000001\n
101111111111111\n
100000000000001\n
111111111111101\n
100000000000001\n
101111111111111\n
100000000000001\n
111111111111101\n
100000000000001\n
101111111111111\n
1000000000000E1\n
111111111111111\n

111111111111111\n1P0000000000001\n111111111111101\n100000000000001\n101111111111111\n100000000000001\n111111111111101\n100000000000001\n101111111111111\n100000000000001\n111111111111101\n100000000000001\n101111111111111\n1000000000000E1\n111111111111111\n

-----

1111111111111111\n
1000000000000001\n
10P0000000000001\n
10000000000C0001\n
1000000011000001\n
100000001C000001\n
1000000000000001\n
1000000000000001\n
10000C1000000001\n
1101001100000001\n
100000001000C001\n
100000001000CC01\n
1000000000111001\n
10E0000000000001\n
1000000000000001\n
1111111111111111\n

1111111111111111\n1000000000000001\n10P0000000000001\n10000000000C0001\n1000000011000001\n100000001C000001\n1000000000000001\n1000000000000001\n10000C1000000001\n1101001100000001\n100000001000C001\n100000001000CC01\n1000000000111001\n10E0000000000001\n1000000000000001\n1111111111111111\n

1111111111111111111111111111111\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
100C00100000000000000000000C001\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
1110111111111110111110111111111\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
100000000000000000100C00100C001\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
1111111110111111111111111110111\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
100000000000000P001000000000001\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
1110111110111110111110111110111\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
100C001000001000000000001000001\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
1111111110111111111110111110111\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
100C00000000100E00000000100C001\n
1000001000001000001000001000001\n
1000001000001000001000001000001\n
1111111111111111111111111111111\n

1111111111111111111111111111111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C00100000000000000000000C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1110111111111110111110111111111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100000000000000000100C00100C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111110111111111111111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100000000000000P001000000000001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1110111110111110111110111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C001000001000000000001000001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111110111111111110111110111\n1000001000001000001000001000001\n1000001000001000001000001000001\n100C00000000100E00000000100C001\n1000001000001000001000001000001\n1000001000001000001000001000001\n1111111111111111111111111111111\n

*/