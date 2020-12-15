#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "math.h"
# include "data_structures.h"

void	*malloser(long unsigned size);
void	print_textures(t_textures textures);
void	print_res(t_uvector res);
/* void	print_colors(t_colors colors); */
void	draw_rect(t_vars const *v, int tlx, int tly, int brx, int bry, t_color color);
void	print_map(char **map);
void	print_elems(t_vars *v);
void	print_player(t_vars *v);
void	print_keys(t_keys *keys);
void	print_hit(t_hit *hit);
void	draw_minimap(t_vars *v);

#endif
