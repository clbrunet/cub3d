#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "structs.h"

void	print_textures(t_textures textures);
void	print_res(t_vector res);
void	print_colors(t_config *config);
void	print_map(char **map);
void	print_config(t_config *config);
void	printf_player(t_player *player);

#endif
