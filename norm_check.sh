#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Parse command line arguments
EXCLUDE_HEADERS=false
HELP=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --no-headers|--exclude-headers|-nh)
            EXCLUDE_HEADERS=true
            shift
            ;;
        --help|-h)
            HELP=true
            shift
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            HELP=true
            shift
            ;;
    esac
done

# Show help if requested
if [ "$HELP" = true ]; then
    echo -e "${BLUE}🔍 Norminette Check for Cub3D${NC}"
    echo ""
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --no-headers, --exclude-headers, -nh    Exclude header errors (INVALID_HEADER)"
    echo "  --help, -h                              Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                    # Check all norminette errors"
    echo "  $0 --no-headers      # Check all errors except missing 42 headers"
    echo "  $0 -nh               # Same as above (short form)"
    exit 0
fi

echo -e "${BLUE}🔍 Running Norminette Check for Cub3D${NC}"
echo -e "${BLUE}Excluding: mlx folder${NC}"
if [ "$EXCLUDE_HEADERS" = true ]; then
    echo -e "${YELLOW}Note: Excluding header errors (INVALID_HEADER)${NC}"
fi
echo ""

# Check if norminette is installed
if ! command -v norminette &> /dev/null; then
    echo -e "${RED}❌ Norminette is not installed!${NC}"
    echo -e "${YELLOW}Install it with: pip3 install norminette${NC}"
    exit 1
fi

# Initialize counters
total_files=0
error_files=0
total_errors=0

# Function to check files in a directory
check_directory() {
    local dir="$1"
    local exclude_pattern="$2"
    
    echo -e "${BLUE}Checking directory: $dir${NC}"
    
    # Find all .c and .h files, excluding mlx directory
    while IFS= read -r -d '' file; do
        # Skip if file contains mlx in path
        if [[ "$file" == *"/mlx/"* ]] || [[ "$file" == *"incs/mlx"* ]]; then
            continue
        fi
        
        ((total_files++))
        echo -n "  Checking $(basename "$file")... "
        
        # Run norminette on the file
        output=$(norminette "$file" 2>&1)
        exit_code=$?
        
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✅${NC}"
        else
            # Filter output if excluding headers
            if [ "$EXCLUDE_HEADERS" = true ]; then
                # Remove INVALID_HEADER lines and the corresponding Error: line
                filtered_output=$(echo "$output" | grep -v "Error: INVALID_HEADER")
                # Check if there are any non-OK lines left after filtering
                remaining_errors=$(echo "$filtered_output" | grep -v "OK!" | grep -v "^$" | grep -v ": Error!$")
                if [ -z "$remaining_errors" ]; then
                    echo -e "${GREEN}✅${NC} (header errors ignored)"
                else
                    echo -e "${RED}❌${NC}"
                    ((error_files++))
                    echo -e "${RED}    Errors in $file:${NC}"
                    error_count=$(echo "$remaining_errors" | wc -l)
                    ((total_errors += error_count))
                    echo "$remaining_errors" | sed 's/^/      /'
                    echo ""
                fi
            else
                echo -e "${RED}❌${NC}"
                ((error_files++))
                echo -e "${RED}    Errors in $file:${NC}"
                # Count errors (lines that don't contain "OK!" and aren't empty)
                file_errors=$(echo "$output" | grep -v "OK!" | grep -v "^$" | wc -l)
                ((total_errors += file_errors))
                echo "$output" | sed 's/^/      /'
                echo ""
            fi
        fi
    done < <(find "$dir" -type f \( -name "*.c" -o -name "*.h" \) -print0)
}

# Check main source directories
if [ -d "srcs" ]; then
    check_directory "srcs"
fi

if [ -d "incs" ]; then
    check_directory "incs"
fi

if [ -d "bonus" ]; then
    check_directory "bonus"
fi

# Check root directory for .c and .h files
echo -e "${BLUE}Checking root directory${NC}"
shopt -s nullglob 2>/dev/null || true  # Enable nullglob for bash, ignore error in zsh
for file in *.c *.h; do
    if [ -f "$file" ]; then
        ((total_files++))
        echo -n "  Checking $file... "
        
        output=$(norminette "$file" 2>&1)
        exit_code=$?
        
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✅${NC}"
        else
            # Filter output if excluding headers
            if [ "$EXCLUDE_HEADERS" = true ]; then
                filtered_output=$(echo "$output" | grep -v "INVALID_HEADER")
                # Check if there are any errors left after filtering
                error_count=$(echo "$filtered_output" | grep -v "OK!" | grep -v "^$" | wc -l)
                if [ $error_count -eq 0 ]; then
                    echo -e "${GREEN}✅${NC} (header errors ignored)"
                else
                    echo -e "${RED}❌${NC}"
                    ((error_files++))
                    ((total_errors += error_count))
                    echo -e "${RED}    Errors in $file:${NC}"
                    echo "$filtered_output" | sed 's/^/      /'
                    echo ""
                fi
            else
                echo -e "${RED}❌${NC}"
                ((error_files++))
                file_errors=$(echo "$output" | grep -v "OK!" | grep -v "^$" | wc -l)
                ((total_errors += file_errors))
                echo -e "${RED}    Errors in $file:${NC}"
                echo "$output" | sed 's/^/      /'
                echo ""
            fi
        fi
    fi
done
shopt -u nullglob 2>/dev/null || true  # Disable nullglob

# Summary
echo ""
echo -e "${BLUE}📊 Norminette Check Summary${NC}"
echo "================================"
echo -e "Total files checked: ${BLUE}$total_files${NC}"
echo -e "Files with errors: ${RED}$error_files${NC}"
echo -e "Total errors: ${RED}$total_errors${NC}"

if [ $error_files -eq 0 ]; then
    echo ""
    echo -e "${GREEN}🎉 All files pass norminette! Great job!${NC}"
    exit 0
else
    echo ""
    echo -e "${RED}⚠️  Please fix the norminette errors above.${NC}"
    exit 1
fi
