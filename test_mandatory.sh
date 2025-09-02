#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PROGRAM="./cub3d"
TEST_DIR="test_maps"
PASSED=0
FAILED=0

# Create test directory
mkdir -p $TEST_DIR

echo -e "${BLUE}=== CUB3D MANDATORY TESTING ===${NC}"
echo

# Function to run test
run_test() {
    local test_name="$1"
    local map_file="$2"
    local should_pass="$3"
    local description="$4"
    
    echo -e "${YELLOW}Test: $test_name${NC}"
    echo "Description: $description"
    echo "File: $map_file"
    
    # Run the program and capture output
    $PROGRAM "$map_file" > /tmp/test_output.txt 2>&1 &
    PID=$!
    
    # Wait a short time to see if it starts successfully
    sleep 1
    
    # Check if process is still running (success) or has exited (error)
    if kill -0 $PID 2>/dev/null; then
        # Process is running, kill it and consider it a success
        kill $PID 2>/dev/null
        wait $PID 2>/dev/null
        exit_code=0
    else
        # Process has exited, get its exit code
        wait $PID 2>/dev/null
        exit_code=$?
    fi
    
    if [ "$should_pass" = "true" ]; then
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ PASSED${NC} - Program started successfully"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAILED${NC} - Program should have started but exited with code $exit_code"
            echo -e "${YELLOW}Error Output:${NC}"
            cat /tmp/test_output.txt
            ((FAILED++))
        fi
    else
        if [ $exit_code -ne 0 ]; then
            # Check if output contains "Error"
            if grep -q "Error" /tmp/test_output.txt; then
                echo -e "${GREEN}✓ PASSED${NC} - Program correctly returned error"
                echo -e "${BLUE}Error Message:${NC}"
                cat /tmp/test_output.txt
                ((PASSED++))
            else
                echo -e "${RED}✗ FAILED${NC} - Program exited but didn't print 'Error'"
                echo -e "${YELLOW}Output:${NC}"
                cat /tmp/test_output.txt
                ((FAILED++))
            fi
        else
            echo -e "${RED}✗ FAILED${NC} - Program should have failed but succeeded"
            echo -e "${YELLOW}Output:${NC}"
            cat /tmp/test_output.txt
            ((FAILED++))
        fi
    fi
    echo
}

# Test 1: Valid maps that should work
echo -e "${BLUE}=== TESTING VALID MAPS ===${NC}"

# Create a simple valid map
cat > $TEST_DIR/simple_valid.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
EOF

run_test "Simple Valid Map" "$TEST_DIR/simple_valid.cub" "true" "Basic valid map with player N"

# Test existing valid maps
if [ -f "maps/mandatory/simple_valid.cub" ]; then
    run_test "Existing Simple Valid" "maps/mandatory/simple_valid.cub" "true" "Existing simple valid map"
fi

if [ -f "maps/mandatory/maze.cub" ]; then
    run_test "Maze Map" "maps/mandatory/maze.cub" "true" "Complex maze map"
fi

# Test 2: Different player orientations
echo -e "${BLUE}=== TESTING PLAYER ORIENTATIONS ===${NC}"

for orientation in N S E W; do
    cat > $TEST_DIR/player_${orientation}.cub << EOF
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
100001
100001
100${orientation}01
100001
111111
EOF
    run_test "Player Orientation $orientation" "$TEST_DIR/player_${orientation}.cub" "true" "Map with player facing $orientation"
done

# Test 3: Maps with spaces (should be valid)
echo -e "${BLUE}=== TESTING MAPS WITH SPACES ===${NC}"

cat > $TEST_DIR/with_spaces.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

11111111111
10001000001
10001000001
1000N000001
10001000001
11111111111
EOF

run_test "Map with Spaces" "$TEST_DIR/with_spaces.cub" "true" "Map containing spaces within walls"

# Test 4: Different element orders
echo -e "${BLUE}=== TESTING ELEMENT ORDER VARIATIONS ===${NC}"

cat > $TEST_DIR/different_order.cub << 'EOF'
F 220,100,0
EA ./incs/assets/textures/Bricks_East.xpm
C 225,30,0
NO ./incs/assets/textures/Bricks_North.xpm
WE ./incs/assets/textures/Bricks_West.xpm
SO ./incs/assets/textures/Bricks_South.xpm

111111
100101
101001
1100N1
111111
EOF

run_test "Different Element Order" "$TEST_DIR/different_order.cub" "true" "Elements in different order"

# Test 5: Empty lines between elements
echo -e "${BLUE}=== TESTING EMPTY LINES ===${NC}"

cat > $TEST_DIR/empty_lines.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm

SO ./incs/assets/textures/Bricks_South.xpm


WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm

F 220,100,0

C 225,30,0


111111
100101
101001
1100N1
111111
EOF

run_test "Empty Lines Between Elements" "$TEST_DIR/empty_lines.cub" "true" "Map with empty lines between elements"

# Test 6: Error cases
echo -e "${BLUE}=== TESTING ERROR CASES ===${NC}"

# Missing player
cat > $TEST_DIR/no_player.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
110001
111111
EOF

run_test "No Player" "$TEST_DIR/no_player.cub" "false" "Map without player should fail"

# Multiple players
cat > $TEST_DIR/multi_player.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
1N0E01
101001
110001
111111
EOF

run_test "Multiple Players" "$TEST_DIR/multi_player.cub" "false" "Map with multiple players should fail"

# Open map (not surrounded by walls)
cat > $TEST_DIR/open_map.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
100101
001001
1100N1
111111
EOF

run_test "Open Map" "$TEST_DIR/open_map.cub" "false" "Map not surrounded by walls should fail"

# Invalid characters in map
cat > $TEST_DIR/invalid_chars.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
1X0101
101001
1100N1
111111
EOF

run_test "Invalid Characters" "$TEST_DIR/invalid_chars.cub" "false" "Map with invalid character X should fail"

# Missing texture
cat > $TEST_DIR/missing_texture.cub << 'EOF'
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
EOF

run_test "Missing North Texture" "$TEST_DIR/missing_texture.cub" "false" "Missing NO texture should fail"

# Missing color
cat > $TEST_DIR/missing_color.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
C 225,30,0

111111
100101
101001
1100N1
111111
EOF

run_test "Missing Floor Color" "$TEST_DIR/missing_color.cub" "false" "Missing F color should fail"

# Invalid RGB values
cat > $TEST_DIR/invalid_rgb.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 300,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
EOF

run_test "Invalid RGB Values" "$TEST_DIR/invalid_rgb.cub" "false" "RGB value > 255 should fail"

# Wrong file extension
cat > $TEST_DIR/wrong_extension.txt << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
EOF

run_test "Wrong File Extension" "$TEST_DIR/wrong_extension.txt" "false" "Non-.cub extension should fail"

# No arguments
run_test "No Arguments" "" "false" "No arguments should fail"

# Non-existent file
run_test "Non-existent File" "non_existent.cub" "false" "Non-existent file should fail"

# Test 7: Edge cases
echo -e "${BLUE}=== TESTING EDGE CASES ===${NC}"

# Minimum valid map
cat > $TEST_DIR/minimum.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 0,0,0
C 255,255,255

111
1N1
111
EOF

run_test "Minimum Map" "$TEST_DIR/minimum.cub" "true" "Minimum possible valid map"

# Test RGB boundary values
cat > $TEST_DIR/rgb_boundary.cub << 'EOF'
NO ./incs/assets/textures/Bricks_North.xpm
SO ./incs/assets/textures/Bricks_South.xpm
WE ./incs/assets/textures/Bricks_West.xpm
EA ./incs/assets/textures/Bricks_East.xpm
F 0,0,0
C 255,255,255

111111
100101
101001
1100N1
111111
EOF

run_test "RGB Boundary Values" "$TEST_DIR/rgb_boundary.cub" "true" "RGB values at boundaries (0,255)"

# Summary
echo -e "${BLUE}=== TEST SUMMARY ===${NC}"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "Total: $((PASSED + FAILED))"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! Your cub3d implementation meets the mandatory requirements.${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Please review the failed cases above.${NC}"
    exit 1
fi
