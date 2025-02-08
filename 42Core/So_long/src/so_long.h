/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:40:12 by juliensarda       #+#    #+#             */
/*   Updated: 2024/01/10 11:00:05 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdlib.h>
# include <time.h>

# define WALL_XPM "assets/wall.xpm"
# define COINS_XPM "assets/coins.xpm"
# define PLAYER_LEFT_XPM "assets/player_left.xpm"
# define PLAYER_RIGHT_XPM "assets/player_right.xpm"
# define PLAYER_TOP_XPM "assets/player_top.xpm"
# define PLAYER_BACK_XPM "assets/player_back.xpm"
# define EXIT_OPEN_XPM "assets/exit_open.xpm"
# define EXIT_CLOSE_XPM "assets/exit_close.xpm"
# define FLOOR_XPM "assets/floor.xpm"

# define WALL '1'
# define FLOOR '0'
# define COINS 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define VISITED 'V'

# define TEXTURE_WIDTH 32
# define TEXTURE_HEIGHT 32

# define TOP 1
# define BACK 2
# define RIGHT 3
# define LEFT 4

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

# define KEY_Q 113
# define KEY_ESC 65307

# define MOVEMENT_INTERVAL 0.4

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef enum e_bool
{
	false,
	true
}				t_bool;

typedef struct s_image
{
	void		*xpm_ptr;
	int			x;
	int			y;
}				t_image;

typedef struct s_map
{
	char		**map_tab;
	t_position	player;
	int			players;
	int			columns;
	int			rows;
	int			coins_count;
	int			exit;
}				t_map;

typedef struct s_game
{
	void		*win_ptr;
	void		*mlx_ptr;
	int			player_texture;
	int			move_count;
	t_bool		map_alloc;
	t_map		map;
	t_image		wall;
	t_image		coins;
	int			texture;
	char		previous_texture;
	t_image		player_left;
	t_image		player_right;
	t_image		player_top;
	t_image		player_back;
	t_image		exit_open;
	t_image		exit_close;
	t_image		floor;
}				t_game;

void			init_new_window(t_game *game);
void			error_failure_message(char *message);
void			init_texture(t_game *game);
void			init_map(t_game *game, const char *argv);
int				render_map(t_game *game);
void			init_values(t_game *game, char *argv);
int				handle_input(int keysym, t_game *game);
void			free_string_2(char **str);
void			check_map(t_game *game);
void			print_movements(t_game *game);
void			free_all(t_game *game);
int				close_game(t_game *game);
void			free_map(t_game *game);
int				victory(t_game *game);
void			is_path_available(t_game *game);
void			set_param_rules(t_game *game);
void			destroy_textures(t_game *game);
void			free_string(char **str, int i);
void			check_command_line_arguments(int argc, char **argv);
void			end_file(int fd);
void			check_r_c_parsing(t_game *game, char *trimmed_line, int fd);
void			init_values(t_game *game, char *argv);
void			get_rows_len(t_game *game, char *argv);
void			end_file(int fd);

#endif
