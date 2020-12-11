#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "math.h"
# include "data_structures.h"

void	print_textures(t_textures textures);
void	print_res(t_uvector res);
void	print_colors(t_colors colors);
void	print_map(char **map);
void	print_elems(t_vars *v);
void	print_player(t_player *player);
void	print_keys(t_keys *keys);
void	print_hit(t_hit *hit);

#endif
