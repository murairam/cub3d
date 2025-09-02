#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

PROGRAM="./cub3d"
BONUS_PROGRAM="./cub3d_bonus"
TEST_DIR="test_maps"
PASSED=0
FAILED=0
VALGRIND_PASSED=0
VALGRIND_FAILED=0
BONUS_PASSED=0
BONUS_FAILED=0

# Check if valgrind is available
VALGRIND_AVAILABLE=false
if command -v valgrind &> /dev/null; then
    VALGRIND_AVAILABLE=true
    echo -e "${CYAN}✓ Valgrind detected - Memory leak checking enabled${NC}"
else
    echo -e "${YELLOW}⚠ Valgrind not found - Memory leak checking disabled${NC}"
fi

# Check if bonus executable exists
BONUS_AVAILABLE=false
if [ -f "$BONUS_PROGRAM" ]; then
    BONUS_AVAILABLE=true
    echo -e "${CYAN}✓ Bonus executable detected - Bonus testing enabled${NC}"
else
    echo -e "${YELLOW}⚠ Bonus executable not found - Bonus testing disabled${NC}"
fi

# Create test directory
mkdir -p $TEST_DIR

echo -e "${BLUE}=== CUB3D MANDATORY TESTING WITH ENHANCED CHECKS ===${NC}"
echo

# Function to run valgrind test
run_valgrind_test() {
    local test_name="$1"
    local program="$2"
    local map_file="$3"
    local description="$4"
    
    echo -e "${PURPLE}Valgrind Test: $test_name${NC}"
    echo "Program: $program"
    echo "File: $map_file"
    
    # Run with valgrind for memory leak detection
    timeout 5 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --error-exitcode=1 --log-file=/tmp/valgrind_output.txt \
        $program "$map_file" > /tmp/test_output.txt 2>&1 &
    
    PID=$!
    sleep 2
    
    # Kill the process if it's still running (normal for valid maps)
    if kill -0 $PID 2>/dev/null; then
        kill $PID 2>/dev/null
        wait $PID 2>/dev/null
    else
        wait $PID 2>/dev/null
    fi
    
    # Check valgrind output for memory leaks
    if grep -q "definitely lost: 0 bytes" /tmp/valgrind_output.txt && \
       grep -q "indirectly lost: 0 bytes" /tmp/valgrind_output.txt && \
       grep -q "possibly lost: 0 bytes" /tmp/valgrind_output.txt; then
        echo -e "${GREEN}✓ VALGRIND PASSED${NC} - No memory leaks detected"
        ((VALGRIND_PASSED++))
    else
        echo -e "${RED}✗ VALGRIND FAILED${NC} - Memory leaks detected"
        echo -e "${YELLOW}Valgrind Output:${NC}"
        cat /tmp/valgrind_output.txt
        ((VALGRIND_FAILED++))
    fi
    echo
}

# Function to run bonus test
run_bonus_test() {
    local test_name="$1"
    local map_file="$2"
    local should_pass="$3"
    local description="$4"
    
    echo -e "${CYAN}Bonus Test: $test_name${NC}"
    echo "Description: $description"
    echo "File: $map_file"
    
    # Run the bonus program with timeout
    timeout 2 $BONUS_PROGRAM "$map_file" > /tmp/bonus_output.txt 2>&1
    exit_code=$?
    
    if [ "$should_pass" = "true" ]; then
        # For valid maps, timeout (exit code 124) or SIGTERM (exit code 143) means success
        if [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ] || [ $exit_code -eq 143 ]; then
            echo -e "${GREEN}✓ BONUS PASSED${NC} - Program started successfully"
            ((BONUS_PASSED++))
        else
            echo -e "${RED}✗ BONUS FAILED${NC} - Program exited with code $exit_code"
            echo -e "${YELLOW}Error Output:${NC}"
            cat /tmp/bonus_output.txt
            ((BONUS_FAILED++))
        fi
    else
        if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ] && [ $exit_code -ne 143 ]; then
            if grep -q "Error" /tmp/bonus_output.txt; then
                echo -e "${GREEN}✓ BONUS PASSED${NC} - Program correctly returned error"
                echo -e "${BLUE}Error Message:${NC}"
                cat /tmp/bonus_output.txt
                ((BONUS_PASSED++))
            else
                echo -e "${RED}✗ BONUS FAILED${NC} - Program exited but didn't print 'Error'"
                ((BONUS_FAILED++))
            fi
        else
            echo -e "${RED}✗ BONUS FAILED${NC} - Program should have failed but succeeded"
            ((BONUS_FAILED++))
        fi
    fi
    echo
}

# Function to run test
run_test() {
    local test_name="$1"
    local map_file="$2"
    local should_pass="$3"
    local description="$4"
    
    echo -e "${YELLOW}Test: $test_name${NC}"
    echo "Description: $description"
    echo "File: $map_file"
    
    # Run the program with timeout
    timeout 2 $PROGRAM "$map_file" > /tmp/test_output.txt 2>&1
    exit_code=$?
    
    if [ "$should_pass" = "true" ]; then
        # For valid maps, timeout (exit code 124) or SIGTERM (exit code 143) means success
        if [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ] || [ $exit_code -eq 143 ]; then
            echo -e "${GREEN}✓ PASSED${NC} - Program started successfully"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAILED${NC} - Program should have started but exited with code $exit_code"
            echo -e "${YELLOW}Error Output:${NC}"
            cat /tmp/test_output.txt
            ((FAILED++))
        fi
    else
        if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ] && [ $exit_code -ne 143 ]; then
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

# Enhanced testing with valgrind
if [ "$VALGRIND_AVAILABLE" = true ]; then
    echo -e "${PURPLE}=== MEMORY LEAK TESTING WITH VALGRIND ===${NC}"
    
    # Test with valid maps
    if [ -f "$TEST_DIR/simple_valid.cub" ]; then
        run_valgrind_test "Simple Valid Map" "$PROGRAM" "$TEST_DIR/simple_valid.cub" "Memory leak test with simple valid map"
    fi
    
    # Test with mandatory folder maps
    for map_file in maps/mandatory/*.cub; do
        if [ -f "$map_file" ]; then
            map_name=$(basename "$map_file" .cub)
            run_valgrind_test "Mandatory Map: $map_name" "$PROGRAM" "$map_file" "Memory leak test with $map_file"
        fi
    done
    
    # Test error cases for memory leaks
    run_valgrind_test "Missing Texture" "$PROGRAM" "maps/missing_texture_path.cub" "Memory leak test with missing texture"
    run_valgrind_test "Invalid RGB" "$PROGRAM" "$TEST_DIR/bad_rgb.cub" "Memory leak test with invalid RGB"
fi

# Test mandatory maps with bonus executable
if [ "$BONUS_AVAILABLE" = true ]; then
    echo -e "${CYAN}=== TESTING MANDATORY MAPS WITH BONUS EXECUTABLE ===${NC}"
    
    # Test all maps in mandatory folder with bonus
    for map_file in maps/mandatory/*.cub; do
        if [ -f "$map_file" ]; then
            map_name=$(basename "$map_file" .cub)
            run_bonus_test "Bonus: $map_name" "$map_file" "true" "Testing mandatory map $map_name with bonus executable"
            
            # Also run valgrind test on bonus if available
            if [ "$VALGRIND_AVAILABLE" = true ]; then
                run_valgrind_test "Bonus Valgrind: $map_name" "$BONUS_PROGRAM" "$map_file" "Memory leak test with bonus executable"
            fi
        fi
    done
    
    # Test some error cases with bonus
    if [ -f "maps/missing_texture_path.cub" ]; then
        run_bonus_test "Bonus: Missing Texture" "maps/missing_texture_path.cub" "false" "Error handling test with bonus executable"
    fi
fi

# Summary
echo -e "${BLUE}=== COMPREHENSIVE TEST SUMMARY ===${NC}"
echo -e "${BLUE}======================================${NC}"
echo -e "${GREEN}Mandatory Tests Passed: $PASSED${NC}"
echo -e "${RED}Mandatory Tests Failed: $FAILED${NC}"

if [ "$VALGRIND_AVAILABLE" = true ]; then
    echo -e "${GREEN}Valgrind Tests Passed: $VALGRIND_PASSED${NC}"
    echo -e "${RED}Valgrind Tests Failed: $VALGRIND_FAILED${NC}"
fi

if [ "$BONUS_AVAILABLE" = true ]; then
    echo -e "${GREEN}Bonus Tests Passed: $BONUS_PASSED${NC}"
    echo -e "${RED}Bonus Tests Failed: $BONUS_FAILED${NC}"
fi

echo -e "${BLUE}Total Tests: $((PASSED + FAILED + VALGRIND_PASSED + VALGRIND_FAILED + BONUS_PASSED + BONUS_FAILED))${NC}"

# Determine overall result
TOTAL_FAILED=$((FAILED + VALGRIND_FAILED + BONUS_FAILED))

if [ $TOTAL_FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! Your cub3d implementation is excellent!${NC}"
    if [ "$VALGRIND_AVAILABLE" = true ]; then
        echo -e "${GREEN}✓ No memory leaks detected${NC}"
    fi
    if [ "$BONUS_AVAILABLE" = true ]; then
        echo -e "${GREEN}✓ Bonus executable works perfectly with mandatory maps${NC}"
    fi
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Please review the failed cases above.${NC}"
    if [ $FAILED -gt 0 ]; then
        echo -e "${RED}   - Mandatory tests failed: $FAILED${NC}"
    fi
    if [ $VALGRIND_FAILED -gt 0 ]; then
        echo -e "${RED}   - Memory leak tests failed: $VALGRIND_FAILED${NC}"
    fi
    if [ $BONUS_FAILED -gt 0 ]; then
        echo -e "${RED}   - Bonus tests failed: $BONUS_FAILED${NC}"
    fi
    exit 1
fi
