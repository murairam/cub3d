/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:41:45 by obajja            #+#    #+#             */
/*   Updated: 2025/09/03 12:41:46 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

/* ****************************************************************************/
/*                              PARSER BONUS                                  */
/* ****************************************************************************/

typedef struct s_line_list
{
	char				*line;
	struct s_line_list	*next;
}						t_line_list;

/* Forward declaration */
typedef struct s_game	t_game;

/* Base parsing functions (same as mandatory) */
void					parse_file(const char *filename, t_game *game);
void					parse_texture(char *line, t_game *game);
void					parse_color(char *line, t_game *game);
void					parse_map(t_list **map_lines, t_game *game);

/* Bonus parsing functions */
int						parse_door(t_game *game, char *line);
int						parse_sprite(t_game *game, char *line);
int						validate_map_bonus(t_game *game);

/* Utility functions */
t_line_list				*ft_lstnew_line(char *line);
void					ft_lstclear_lines(t_line_list **lst);
int						is_valid_map_char_bonus(char c);

/* Internal parsing functions */
void					init_parsing(const char *filename, t_game *game);
void					process_line(char *line, t_game *game,
							t_list **map_lines, int *map_started);
void					finalize_parsing(t_game *game, t_list *map_lines);
void					validate_boundaries(char **map, t_game *game,
							t_list **map_lines);
char					**list_to_array(t_list *list);
void					handle_line_error(t_game *game, t_list **map_lines,
							int map_started);
void					process_map_line(char *line, t_game *game,
							t_list **map_lines, int *map_started);

/* Utility functions */
int						is_map_line(char *line);
int						is_color_line(char *line);
int						is_texture_line(char *line);
int						is_empty_line(char *line);
void					get_map_dimensions(char **map, t_game *game);

#endif
