/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:41:42 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/09/03 12:41:43 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ************************************************************************** */
/*                            FORWARD DECLARATIONS                            */
/* ************************************************************************** */

typedef struct s_game	t_game;
typedef struct s_list	t_list;

/* ************************************************************************** */
/*                              MAIN PARSER                                  */
/* ************************************************************************** */

void					parse_file(const char *filename, t_game *game);
void					init_parsing(const char *filename, t_game *game);
void					finalize_parsing(t_game *game, t_list *map_lines);

/* ************************************************************************** */
/*                            LINE PROCESSING                                */
/* ************************************************************************** */

void					process_line(char *line, t_game *game,
							t_list **map_lines, int *map_started);
void					process_map_line(char *line, t_game *game,
							t_list **map_lines, int *map_started);
void					handle_line_error(t_game *game, t_list **map_lines,
							int map_started);

/* ************************************************************************** */
/*                          CONTENT PARSERS                                  */
/* ************************************************************************** */

void					parse_texture(char *line, t_game *game);
void					parse_color(char *line, t_game *game);
void					parse_map(t_list **map_lines, t_game *game);

/* ************************************************************************** */
/*                           LINE VALIDATORS                                 */
/* ************************************************************************** */

int						is_map_line(char *line);
int						is_color_line(char *line);
int						is_texture_line(char *line);
int						is_empty_line(char *line);

/* ************************************************************************** */
/*                              MAP UTILS                                    */
/* ************************************************************************** */

char					**list_to_array(t_list *list);
void					validate_boundaries(char **map, t_game *game,
							t_list **map_lines);

#endif