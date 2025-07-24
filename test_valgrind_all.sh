#!/bin/bash

echo "=== COMPREHENSIVE VALGRIND TEST FOR ALL MAPS ==="
echo "Testing $(ls maps/*.cub | wc -l) map files..."
echo

TOTAL_MAPS=0
CLEAN_MAPS=0
LEAKY_MAPS=0

for map_file in maps/*.cub; do
    TOTAL_MAPS=$((TOTAL_MAPS + 1))
    echo "Testing: $map_file"
    
    # Run valgrind and capture output  
    VALGRIND_OUTPUT=$(valgrind --leak-check=full --track-origins=yes ./cub3d "$map_file" 2>&1)
    EXIT_CODE=$?
    
    # Check for leaks in valgrind output
    if echo "$VALGRIND_OUTPUT" | grep -q "All heap blocks were freed -- no leaks are possible"; then
        echo "  ✅ CLEAN - No memory leaks"
        CLEAN_MAPS=$((CLEAN_MAPS + 1))
    else
        echo "  ❌ LEAKS DETECTED"
        LEAKY_MAPS=$((LEAKY_MAPS + 1))
        # Show leak summary
        echo "$VALGRIND_OUTPUT" | grep -A 6 "LEAK SUMMARY" | head -8
    fi
    
    echo "  Program exit code: $([[ $EXIT_CODE -eq 42 ]] && echo "VALGRIND_ERROR" || echo $EXIT_CODE)"
    echo
done

echo "=== SUMMARY ==="
echo "Total maps tested: $TOTAL_MAPS"
echo "Clean maps: $CLEAN_MAPS"
echo "Leaky maps: $LEAKY_MAPS"
echo "Success rate: $((CLEAN_MAPS * 100 / TOTAL_MAPS))%"
