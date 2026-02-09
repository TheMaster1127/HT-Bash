#!/usr/bin/env bash
if ((BASH_VERSINFO[0] < 4 || (BASH_VERSINFO[0] == 4 && BASH_VERSINFO[1] < 3))); then
    echo "Error: This script requires Bash 4.3+. Update bash." >&2
    exit 1
fi

# ==========================================================
# HTVM Core Functions (Bash Implementation)
# ==========================================================

# Initialize Global Arguments (Matches C++ constructor logic)
# CALL THIS AT THE START OF YOUR SCRIPT: InitArgs "$@"
declare -a __HTVM_GLOBAL_ARGS
InitArgs() {
    __HTVM_GLOBAL_ARGS=("$@")
}

# Convert string to int (mimics std::istringstream >> int)
INT() {
    local str="$1"
    # Extract leading signed integer, ignore trailing garbage
    local val=$(grep -oE '^-?[0-9]+' <<< "$str" | head -n1)
    echo "${val:-0}"
}

# Convert various types to std::string (Overloaded STR in C++)
STR() {
    # Bash is typeless; simply echo the value. 
    # Boolean logic (1/0) is handled by the caller or passed as 1/0.
    echo "$1"
}

# Find position of needle in haystack (1-based index)
InStr() {
    local haystack="$1"
    local needle="$2"
    
    # If needle is empty or not found
    if [[ -z "$needle" ]] || [[ "$haystack" != *"$needle"* ]]; then
        echo 0
        return
    fi
    
    # Get prefix before match
    local prefix="${haystack%%$needle*}"
    # Return length of prefix + 1
    echo $(( ${#prefix} + 1 ))
}

# Read file content
FileRead() {
    local path="$1"
    if [[ ! -f "$path" ]]; then
        # C++ throws error, we print to stderr but return empty as per Bash conventions
        >&2 echo "Error: Could not open the file: $path"
        return
    fi
    cat "$path"
}

# Append to file (Returns 1 on success, 0 on fail)
FileAppend() {
    local content="$1"
    local path="$2"
    
    # Try append
    if printf "%s" "$content" >> "$path"; then
        echo 1
    else
        >&2 echo "Error: Could not open the file for appending."
        echo 0
    fi
}

# Delete file (Returns 1 on success, 0 on fail)
FileDelete() {
    local path="$1"
    if rm -f "$path"; then
        echo 1
    else
        echo 0
    fi
}

# String Length
StrLen() {
    echo "${#1}"
}

# Substring (Exact C++ Logic: 1-based start, negative handling)
SubStr() {
    local str="$1"
    local startPos="$2"
    local length="${3:--1}" # Default to -1
    local strLen="${#str}"

    # Handle negative starting positions
    if (( startPos < 0 )); then
        startPos=$(( strLen + startPos ))
        if (( startPos < 0 )); then startPos=0; fi
    else
        startPos=$(( startPos - 1 )) # Convert 1-based to 0-based
    fi

    # Handle length
    if (( length < 0 )); then
        length=$(( strLen - startPos ))
    elif (( startPos + length > strLen )); then
        length=$(( strLen - startPos ))
    fi

    # Bash substring expansion: ${var:start:length}
    # Check if length is valid (non-negative)
    if (( length < 0 )); then length=0; fi
    
    echo "${str:$startPos:$length}"
}

# Trim whitespace (Both ends)
Trim() {
    local input="$1"
    # Using extglob logic implicitly via pattern matching
    input="${input#"${input%%[![:space:]]*}"}"   # Trim leading
    input="${input%"${input##*[![:space:]]}"}"   # Trim trailing
    echo "$input"
}

# Replace all occurrences of 'find' with 'replaceWith' (Literal, NOT Regex)
StrReplace() {
    local originalString="$1"
    local find="$2"
    local replaceWith="$3"
    local result=""
    
    if [[ -z "$find" ]]; then
        echo "$originalString"
        return
    fi

    # Loop to handle literal replacement safely without regex chars interfering
    while [[ "$originalString" == *"$find"* ]]; do
        result+="${originalString%%$find*}$replaceWith"
        originalString="${originalString#*$find}"
    done
    result+="$originalString"
    echo "$result"
}

# Trim Left
StringTrimLeft() {
    local input="$1"
    local numChars="$2"
    echo "${input:$numChars}"
}

# Trim Right
StringTrimRight() {
    local input="$1"
    local numChars="$2"
    local len="${#input}"
    local end=$(( len - numChars ))
    if (( end < 0 )); then end=0; fi
    echo "${input:0:$end}"
}

# To Lowercase
StrLower() {
    local str="$1"
    echo "${str,,}"
}

# Split string and get Nth token (1-based index)
StrSplit() {
    local inputStr="$1"
    local delimiter="$2"
    local num="$3"
    
    local start=0
    local count=0
    local strLen="${#inputStr}"
    local delimLen="${#delimiter}"
    local tmpStr="$inputStr"
    
    # If delimiter is empty, return whole string if num==1
    if [[ -z "$delimiter" ]]; then
        [[ "$num" -eq 1 ]] && echo "$inputStr"
        return
    fi

    # Iterative search
    while [[ "$tmpStr" == *"$delimiter"* ]]; do
        local part="${tmpStr%%$delimiter*}"
        ((count++))
        if (( count == num )); then
            echo "$part"
            return
        fi
        # Remove the part we just processed + delimiter
        tmpStr="${tmpStr#*$delimiter}"
    done
    
    # Check the last part (remainder)
    if (( count + 1 == num )); then
        echo "$tmpStr"
    fi
}

# Character from Code
Chr() {
    local number="$1"
    if (( number >= 0 && number <= 1114111 )); then
        # Unicode safe print
        printf "\\U$(printf %08x "$number")"
    fi
}

# Modulo
Mod() {
    local dividend="$1"
    local divisor="$2"
    echo $(( dividend % divisor ))
}

# Check if OS is Windows
isWindows() {
    local unameOut="$(uname -s)"
    case "${unameOut}" in
        CYGWIN*|MINGW*|MSYS*) echo 1 ;;
        *) echo 0 ;;
    esac
}

# Get Params (Uses the global array populated by InitArgs)
GetParams() {
    local result=""
    # Start from index 0 of the args array (which corresponds to ARGV[1] effectively 
    # because InitArgs("$@") captures script args, excluding $0)
    for param in "${__HTVM_GLOBAL_ARGS[@]}"; do
        result+="${param}"$'\n'
    done
    echo -n "$result"
}

# Regex Replace
RegExReplace() {
    local inputStr="$1"
    local regexPattern="$2"
    local replacement="$3"
    
    # Use sed -E for extended regex
    echo "$inputStr" | sed -E "s/$regexPattern/$replacement/g"
}

# Regex Match (Returns position + 1, or 0)
RegExMatch() {
    local haystack="$1"
    local needle="$2"
    
    # Use awk to find the byte position (1-based)
    awk -v s="$haystack" -v p="$needle" 'BEGIN {
        if (match(s, p)) print RSTART; else print 0;
    }'
}