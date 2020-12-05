#include <stdio.h>
#include "cub3d.h"

void	print_res(t_ivector res)
{
	printf("----------- RESOLUTION -----------\n\n");
	printf("X : %4i, Y : %4i\n", (int)res.x, (int)res.y);
}

void	print_textures(t_textures textures)
{
	printf("\n------------ TEXTURES ------------\n\n");
	printf("NO : |%s|\n", textures.north);
	printf("SO : |%s|\n", textures.south);
	printf("WE : |%s|\n", textures.west);
	printf("EA : |%s|\n", textures.east);
	printf("S  : |%s|\n", textures.sprite);
}

void	print_colors(t_colors colors)
{
	printf("\n------------- COLORS -------------\n\n");
	printf("F full : %#.8X, %i\n", colors.floor.full,
			colors.floor.full);
	printf("C full : %#.8X, %i\n", colors.ceilling.full,
			colors.ceilling.full);
}

void	print_elems(t_vars *v)
{
	print_res(v->res);
	print_textures(v->textures);
	print_colors(v->colors);
}

void	print_map(char **map)
{
	printf("\n-------------- MAPS --------------\n\n");
	int i = 0;
	while (map[i])
	{
		printf("|%s|\n", map[i]);
		i++;
	}
	printf("|%s|\n", map[i]);
}

void	print_player(t_player *player)
{
	printf("\n------------- PLAYER -------------\n\n");
	printf("Pos : X: %f, Y: %f\n", player->x, player->y);
	printf("Grid pos : X: %i, Y: %i\n", (int)player->x / 64, (int)player->y / 64);
	printf("Angle : %f\n", player->angle);
	printf("Height : %2i\n", player->height);
	/* printf("FOV : %3i\n", player->fov); */
}

void	print_keys(t_keys *keys_down)
{
	printf("\n-------------- KEYS --------------\n\n");
	printf("<-: %i\n", keys_down->left);
	printf("-> %i\n", keys_down->right);
	printf("w: %i\n", keys_down->w);
	printf("a: %i\n", keys_down->a);
	printf("s: %i\n", keys_down->s);
	printf("d: %i\n", keys_down->d);
}
