#ifndef PARSER_H
#define PARSER_H

// Forward declaration to avoid circular dependency
typedef struct s_game t_game;

int parse_file(const char *filename, t_game *game);

#endif