#include <stdio.h>
#include "debug.h"
#include "defines.h"
#include "utils.h"
#include "draw.h"

void	print_res(t_uvector res)
{
	printf("----------- RESOLUTION -----------\n\n");
	printf("X : %4i, Y : %4i\n", (int)res.x, (int)res.y);
}

void	print_hit(t_hit *hit)
{
	printf("\n--------------- HIT --------------\n\n");
	printf("x: %f, y: %f\n", hit->pos.x, hit->pos.y);
	printf("dist: %f, hei: %d\n", hit->distance, hit->height);
}

void	print_textures(t_textures textures)
{
	printf("\n------------ TEXTURES ------------\n\n");
	(void)textures;
	/* printf("NO : |%s|\n", textures.north); */
	/* printf("SO : |%s|\n", textures.south); */
	/* printf("WE : |%s|\n", textures.west); */
	/* printf("EA : |%s|\n", textures.east); */
	/* printf("S  : |%s|\n", textures.sprite); */
}

void	print_colors(t_colors colors)
{
	printf("\n------------- COLORS -------------\n\n");
	printf("F full : %#.8X, %u\n", colors.floor.full, colors.floor.full);
	printf("C full : %#.8X, %u\n", colors.ceilling.full, colors.ceilling.full);
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
	printf("Pos : X: %f, Y: %f\n", player->pos.x, player->pos.y);
	printf("Grid pos : X: %i, Y: %i\n", (int)player->pos.x / BLOCK_SIZE, (int)player->pos.y / BLOCK_SIZE);
	/* printf("Pos : X: %f, Y: %f\n", player->pos.x, player->pos.y); */
	/* printf("Grid pos : X: %i, Y: %i\n", (int)player->pos.x / BLOCK_SIZE, (int)player->pos.y / BLOCK_SIZE); */
	printf("Angle : %f\n", player->angle);
	printf("Height : %2i\n", player->height);
	/* printf("FOV : %3i\n", player->fov); */
}

void	print_keys(t_keys *keys)
{
	printf("\n-------------- KEYS --------------\n\n");
	printf("<-: %i\n", keys->left);
	printf("-> %i\n", keys->right);
	printf("z: %i\n", keys->z);
	printf("q: %i\n", keys->q);
	printf("s: %i\n", keys->s);
	printf("d: %i\n", keys->d);
}

void	draw_rect(t_vars *v, int tlx, int tly, int brx, int bry, int color)
{
	int		bp;

	bp = tlx;
	while (tly <= bry)
	{
		tlx = bp;
		while (tlx <= brx)
		{
			if (tly > 0)
				mlx_img_pixel_put(v, tlx, tly, color);
			tlx++;
		}
		tly++;
	}
}

void	draw_minimap(t_vars *v)
{
	int		i;
	int		j;

	i = 0;
	while (i < v->map.max.y * BLOCK_SIZE * v->map.minimap_factor)
	{
		j = 0;
		while (j < v->map.max.x * BLOCK_SIZE * v->map.minimap_factor)
		{
			if (v->map.grid
					[(int)((double)i / v->map.minimap_factor) >> BLOCK_SIZE_BIT]
					[(int)(j / v->map.minimap_factor) >> BLOCK_SIZE_BIT] == '1')
				mlx_img_pixel_put(v, j, i, WHITE);
			else if (v->map.grid
					[(int)((double)i / v->map.minimap_factor) >> BLOCK_SIZE_BIT]
					[(int)(j / v->map.minimap_factor) >> BLOCK_SIZE_BIT] == 'S')
				mlx_img_pixel_put(v, j, i, BLUE);
			else if (j % (int)round(BLOCK_SIZE * v->map.minimap_factor)
					&& i % (int)round(BLOCK_SIZE
						*v->map.minimap_factor))
				mlx_img_pixel_put(v, j, i, 0x00ffb74d);
			else
				mlx_img_pixel_put(v, j, i, 0);

			j++;
		}
		i++;
	}
	draw_rect(v, v->player.pos.x * v->map.minimap_factor - 10,
			v->player.pos.y * v->map.minimap_factor - 10,
			v->player.pos.x * v->map.minimap_factor + 10,
			v->player.pos.y * v->map.minimap_factor + 10, GREEN);
	double newx = v->player.pos.x + cos(v->player.angle) * 10;
	double newy = v->player.pos.y - sin(v->player.angle) * 10;
	for (int c = 0; c < 100; c++)
	{
		draw_rect(v, newx * v->map.minimap_factor - 1,
				newy * v->map.minimap_factor - 1,
				newx * v->map.minimap_factor + 1,
				newy * v->map.minimap_factor + 1, RED);
		newx = newx + cos(v->player.angle) * 10;
		newy = newy - sin(v->player.angle) * 10;
	}
	newx = v->player.pos.x + cos(v->player.angle + deg_to_rad(30)) * 10;
	newy = v->player.pos.y - sin(v->player.angle + deg_to_rad(30)) * 10;
	for (int c = 0; c < 100; c++)
	{
		draw_rect(v, newx * v->map.minimap_factor - 1,
				newy * v->map.minimap_factor - 1,
				newx * v->map.minimap_factor + 1,
				newy * v->map.minimap_factor + 1, RED);
		newx = newx + cos(v->player.angle + deg_to_rad(30)) * 10;
		newy = newy - sin(v->player.angle + deg_to_rad(30)) * 10;
	}
	newx = v->player.pos.x + cos(v->player.angle - deg_to_rad(30)) * 10;
	newy = v->player.pos.y - sin(v->player.angle - deg_to_rad(30)) * 10;
	for (int c = 0; c < 100; c++)
	{
		draw_rect(v, newx * v->map.minimap_factor - 1,
				newy * v->map.minimap_factor - 1,
				newx * v->map.minimap_factor + 1,
				newy * v->map.minimap_factor + 1, RED);
		newx = newx + cos(v->player.angle - deg_to_rad(30)) * 10;
		newy = newy - sin(v->player.angle - deg_to_rad(30)) * 10;
	}
}
