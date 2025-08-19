# Cub3D Test Maps Organization

## Structure

### 1. `/test_maps/error/` - Error Testing Maps
Maps designed to trigger specific error conditions:
- `bad_rgb.cub` - RGB values > 255
- `boundary_rgb.cub` - Invalid texture paths (boundary testing)
- `duplicate_ceiling.cub` - Duplicate ceiling definitions
- `hole_in_wall.cub` - Map with holes/invalid boundaries
- `leaky_map.cub` - Map boundaries not closed
- `missing_texture_path.cub` - Missing texture path
- `multi_player.cub` - Multiple player positions
- `no_player.cub` - No player in map
- `open_left.cub` - Map open on left side
- `rgb_negative.cub` - Negative RGB values
- `truly_open.cub` - Map completely open
- `with_spaces.cub` - Map with spaces in layout

**Note**: These maps intentionally keep incorrect texture paths (`./textures/`) to test error handling.

### 2. `/test_maps/mandatory/` - Working Maps for Mandatory Part
Valid maps for testing basic functionality:
- `simple_valid.cub` - Basic small map
- `circle_shape.cub` - Circular layout
- `l_shape.cub` - L-shaped layout
- `maze.cub` - Complex maze
- `spiral.cub` - Spiral design
- `a_large_complex.cub` - Large complex map
- `player_at_edge.cub` - Player near edge

**All maps have corrected texture paths**: `incs/assets/textures/Bricks_*.xpm`

### 3. `/test_maps/bonus/` - Maps for Bonus Features
Maps with special features for bonus testing:
- `doors_test.cub` - Map with doors (DR texture)
- `doors_test_alt.cub` - Alternative door configuration
- `doors_test_fixed.cub` - Fixed door layout
- `doors_no_texture.cub` - Door map without door texture

**All maps have corrected texture paths**: `incs/assets/textures/Bricks_*.xpm`

## Usage

### Testing Error Handling:
```bash
./cub3d test_maps/error/bad_rgb.cub          # Should show RGB error
./cub3d test_maps/error/no_player.cub        # Should show no player error
```

### Testing Mandatory Features:
```bash
./cub3d test_maps/mandatory/simple_valid.cub  # Basic functionality
./cub3d test_maps/mandatory/maze.cub          # Complex layout
```

### Testing Bonus Features:
```bash
./cub3d_bonus test_maps/bonus/doors_test.cub  # Door mechanics
```

## Texture Files Location
All working maps reference textures in: `incs/assets/textures/`
- `Bricks_North1.xpm`
- `Bricks_South1.xpm` 
- `Bricks_East1.xpm`
- `Bricks_West1.xpm`
- `door.xpm` (for bonus maps)
