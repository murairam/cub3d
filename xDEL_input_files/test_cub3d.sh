#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to run a test
run_test() {
    local test_name="$1"
    local program="$2"
    local map_file="$3"
    local expected_exit="$4"  # 0 for success, 1 for error
    local description="$5"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Test $TOTAL_TESTS: $test_name${NC}"
    echo -e "  Description: $description"
    echo -e "  Command: $program $map_file"
    
    # Run the program with timeout and capture exit code
    timeout 2s ./$program "$map_file" >/dev/null 2>&1
    local exit_code=$?
    
    # Handle timeout (exit code 124)
    if [ $exit_code -eq 124 ]; then
        if [ $expected_exit -eq 0 ]; then
            echo -e "  ${GREEN}✓ PASS${NC} (timeout indicates program started successfully)"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "  ${RED}✗ FAIL${NC} (expected error but program started)"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    elif [ $exit_code -eq $expected_exit ]; then
        echo -e "  ${GREEN}✓ PASS${NC} (exit code: $exit_code)"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "  ${RED}✗ FAIL${NC} (expected: $expected_exit, got: $exit_code)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo
}

# Build programs
echo -e "${YELLOW}Building programs...${NC}"
make clean > /dev/null 2>&1
make > /dev/null 2>&1
make bonus > /dev/null 2>&1

if [ ! -f "cub3d" ] || [ ! -f "cub3d_bonus" ]; then
    echo -e "${RED}Error: Failed to build executables${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}\n"

# Test Categories
echo -e "${YELLOW}=== ARGUMENT VALIDATION TESTS ===${NC}"

# No arguments
run_test "No arguments" "cub3d" "" 1 "Should reject when no map file provided"
run_test "No arguments (bonus)" "cub3d_bonus" "" 1 "Should reject when no map file provided"

# Too many arguments  
run_test "Too many args" "cub3d" "maps/mandatory/simple_valid.cub extra" 1 "Should reject multiple arguments"

# Wrong extension
run_test "Wrong extension" "cub3d" "maps/mandatory/simple_valid.txt" 1 "Should reject non-.cub files"

# Non-existent file
run_test "Non-existent file" "cub3d" "maps/nonexistent.cub" 1 "Should reject missing files"

echo -e "${YELLOW}=== ERROR MAP TESTS ===${NC}"

# Test all error maps with mandatory version
for map in maps/error/*.cub; do
    if [ -f "$map" ]; then
        basename_map=$(basename "$map")
        run_test "Error map (mandatory)" "cub3d" "$map" 1 "Testing $basename_map - should fail"
    fi
done

# Test all error maps with bonus version
for map in maps/error/*.cub; do
    if [ -f "$map" ]; then
        basename_map=$(basename "$map")
        run_test "Error map (bonus)" "cub3d_bonus" "$map" 1 "Testing $basename_map - should fail"
    fi
done

echo -e "${YELLOW}=== VALID MAP TESTS ===${NC}"

# Test mandatory maps with mandatory version
for map in maps/mandatory/*.cub; do
    if [ -f "$map" ]; then
        basename_map=$(basename "$map")
        run_test "Valid map (mandatory)" "cub3d" "$map" 0 "Testing $basename_map - should start successfully"
    fi
done

# Test mandatory maps with bonus version (should also work)
for map in maps/mandatory/*.cub; do
    if [ -f "$map" ]; then
        basename_map=$(basename "$map")
        run_test "Valid map (bonus)" "cub3d_bonus" "$map" 0 "Testing $basename_map - should start successfully"
    fi
done

echo -e "${YELLOW}=== BONUS MAP TESTS ===${NC}"

# Test bonus maps with bonus version
for map in maps/bonus/*.cub; do
    if [ -f "$map" ]; then
        basename_map=$(basename "$map")
        run_test "Bonus map (bonus)" "cub3d_bonus" "$map" 0 "Testing $basename_map - should start successfully"
    fi
done

# Test bonus maps with mandatory version (might fail due to doors)
for map in maps/bonus/*.cub; do
    if [ -f "$map" ]; then
        basename_map=$(basename "$map")
        # Check if map contains doors
        if grep -q "D" "$map"; then
            run_test "Bonus map (mandatory)" "cub3d" "$map" 1 "Testing $basename_map - should fail (contains doors)"
        else
            run_test "Bonus map (mandatory)" "cub3d" "$map" 0 "Testing $basename_map - should work (no doors)"
        fi
    fi
done

echo -e "${YELLOW}=== TEST SUMMARY ===${NC}"
echo -e "Total tests: $TOTAL_TESTS"
echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
echo -e "${RED}Failed: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed.${NC}"
    exit 1
fi
