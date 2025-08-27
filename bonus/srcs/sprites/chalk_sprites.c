/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 00:00:00 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <sys/time.h>
#include <math.h>

/* ************************************************************************** */
/*                         MAP PARSING AND INITIALIZATION                    */
/* ************************************************************************** */

int	parse_map_for_chalks(t_game *game)
{
	int	row;
	int	col;
	int	count;

	count = 0;
	// First pass: count chalks
	for (row = 0; row < game->map_height; row++)
	{
		for (col = 0; game->map[row] && game->map[row][col]; col++)
		{
			if (game->map[row][col] == 'c')
				count++;
		}
	}
	
	if (count == 0)
	{
		game->chalk_sprites = NULL;
		game->chalk_sprite_count = 0;
		return (1); // Success, just no chalks found
	}
	
	// Allocate array for chalks
	game->chalk_sprites = malloc(sizeof(t_chalk_sprite) * count);
	if (!game->chalk_sprites)
		return (0);
	
	// Second pass: store positions and replace with floor
	game->chalk_sprite_count = 0;
	for (row = 0; row < game->map_height; row++)
	{
		for (col = 0; game->map[row] && game->map[row][col]; col++)
		{
			if (game->map[row][col] == 'c')
			{
				// Convert map coordinates to world coordinates (these stay fixed)
				double world_x = col * CUBE + (CUBE / 2);
				double world_y = row * CUBE + (CUBE / 2);
				
				game->chalk_sprites[game->chalk_sprite_count].x = world_x;
				game->chalk_sprites[game->chalk_sprite_count].y = world_y;
				game->chalk_sprites[game->chalk_sprite_count].base_x = world_x;
				game->chalk_sprites[game->chalk_sprite_count].base_y = world_y;
				game->chalk_sprites[game->chalk_sprite_count].visible = 1;
				game->chalk_sprites[game->chalk_sprite_count].collected = 0;
				game->chalk_sprites[game->chalk_sprite_count].id = game->chalk_sprite_count;
				
				// Give each chalk slightly different animation timing for variety
				game->chalk_sprites[game->chalk_sprite_count].time = game->chalk_sprite_count * 0.3;
				game->chalk_sprites[game->chalk_sprite_count].amplitude = CHALK_AMPLITUDE;
				game->chalk_sprites[game->chalk_sprite_count].frequency = CHALK_FREQUENCY + (game->chalk_sprite_count * 0.05);
				
				// Replace with floor in map
				game->map[row][col] = '0';
				
				game->chalk_sprite_count++;
			}
		}
	}
	
	return (1);
}

int	init_chalk_sprite_system(t_game *game)
{
	int	i;
	
	// Parse map for chalk positions first
	if (!parse_map_for_chalks(game))
		return (0);
	
	if (game->chalk_sprite_count == 0)
		return (1); // No chalks found, but not an error
	
	// Initialize textures for all chalks
	for (i = 0; i < game->chalk_sprite_count; i++)
	{
		if (!load_chalk_sprite_texture(game, &game->chalk_sprites[i]))
		{
			// Cleanup already initialized sprites
			while (--i >= 0)
				mlx_destroy_image(game->mlx, game->chalk_sprites[i].img);
			free(game->chalk_sprites);
			return (0);
		}
	}
	
	game->chalk_collected = 0;
	game->game_time = 0.0;
	
	return (1);
}

int	load_chalk_sprite_texture(t_game *game, t_chalk_sprite *sprite)
{
	// Load the chalk texture
	sprite->img = mlx_xpm_file_to_image(game->mlx, TEX_CHALK_ITEM, 
	                                    &sprite->width, &sprite->height);
	if (!sprite->img)
	{
		return (0);
	}
	
	// Get image data for pixel access
	sprite->data = (int *)mlx_get_data_addr(sprite->img, &sprite->bpp, 
	                                        &sprite->size_line, &sprite->endian);
	if (!sprite->data)
	{
		mlx_destroy_image(game->mlx, sprite->img);
		return (0);
	}
	
	return (1);
}

/* ************************************************************************** */
/*                            ANIMATION SYSTEM                               */
/* ************************************************************************** */

double	get_current_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	animate_chalks(t_game *game, double delta_time)
{
	int	i;
	
	if (!game->chalk_sprites || game->chalk_sprite_count == 0)
		return;
	
	game->game_time += delta_time;
	
	// Animate all visible chalks
	for (i = 0; i < game->chalk_sprite_count; i++)
	{
		if (game->chalk_sprites[i].visible && !game->chalk_sprites[i].collected)
			animate_chalk_sprite(&game->chalk_sprites[i], delta_time);
	}
}

void	animate_chalk_sprite(t_chalk_sprite *sprite, double delta_time)
{
	// Update animation time
	sprite->time += delta_time;
	
	// Apply bobbing animation to Y position
	// y = base_y + sin(time * frequency) * amplitude
	double offset = sin(sprite->time * sprite->frequency) * sprite->amplitude;
	sprite->y = sprite->base_y + offset;
	
	// Keep X position fixed at base position
	sprite->x = sprite->base_x;
	
	// Prevent time overflow for smooth continuous animation
	if (sprite->time > 1000.0)
		sprite->time = 0.0;
}

/* ************************************************************************** */
/*                            3D SPRITE RENDERING                           */
/* ************************************************************************** */

void	render_chalks(t_game *game)
{
	int	i;
	
	if (!game->chalk_sprites || game->chalk_sprite_count == 0)
		return;
	
	// Render all visible chalks
	for (i = 0; i < game->chalk_sprite_count; i++)
	{
		if (game->chalk_sprites[i].visible && !game->chalk_sprites[i].collected)
		{
			// Check if chalk is in field of view and within render distance
			if (is_in_fov(game, game->chalk_sprites[i].x, game->chalk_sprites[i].y))
				render_chalk_sprite(game, &game->chalk_sprites[i]);
		}
	}
}

int	is_in_fov(t_game *game, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle_to_sprite;
	double	angle_diff;
	
	// Calculate distance
	dx = sprite_x - game->player.x;
	dy = sprite_y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	
	// Distance culling
	if (distance > MAX_RENDER_DISTANCE)
		return (0);
	
	// Calculate angle to sprite
	angle_to_sprite = atan2(dy, dx);
	
	// Calculate angle difference from player's view direction
	angle_diff = angle_to_sprite - game->player.angle;
	
	// Normalize angle difference to [-PI, PI]
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	
	// Check if within field of view (±30 degrees = ±PI/6)
	return (fabs(angle_diff) <= (FOV_DEGREES * M_PI / 180.0) / 2.0);
}

void	world_to_screen(t_game *game, double world_x, double world_y, int *screen_x, int *screen_y, double *distance)
{
	double	dx;
	double	dy;
	double	sprite_angle;
	double	angle_diff;
	double	sprite_distance;
	
	// Calculate relative position from player
	dx = world_x - game->player.x;
	dy = world_y - game->player.y;
	sprite_distance = sqrt(dx * dx + dy * dy);
	*distance = sprite_distance;
	
	// Calculate angle to sprite relative to player's facing direction
	sprite_angle = atan2(dy, dx);
	angle_diff = sprite_angle - game->player.angle;
	
	// Normalize angle difference to [-PI, PI]
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	
	// Calculate screen X position based on angle difference
	// This keeps the sprite anchored to its world position horizontally
	*screen_x = (int)(WIDTH / 2 + (angle_diff * WIDTH) / (FOV_DEGREES * M_PI / 180.0));
	
	// Y position is completely fixed - never affected by camera pitch or vertical look
	*screen_y = HEIGHT / 2;  // Always center height regardless of any camera movement
}

void	render_chalk_sprite(t_game *game, t_chalk_sprite *sprite)
{
	int		screen_x;
	double	distance;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	int		pixel_color;
	double	dx;
	double	dy;
	double	sprite_angle;
	double	angle_diff;
	
	// Safety checks
	if (!game || !sprite || !sprite->data || !game->data)
		return;
	
	// Calculate distance and screen X position manually (exactly like raycasting)
	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	
	// Distance culling - don't render very far sprites
	if (distance > MAX_RENDER_DISTANCE)
		return;
	
	// Calculate angle to sprite
	sprite_angle = atan2(dy, dx);
	angle_diff = sprite_angle - game->player.angle;
	
	// Normalize angle difference
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	
	// Calculate screen X position (same method as walls)
	screen_x = (int)(WIDTH / 2 + (angle_diff * WIDTH) / (FOV_DEGREES * M_PI / 180.0));
	
	// Calculate sprite size based on distance, maintaining aspect ratio
	if (distance < 1.0)
		distance = 1.0;
	
	// Calculate base size and maintain 64:32 aspect ratio (width:height = 2:1)
	int base_size = (int)(SPRITE_SCALE_FACTOR * CUBE / distance);
	int sprite_width = base_size * 2;  // Chalk is twice as wide as tall (64x32)
	int sprite_height = base_size;
	
	if (sprite_width < 4)
		sprite_width = 4;
	if (sprite_height < 2)
		sprite_height = 2;
	if (sprite_width > WIDTH / 3)
	{
		sprite_width = WIDTH / 3;
		sprite_height = sprite_width / 2;  // Maintain aspect ratio
	}
	
	// Position sprite at screen center with pitch offset (same as walls)
	int pitch_offset = -(int)(game->player.pitch * HEIGHT * 0.3f);
	
	// Add vertical offset based on sprite's animated Y position
	// Convert world Y difference to screen pixels (negative because screen Y is inverted)
	double world_y_diff = sprite->y - sprite->base_y;  // This is our animation offset
	
	// Scale movement amplitude based on distance - closer = more visible movement
	double distance_scale = 1.0 / (distance + 0.5);  // Simple inverse with offset to prevent division issues
	if (distance_scale > 2.0) distance_scale = 2.0;   // Cap maximum movement
	if (distance_scale < 0.3) distance_scale = 0.3;   // Ensure minimum movement
	
	int vertical_offset = -(int)(world_y_diff * 30 * distance_scale);  // Reduced base scale
	
	start_x = screen_x - sprite_width / 2;
	end_x = screen_x + sprite_width / 2;
	start_y = HEIGHT / 2 - sprite_height / 2 + pitch_offset + vertical_offset;
	end_y = HEIGHT / 2 + sprite_height / 2 + pitch_offset + vertical_offset;
	
	// Bounds checking
	if (start_x >= WIDTH || end_x < 0 || start_y >= HEIGHT || end_y < 0)
		return;
	
	// Clamp to screen bounds
	if (start_x < 0)
		start_x = 0;
	if (end_x >= WIDTH)
		end_x = WIDTH - 1;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	
	// Render sprite with transparency (pixel-by-pixel)
	for (y = start_y; y < end_y; y++)
	{
		for (x = start_x; x < end_x; x++)
		{
			// Calculate texture coordinates with safety bounds
			if (sprite_width > 0 && sprite_height > 0)
			{
				tex_x = (x - start_x) * sprite->width / sprite_width;
				tex_y = (y - start_y) * sprite->height / sprite_height;
			}
			else
			{
				tex_x = 0;
				tex_y = 0;
			}
			
			// Bounds check for texture coordinates
			if (tex_x >= 0 && tex_x < sprite->width && tex_y >= 0 && tex_y < sprite->height)
			{
				// Calculate texture index with safety check
				int tex_index = tex_y * sprite->width + tex_x;
				if (tex_index >= 0 && tex_index < sprite->width * sprite->height)
				{
					// Get pixel color from sprite texture
					pixel_color = sprite->data[tex_index];
					
					// Transparency check: skip transparent pixels (None/black)
					if ((pixel_color & 0x00FFFFFF) != 0x000000)
					{
						// Draw pixel to screen with bounds check
						if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
							put_pixel(x, y, pixel_color, game);
					}
				}
			}
		}
	}
}

void	render_chalk_pixel(t_game *game, int screen_x, int screen_y, int color)
{
	char	*dst;
	int		offset;
	
	// Safety checks for all required pointers
	if (!game || !game->data)
		return;
	
	// Bounds checking
	if (screen_x < 0 || screen_x >= WIDTH || screen_y < 0 || screen_y >= HEIGHT)
		return;
	
	// Calculate pixel offset in the MLX image buffer
	offset = screen_y * game->size_line + screen_x * (game->bpp / 8);
	
	// Ensure we don't write outside buffer bounds
	if (offset >= 0 && offset < HEIGHT * game->size_line - 4)
	{
		dst = game->data + offset;
		*(unsigned int*)dst = color;
	}
}

/* ************************************************************************** */
/*                            MEMORY MANAGEMENT                              */
/* ************************************************************************** */

void	cleanup_chalk_sprites(t_game *game)
{
	int	i;
	
	if (!game)
		return;
		
	if (game->chalk_sprites && game->chalk_sprite_count > 0)
	{
		for (i = 0; i < game->chalk_sprite_count; i++)
		{
			// Only destroy image if both MLX and image exist
			if (game->chalk_sprites[i].img && game->mlx)
			{
				mlx_destroy_image(game->mlx, game->chalk_sprites[i].img);
			}
			game->chalk_sprites[i].img = NULL;
			game->chalk_sprites[i].data = NULL;  // Clear data pointer
		}
		free(game->chalk_sprites);
		game->chalk_sprites = NULL;
	}
	game->chalk_sprite_count = 0;
}

/* ************************************************************************** */
/*                            MINIMAP INTEGRATION                           */
/* ************************************************************************** */

static void	draw_chalk_tile_on_minimap(t_game *game, int map_x, int map_y)
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		x;
	int		y;
	char	*dst;
	unsigned int	chalk_color;
	
	// Calculate minimap position for this map tile
	int player_map_x = (int)(game->player.x / CUBE);
	int player_map_y = (int)(game->player.y / CUBE);
	
	// Calculate relative position from player
	int rel_x = map_x - player_map_x + MINIMAP_TILES_X / 2;
	int rel_y = map_y - player_map_y + MINIMAP_TILES_Y / 2;
	
	// Check if within minimap bounds
	if (rel_x < 0 || rel_x >= MINIMAP_TILES_X || rel_y < 0 || rel_y >= MINIMAP_TILES_Y)
		return;
	
	// Convert to minimap pixel coordinates
	start_x = rel_x * MINIMAP_SCALE;
	start_y = rel_y * MINIMAP_SCALE;
	end_x = start_x + MINIMAP_SCALE;
	end_y = start_y + MINIMAP_SCALE;
	
	// Blue color for chalk on minimap
	chalk_color = 0x0066FF; // Bright blue
	
	// Draw a small blue square in the center of the tile
	int center_x = start_x + MINIMAP_SCALE / 2;
	int center_y = start_y + MINIMAP_SCALE / 2;
	int chalk_size = MINIMAP_SCALE / 4; // Small square
	
	for (y = center_y - chalk_size / 2; y <= center_y + chalk_size / 2; y++)
	{
		for (x = center_x - chalk_size / 2; x <= center_x + chalk_size / 2; x++)
		{
			if (x >= 0 && x < game->minimap.width && y >= 0 && y < game->minimap.height)
			{
				dst = game->minimap.data + (y * game->minimap.size_line + x * (game->minimap.bpp / 8));
				*(unsigned int *)dst = chalk_color;
			}
		}
	}
}

void	draw_chalks_on_minimap(t_game *game)
{
	int	i;
	
	if (!game || !game->chalk_sprites)
		return;
	
	// Draw all uncollected chalks on minimap
	for (i = 0; i < game->chalk_sprite_count; i++)
	{
		if (!game->chalk_sprites[i].collected)
		{
			int map_x = (int)(game->chalk_sprites[i].x / CUBE);
			int map_y = (int)(game->chalk_sprites[i].y / CUBE);
			draw_chalk_tile_on_minimap(game, map_x, map_y);
		}
	}
}
