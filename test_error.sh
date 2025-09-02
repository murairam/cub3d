#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

PROGRAM="./cub3d"
BONUS_PROGRAM="./cub3d_bonus"
ERROR_DIR="maps/error"
TOTAL_TESTS=0
MANDATORY_PASSED=0
MANDATORY_FAILED=0
BONUS_PASSED=0
BONUS_FAILED=0
VALGRIND_PASSED=0
VALGRIND_FAILED=0

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
    echo -e "${CYAN}✓ Bonus executable detected - Bonus error testing enabled${NC}"
else
    echo -e "${YELLOW}⚠ Bonus executable not found - Bonus testing disabled${NC}"
fi

# Check if error directory exists
if [ ! -d "$ERROR_DIR" ]; then
    echo -e "${RED}❌ Error directory '$ERROR_DIR' not found!${NC}"
    exit 1
fi

echo -e "${BOLD}${BLUE}=== CUB3D ERROR TESTING SUITE ===${NC}"
echo -e "${BLUE}Testing all maps in $ERROR_DIR folder${NC}"
echo -e "${BLUE}Expected: All maps should produce error messages and exit with non-zero status${NC}"
echo

# Function to test with mandatory executable
test_mandatory_error() {
    local map_file="$1"
    local map_name="$(basename "$map_file" .cub)"
    
    echo -e "${YELLOW}🔍 Testing: $map_name (Mandatory)${NC}"
    echo "File: $map_file"
    
    # Run the mandatory program
    $PROGRAM "$map_file" > /tmp/mandatory_error_output.txt 2>&1
    exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        # Check if output contains "Error"
        if grep -q "Error" /tmp/mandatory_error_output.txt; then
            echo -e "${GREEN}✓ MANDATORY PASSED${NC} - Correctly returned error (exit code: $exit_code)"
            echo -e "${BLUE}Error Message:${NC}"
            cat /tmp/mandatory_error_output.txt | sed 's/^/  /'
            ((MANDATORY_PASSED++))
        else
            echo -e "${RED}✗ MANDATORY FAILED${NC} - Exited with error but no 'Error' message"
            echo -e "${YELLOW}Output:${NC}"
            cat /tmp/mandatory_error_output.txt | sed 's/^/  /'
            ((MANDATORY_FAILED++))
        fi
    else
        echo -e "${RED}✗ MANDATORY FAILED${NC} - Should have failed but succeeded"
        echo -e "${YELLOW}Output:${NC}"
        cat /tmp/mandatory_error_output.txt | sed 's/^/  /'
        ((MANDATORY_FAILED++))
    fi
    echo
}

# Function to test with bonus executable
test_bonus_error() {
    local map_file="$1"
    local map_name="$(basename "$map_file" .cub)"
    
    echo -e "${CYAN}🎯 Testing: $map_name (Bonus)${NC}"
    echo "File: $map_file"
    
    # Run the bonus program
    $BONUS_PROGRAM "$map_file" > /tmp/bonus_error_output.txt 2>&1
    exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        # Check if output contains "Error"
        if grep -q "Error" /tmp/bonus_error_output.txt; then
            echo -e "${GREEN}✓ BONUS PASSED${NC} - Correctly returned error (exit code: $exit_code)"
            echo -e "${BLUE}Error Message:${NC}"
            cat /tmp/bonus_error_output.txt | sed 's/^/  /'
            ((BONUS_PASSED++))
        else
            echo -e "${RED}✗ BONUS FAILED${NC} - Exited with error but no 'Error' message"
            echo -e "${YELLOW}Output:${NC}"
            cat /tmp/bonus_error_output.txt | sed 's/^/  /'
            ((BONUS_FAILED++))
        fi
    else
        echo -e "${RED}✗ BONUS FAILED${NC} - Should have failed but succeeded"
        echo -e "${YELLOW}Output:${NC}"
        cat /tmp/bonus_error_output.txt | sed 's/^/  /'
        ((BONUS_FAILED++))
    fi
    echo
}

# Function to test with valgrind
test_valgrind_error() {
    local map_file="$1"
    local program="$2"
    local map_name="$(basename "$map_file" .cub)"
    local prog_name="$(basename "$program")"
    
    echo -e "${PURPLE}🩺 Memory Test: $map_name ($prog_name)${NC}"
    echo "File: $map_file"
    
    # Run with valgrind for memory leak detection
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
        --error-exitcode=42 --log-file=/tmp/valgrind_error_output.txt \
        $program "$map_file" > /tmp/program_error_output.txt 2>&1
    
    valgrind_exit=$?
    
    # Check if valgrind detected memory issues (exit code 42) or if program exited normally with error
    if grep -q "definitely lost: 0 bytes" /tmp/valgrind_error_output.txt && \
       grep -q "indirectly lost: 0 bytes" /tmp/valgrind_error_output.txt && \
       grep -q "possibly lost: 0 bytes" /tmp/valgrind_error_output.txt; then
        echo -e "${GREEN}✓ VALGRIND PASSED${NC} - No memory leaks detected"
        ((VALGRIND_PASSED++))
        
        # Show memory summary
        echo -e "${BLUE}Memory Summary:${NC}"
        grep -E "(in use at exit|total heap usage|definitely lost|All heap blocks)" /tmp/valgrind_error_output.txt | sed 's/^/  /'
    else
        echo -e "${RED}✗ VALGRIND FAILED${NC} - Memory issues detected"
        ((VALGRIND_FAILED++))
        echo -e "${YELLOW}Valgrind Output:${NC}"
        head -20 /tmp/valgrind_error_output.txt | sed 's/^/  /'
    fi
    echo
}

# Main testing loop
echo -e "${BOLD}${BLUE}=== TESTING ERROR MAPS ===${NC}"
echo

# Get all .cub files in error directory
for map_file in "$ERROR_DIR"/*.cub; do
    if [ -f "$map_file" ]; then
        map_name="$(basename "$map_file" .cub)"
        echo -e "${BOLD}${BLUE}📁 Testing Map: $map_name${NC}"
        echo "================================================"
        
        ((TOTAL_TESTS++))
        
        # Test with mandatory executable
        test_mandatory_error "$map_file"
        
        # Test with bonus executable if available
        if [ "$BONUS_AVAILABLE" = true ]; then
            test_bonus_error "$map_file"
        fi
        
        # Test with valgrind if available
        if [ "$VALGRIND_AVAILABLE" = true ]; then
            test_valgrind_error "$map_file" "$PROGRAM" "mandatory"
            
            if [ "$BONUS_AVAILABLE" = true ]; then
                test_valgrind_error "$map_file" "$BONUS_PROGRAM" "bonus"
            fi
        fi
        
        echo -e "${BLUE}================================================${NC}"
        echo
    fi
done

# Test .txt files and other invalid extensions
for invalid_file in "$ERROR_DIR"/*.txt "$ERROR_DIR"/*.invalid; do
    if [ -f "$invalid_file" ]; then
        echo -e "${BOLD}${BLUE}📁 Testing Invalid Extension: $(basename "$invalid_file")${NC}"
        echo "================================================"
        
        # Test with mandatory
        test_mandatory_error "$invalid_file"
        
        # Test with bonus if available
        if [ "$BONUS_AVAILABLE" = true ]; then
            test_bonus_error "$invalid_file"
        fi
        
        echo -e "${BLUE}================================================${NC}"
        echo
    fi
done

# Summary
echo -e "${BOLD}${BLUE}=== COMPREHENSIVE ERROR TESTING SUMMARY ===${NC}"
echo -e "${BLUE}======================================================${NC}"
echo -e "${YELLOW}Total Error Maps Tested: $TOTAL_TESTS${NC}"
echo
echo -e "${GREEN}Mandatory Error Tests Passed: $MANDATORY_PASSED${NC}"
echo -e "${RED}Mandatory Error Tests Failed: $MANDATORY_FAILED${NC}"

if [ "$BONUS_AVAILABLE" = true ]; then
    echo -e "${GREEN}Bonus Error Tests Passed: $BONUS_PASSED${NC}"
    echo -e "${RED}Bonus Error Tests Failed: $BONUS_FAILED${NC}"
fi

if [ "$VALGRIND_AVAILABLE" = true ]; then
    echo -e "${GREEN}Valgrind Tests Passed: $VALGRIND_PASSED${NC}"
    echo -e "${RED}Valgrind Tests Failed: $VALGRIND_FAILED${NC}"
fi

# Calculate totals
TOTAL_FAILED=$((MANDATORY_FAILED + BONUS_FAILED + VALGRIND_FAILED))
TOTAL_PASSED=$((MANDATORY_PASSED + BONUS_PASSED + VALGRIND_PASSED))

echo
echo -e "${BLUE}Overall Results:${NC}"
echo -e "${GREEN}Total Passed: $TOTAL_PASSED${NC}"
echo -e "${RED}Total Failed: $TOTAL_FAILED${NC}"

# Final assessment
if [ $TOTAL_FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL ERROR TESTS PASSED!${NC}"
    echo -e "${GREEN}✓ All invalid maps correctly produce error messages${NC}"
    echo -e "${GREEN}✓ All error handling is working properly${NC}"
    if [ "$VALGRIND_AVAILABLE" = true ]; then
        echo -e "${GREEN}✓ No memory leaks in error handling${NC}"
    fi
    exit 0
else
    echo -e "\n${RED}❌ Some error tests failed. Issues detected:${NC}"
    if [ $MANDATORY_FAILED -gt 0 ]; then
        echo -e "${RED}   - Mandatory error handling failed: $MANDATORY_FAILED tests${NC}"
    fi
    if [ $BONUS_FAILED -gt 0 ]; then
        echo -e "${RED}   - Bonus error handling failed: $BONUS_FAILED tests${NC}"
    fi
    if [ $VALGRIND_FAILED -gt 0 ]; then
        echo -e "${RED}   - Memory leaks in error handling: $VALGRIND_FAILED tests${NC}"
    fi
    echo -e "${YELLOW}Please review the failed cases above and fix error handling.${NC}"
    exit 1
fi
