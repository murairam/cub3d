# cub3d
This is my cub3D game
I hope you like it

Summary: This project is inspired by the world-famous Wolfenstein 3D game, which is considered the first FPS ever created. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, where you will have to find your way.

## ✅ Cub3D Parser - COMPLETED

The cub3D parser has been fully refactored and tested. All major issues have been resolved:

### 🏆 Completed Features
- ✅ Robust error handling with immediate exit and cleanup on any parsing error
- ✅ Complete memory leak prevention (0 leaks in both success and error cases)
- ✅ `.cub` file extension validation
- ✅ Proper initialization of all `t_game` struct values
- ✅ Norminette compliance for core parsing logic
- ✅ Comprehensive map boundary validation
- ✅ Clean and organized code structure

## 🧩 Detailed Parsing Checklist

### 📁 File Handling
- [x] Check `.cub` file extension
- [x] Open and read the file
- [x] Handle empty or invalid files gracefully

### 🆔 Identifier Parsing
- [x] Parse texture paths: `NO`, `SO`, `WE`, `EA`
- [x] Validate that each texture is defined only once
- [ ] Check texture file accessibility (not required for parser)
- [x] Parse floor (`F`) and ceiling (`C`) RGB values
- [x] Validate RGB values are in correct format (0–255)

### 🗺️ Map Extraction
- [ ] Locate where map starts (after identifiers)
- [x] Store map lines in a 2D array
- [x] Normalize map rows to the same width (padding if needed)

### 👤 Player Info
- [ ] Detect player start position (`N`, `S`, `E`, `W`)
- [ ] Store player’s starting direction and coordinates
- [ ] Validate that exactly one player is present

### ✅ Map Validation
- [ ] Check all map characters are valid (`0`, `1`, `N`, `S`, `E`, `W`, space)
- [x] Ensure map is fully closed (no open edges)
- [ ] Check edges of map are walls or spaces only
- [ ] Detect and handle "holes" or leaks in map

### ⚠️ Error Handling
- [ ] Detect missing or duplicate identifiers
- [ ] Catch invalid or misformatted color values
- [ ] Handle invalid characters in map
- [ ] Report descriptive errors and exit cleanly

### 🧹 Final Steps
- [x] Free temporary memory used during parsing
- [x] Store all parsed data into game config structs
- [x] Write unit tests for parsing with good and bad `.cub` files


Sources
 * https://lodev.org/cgtutor/raycasting.html

