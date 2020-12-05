#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "structs.h"

void	print_textures(t_textures textures);
void	print_res(t_ivector res);
void	print_colors(t_colors colors);
void	print_map(char **map);
void	print_elems(t_vars *v);
void	print_player(t_player *player);
void	print_keys(t_keys *keys_down);

#endif
