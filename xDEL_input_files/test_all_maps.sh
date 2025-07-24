#!/bin/bash

echo "=== COMPREHENSIVE MAP TESTING ==="
echo "Testing all maps for correct error messages and memory leaks"
echo ""

MAPS_DIR="maps"
EXECUTABLE="./cub3d"
TOTAL_TESTS=0
PASSED_TESTS=0

# Function to test a single map
test_map() {
    local map_file="$1"
    local expected_error="$2"
    local should_succeed="$3"
    
    echo "--- Testing: $map_file ---"
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test for memory leaks with Valgrind
    echo "🔍 Valgrind check:"
    valgrind_output=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
        $EXECUTABLE "$MAPS_DIR/$map_file" 2>&1)
    
    valgrind_exit_code=$?
    
    # Check if valgrind output contains memory issues
    echo "$valgrind_output" | grep -E "(definitely lost|indirectly lost|possibly lost|All heap blocks were freed)"
    
    # Parse valgrind output to determine if there are actual memory issues
    if echo "$valgrind_output" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        memory_clean=true
    elif echo "$valgrind_output" | grep -qE "definitely lost: 0 bytes.*indirectly lost: 0 bytes.*possibly lost: 0 bytes"; then
        # Check if there are only "still reachable" blocks (not actual leaks)
        memory_clean=true
    else
        memory_clean=false
    fi
    
    # Test normal execution for error message
    echo "📝 Error message check:"
    program_output=$($EXECUTABLE "$MAPS_DIR/$map_file" 2>&1)
    program_exit_code=$?
    echo "$program_output"
    
    # Check expected behavior
    behavior_correct=false
    if [ "$should_succeed" = "true" ]; then
        if [ $program_exit_code -eq 0 ]; then
            echo "✅ Expected: SUCCESS, Got: SUCCESS"
            behavior_correct=true
        else
            echo "❌ Expected: SUCCESS, Got: FAILURE"
        fi
    else
        if [ $program_exit_code -eq 1 ] && echo "$program_output" | grep -q "$expected_error"; then
            echo "✅ Expected error: '$expected_error' - FOUND"
            behavior_correct=true
        elif [ $program_exit_code -eq 1 ]; then
            echo "❌ Expected error: '$expected_error', Got: '$(echo "$program_output" | grep "Error" -A1 | tail -1)'"
        else
            echo "❌ Expected: FAILURE, Got: SUCCESS"
        fi
    fi
    
    echo "💾 Memory status: $(if [ "$memory_clean" = true ]; then echo "✅ CLEAN"; else echo "❌ LEAKS"; fi)"
    echo "🎯 Behavior: $(if [ "$behavior_correct" = true ]; then echo "✅ CORRECT"; else echo "❌ WRONG"; fi)"
    echo ""
    
    if [ "$memory_clean" = true ] && [ "$behavior_correct" = true ]; then
        PASSED_TESTS=$((PASSED_TESTS + 1))
    fi
}

# Test all map files with expected behaviors
test_map "bad_rgb.cub" "RGB value must be between 0 and 255" "false"
test_map "boundary_rgb.cub" "" "true"
test_map "circle_shape.cub" "" "true"
test_map "duplicate_ceiling.cub" "Duplicate color" "false"
test_map "hole_in_wall.cub" "Map not properly enclosed by walls" "false"
test_map "l_shape.cub" "" "true"
test_map "large_complex.cub" "" "true"
test_map "leaky_map.cub" "Map not properly enclosed by walls" "false"
test_map "maze.cub" "" "true"
test_map "missing_texture_path.cub" "Invalid line" "false"
test_map "multi_player.cub" "Multiple players found in map" "false"
test_map "no_player.cub" "No player found in map" "false"
test_map "open_left.cub" "" "true"
test_map "player_at_edge.cub" "Map not properly enclosed by walls" "false"
test_map "rgb_negative.cub" "RGB value must be between 0 and 255" "false"
test_map "simple_valid.cub" "" "true"
test_map "spiral.cub" "" "true"
test_map "truly_open.cub" "Map not properly enclosed by walls" "false"
test_map "with_spaces.cub" "Map not properly enclosed by walls" "false"

echo "=== SUMMARY ==="
echo "Total tests: $TOTAL_TESTS"
echo "Passed (memory + behavior): $PASSED_TESTS"
echo "Failed: $((TOTAL_TESTS - PASSED_TESTS))"

if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
    echo "🎉 ALL TESTS PASSED! No memory leaks and correct behavior."
else
    echo "⚠️  Some tests failed. Check output above."
fi
