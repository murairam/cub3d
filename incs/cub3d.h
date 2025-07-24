#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                INCLUDES                                   */
/* ************************************************************************** */

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "parser.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_game
{
	char	**map;
	int		fd;
	char	*tex_n;
	char	*tex_s;
	char	*tex_e;
	char	*tex_w;
	int		color_c;
	int		color_f;
}			t_game;

/* ************************************************************************** */
/*                              ERROR HANDLING                               */
/* ************************************************************************** */

int		ft_error(const char *msg);
void	ft_exit_error(const char *msg);
void	ft_exit_error_with_cleanup(t_game *game, const char *msg);
void	ft_exit_error_with_cleanup_and_list(t_game *game, t_list **map_lines,
			const char *msg);
void	ft_exit_error_with_cleanup_and_split(t_game *game, char **split1,
	char **split2, const char *msg);
void	ft_exit_error_with_cleanup_and_line(t_game *game, char *line,
	const char *msg);
void	ft_exit_error_with_cleanup_split_and_line(t_game *game, char **split1,
	char **split2, char *line, const char *msg);

/* ************************************************************************** */
/*                              MEMORY MANAGEMENT                            */
/* ************************************************************************** */

void	ft_free_split(char **split);
void	ft_free_game(t_game *game);

/* ************************************************************************** */
/*                              INITIALIZATION                               */
/* ************************************************************************** */

void	init_game(t_game *game);

#endif