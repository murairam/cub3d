#ifndef PARSER_H
#define PARSER_H

// Forward declarations to avoid circular dependency
typedef struct s_game t_game;
typedef struct s_list t_list;

void parse_file(const char *filename, t_game *game);
void parse_texture(char *line, t_game *game);
void parse_color(char *line, t_game *game);
void parse_map(t_list *map_lines, t_game *game);
int is_map_line(char *line);
int is_color_line(char *line);
int is_texture_line(char *line);
int is_empty_line(char *line);
char **list_to_array(t_list *list);
void validate_map_boundaries(char **map);
void init_parsing(const char *filename, t_game *game);
void process_line(char *line, t_game *game, t_list **map_lines, int *map_started);
void finalize_parsing(t_game *game, t_list *map_lines);
void process_map_line(char *line, t_game *game, t_list **map_lines, int *map_started);
void handle_line_error(t_game *game, t_list **map_lines, int map_started);


#endif