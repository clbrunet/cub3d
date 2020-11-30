#include <stdio.h>
#include "cub3d.h"

void	print_res(t_vector res)
{
	printf("----------- RESOLUTION -----------\n\n");
	printf("X : %4i, Y : %4i\n", res.x, res.y);
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

void	print_colors(t_config *config)
{
	printf("\n------------- COLORS -------------\n\n");
	printf("F full : %#X, %i\n", config->floor_color.full,
			config->floor_color.full);
	/* printf("F bytes : [0]: %3i, [1]: %3i, [2]: %3i, [3]: %3i\n", */
			/* config->floor_color.byte[0], config->floor_color.byte[1], */
			/* config->floor_color.byte[2], config->floor_color.byte[3]); */
	printf("C full : %#X, %i\n", config->ceilling_color.full,
			config->ceilling_color.full);
	/* printf("C bytes : [0]: %3i, [1]: %3i, [2]: %3i, [3]: %3i\n", */
	/* 		config->ceilling_color.byte[0], config->ceilling_color.byte[1], */
	/* 		config->ceilling_color.byte[2], config->ceilling_color.byte[3]); */
}

void	print_config(t_config *config)
{
	print_res(config->res);
	print_textures(config->textures);
	print_colors(config);
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

void	printf_player(t_player *player)
{
	printf("\n------------- PLAYER -------------\n\n");
	printf("Pos : X: %4i, Y: %4i\n", player->pos.x, player->pos.y);
	printf("Angle : %3i\n", player->angle);
	printf("Height : %2i\n", player->height);
	/* printf("FOV : %3i\n", player->fov); */
}
