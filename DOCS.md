# **HT-Bash Language Reference Manual (Complete Edition)**

**Target Environment:** Bash v4.3 or newer.

HT-Bash is a high-level, structured language designed to compile into Bash. It enforces strict syntax rules to ensure readability and maintainability, eliminating the common pitfalls of raw shell scripting.

---

### **<a name="toc"></a>Table of Contents**

1.  [**Core Rule: No Expressions in Arguments**](#1-core-rule)
2.  [**Syntax: Comments**](#2-comments)
3.  [**Variables: Scope & Declaration**](#3-variables)
4.  [**Data Types**](#4-data-types)
5.  [**Operators: Assignment & Math**](#5-operators)
6.  [**Logic: Numeric Conditionals (Parentheses Required)**](#6-numeric-logic)
7.  [**Logic: String Conditionals (No Parentheses)**](#7-string-logic)
8.  [**Loops: Counted & Infinite**](#8-loops)
9.  [**Loops: String Parsing**](#9-parsing)
10. [**Arrays: Creation & Methods**](#10-arrays-basic)
11. [**Arrays: Advanced (Passing, Returning, Copying)**](#11-arrays-advanced)
12. [**Functions: Definition & Parameters**](#12-functions-def)
13. [**Functions: Return Values**](#13-functions-return)
14. [**Bash Integration (`run`)**](#14-bash)
15. [**Master Example 1: Log Rotation System**](#15-ex1)
16. [**Master Example 2: Service Health Monitor**](#16-ex2)
17. [**Master Caveat List**](#17-caveats)

---

### **<a name="1-core-rule"></a>1. Core Rule: No Expressions in Arguments**
[Go Back](#toc)

In HT-Bash, you **cannot** perform any operations directly inside a function call's argument list. This includes:

* Arithmetic (`+`, `-`, `*`, `/`, `%`, `**`)
* String concatenation (`.`)
* Nested function calls

The compiler requires you to calculate values in a variable *before* passing them. This keeps the generated Bash code clean and easier to debug.

**Additional Rule:**

* Arithmetic operations cannot be mixed with string concatenation.
* You **can** concatenate a number to a string, but you **cannot** use arithmetic symbols in a concatenation expression.

**Syntax Reference:**

```ahk
; INVALID
Func(1 + 1)
Func("A" . "B")

; VALID
int x := 1 + 1
Func(x)
```

**Example 1: Arithmetic Operations**
You cannot perform math inside a function call like `print`. You must perform the addition first, assign the result to an integer variable, and then pass that variable to the function. This prevents order-of-operation errors in the shell.

```ahk
; We want to print the sum of 10 and 20.
; First, we calculate the sum explicitly.
int result := 10 + 20

; Now we pass the clean variable to the print function.
print(result)
```

**Example 2: String Concatenation**
Attempting to join strings inside a `Log` function call will fail. You must use the concatenation operator `.` to build the full message string in a variable first. This makes the code more readable and allows you to inspect the message before sending it.

```ahk
str user := "admin"
; Construct the error message variable first.
str error_msg := "Access denied for user: " . user

; Pass the constructed string to the logging function.
Log(error_msg)
```

**Example 3: Nested Function Calls**
You cannot pass the result of one function directly into another (e.g., `Process(GetData())`). You must capture the return value of the inner function into a variable, then pass that variable to the outer function. This creates a clear data flow.

```ahk
; Assume GetData() returns a string.
str raw_data := GetData()

; Now pass that data to the processor.
Process(raw_data)
```

---

### **<a name="2-comments"></a>2. Syntax: Comments**
[Go Back](#toc)

Comments are used to document code logic. In HT-Bash, the semicolon `;` character marks the start of a comment. The compiler strips these out, so they do not affect the resulting script size or performance.

**Syntax Reference:**

```ahk
; Full line comment
var x := 1 ; Inline comment
```

**Example 1: Section Headers**
It is best practice to use full-line comments to separate logical sections of your code. This helps other developers (and yourself) scan the file quickly.

```ahk
; ==========================================
; Global Configuration Section
; ==========================================
str app_version := "1.0.0"
```

**Example 2: Inline Explanations**
You can place a comment at the end of a code line to explain the specific value or logic being used. This is useful for "magic numbers" or specific configuration flags.

```ahk
int max_retries := 5 ; Set to 5 to handle network jitters
int timeout := 30    ; Timeout in seconds
```

**Example 3: Debugging/Disabling Code**
Comments are frequently used to temporarily disable lines of code without deleting them. This is essential during the debugging process to isolate specific behaviors.

```ahk
; print("Verbose debugging output enabled")
print("Standard output only")
```

---

### **<a name="3-variables"></a>3. Variables: Scope & Declaration**
[Go Back](#toc)

HT-Bash enforces a strict scope system. **Global** variables are defined at the top level and are visible everywhere. **Local** variables are defined inside functions and are visible only there. You **must** use the `local` keyword inside functions.

**Syntax Reference:**

| Scope | Location | Keyword Requirement |
| :--- | :--- | :--- |
| **Global** | Top Level | **NO** `local` keyword |
| **Local** | Inside Function | **MUST** use `local` |

**Example 1: Defining Global Variables**
Global variables maintain the state of your application across multiple function calls. They should be defined at the very top of your file.

```ahk
; This variable is accessible by every function in the script.
str global_config_path := "/etc/myapp/config.ini"
int global_counter := 0
```

**Example 2: Defining Local Variables**
Inside a function, you must use `local`. This ensures that the variable `temp_val` does not conflict with any other variable named `temp_val` in other functions or the global scope.

```ahk
func Calculate() {
    ; This variable ceases to exist once Calculate() finishes.
    local int temp_val := 100
    local int result := temp_val * 2
    print(result)
}
```

**Example 3: Variable Shadowing**
You can define a local variable with the same name as a global variable. The function will use the local version, leaving the global version untouched. This is safe "shadowing."

```ahk
str status := "Running" ; Global

func Stop() {
    ; This local variable shadows the global one only inside this function.
    local str status := "Stopped"
    print(status) ; Prints "Stopped"
}

Stop()
print(status) ; Prints "Running" (Global is unchanged)
```

---

### **<a name="4-data-types"></a>4. Data Types**
[Go Back](#toc)

While Bash is loosely typed, HT-Bash uses explicit keywords to improve code clarity. `int` and `str` are decorative hints for the programmer. However, `arr` is **mandatory**; failing to use it prevents the compiler from generating array-specific logic.

**Syntax Reference:**

| Keyword | Type    | Mandatory?                | Notes                                  |
| :----   | :------ | :------------------------ | :--------------------------------------|
| `int`   | Integer | No just for readability   | Used for math/counters.                |
| `str`   | String  | No just for readability   | Used for text/strings.                         |
| `var`   | Variant | No just for readability   | Used for mixed or different data.                   |
| `arr`   | Array   | **YES**                   | Required for `.size()`, `.add()`, etc. |

**Example 1: Integer Usage**
Use `int` when dealing with numbers that will be used in arithmetic or numeric comparisons. This signals to the reader that math operations are valid on this variable.

```ahk
int file_count := 0
int max_limit := 1024
int negative_offset := -10
```

**Example 2: String Usage**
Use `str` for file paths, names, and messages. This signals that string manipulation (concatenation, parsing) will likely occur.

```ahk
str username := "john_doe"
str root_dir := "/var/www/html"
str empty_string := ""
```

**Example 3: Mandatory Array Declaration**
You must use `arr` when defining a list. If you used `var my_list := [...]`, the compiler would treat it as a string literal, breaking methods like `.add()` or `.pop()`.

```ahk
; Correct usage
arr server_list := ["web01", "web02", "db01"]

; Correct usage for empty array
arr process_queue := []
```

---

### **<a name="5-operators"></a>5. Operators: Assignment & Math**
[Go Back](#table-of-contents)

HT-Bash requires **whitespace around all operators**. This helps the tokenizer identify symbols. It supports standard math, modulo, power, and string concatenation.

**Syntax Reference:**

| Operator | Description | Example |
| :--- | :--- | :--- |
| `:=` | Assignment | `x := 1` |
| `+=` | Add/Assign | `x += 1` |
| `*=` | Multiply/Assign | `x *= 2` |
| `%=` | Modulo/Assign | `x %= 2` |
| `**=` | Power/Assign | `x **= 3` |
| `.=` | Concat/Assign | `s .= "A"` |
| `.` | Concatenate | `a . b` |

**Example 1: Advanced Arithmetic Assignment**
This demonstrates using power and modulo assignments. These are powerful features often missing in basic shells, useful for algorithms or determining even/odd numbers.

```ahk
int value := 2
value **= 3 ; value is now 8 (2^3)
value += 2  ; value is now 10
value %= 3  ; value is now 1 (10 mod 3)
print(value)
```

**Example 2: String Appending**
Building a string incrementally is done using `.=`. This is cleaner than `s := s . "new"`. It is commonly used for constructing log messages or SQL queries.

```ahk
str log_entry := "TIMESTAMP: "
log_entry .= "2023-01-01 "
log_entry .= "[ERROR] "
log_entry .= "Connection Failed"
print(log_entry)
```

**Example 3: Mixed Operations**
You can perform math and string operations in sequence (but not on the same line). Here we calculate an area and then format it into a string description.

```ahk
int width := 10
int height := 20
int area := width * height

str output := "The calculated area is: " . area
print(output)
```

---

### **<a name="6-numeric-logic"></a>6. Logic: Numeric Conditionals**
[Go Back](#toc)

**CRITICAL RULE:** When comparing **numbers**, you **MUST** enclose the condition in parentheses `()`. The transpiler uses these parentheses to generate the correct Bash arithmetic context `(( ))`.

**Syntax Reference:**

| Operator | Meaning                            | Syntax Example |
| :------- | :--------------------------------- | :------------- |
| `>`      | Greater Than                       | `if (x > y)`   |
| `<`      | Less Than                          | `if (x < y)`   |
| `=`      | Assignment / Equal To (ahk style)  | `if (x = y)`   |
| `==`     | Equal To (comparison)              | `if (x == y)`  |
| `!=`     | Not Equal                          | `if (x != y)`  |
| `>=`     | Greater Than or Equal To           | `if (x >= y)`  |
| `<=`     | Less Than or Equal To              | `if (x <= y)`  |

**Example 1: Basic Numeric Check**
Here we check if a user is an adult. Note the parentheses `(age >= 18)`. Without them, the code would generate a syntax error or incorrect behavior.

```ahk
int age := 21

if (age >= 18) {
    print("User is an adult.")
} else {
    print("User is a minor.")
}
```

**Example 2: Chained Numeric Logic**
You can check multiple numeric states using `else if`. Each condition must explicitly use parentheses. This logic sorts a temperature into categories.

```ahk
int temp := 35

if (temp > 100) {
    print("Gas State")
} else if (temp > 0) {
    print("Liquid State")
} else {
    print("Solid State")
}
```

**Example 3: Numeric While Loop**
Loops that depend on counters or numeric values follow the same rule. The condition `(count > 0)` controls the loop execution.

```ahk
int count := 3
print("Starting countdown...")

while (count > 0) {
    print(count)
    count -= 1
}
print("Liftoff!")
```

---

### **<a name="7-string-logic"></a>7. Logic: String Conditionals**
[Go Back](#toc)

**CRITICAL RULE:** When comparing **strings**, you **MUST NOT** use parentheses. The transpiler uses this absence of parentheses to generate standard Bash string tests `[[ ]]`.

**Syntax Reference:**

| Operator | Meaning | Syntax Example |
| :--- | :--- | :--- |
| `=` | String Match | `if s = "val"` |
| `!=` | String Mismatch | `if s != "val"` |

**Example 1: String Equality Check**
We check a command string. Note the lack of parentheses: `if command = "start"`. This distinguishes it from math.

```ahk
str command := "start"

if command = "start" {
    print("Initializing system sequences...")
}
```

**Example 2: String Inequality (Access Control)**
String inequality is useful for checking against forbidden values or ensuring a specific state is *not* present.

```ahk
str current_user := "guest"

if current_user != "admin" {
    print("Error: Administrative privileges required.")
} else {
    print("Welcome, Administrator.")
}
```

**Example 3: String-Based While Loop**
You can loop based on the state of a string variable. This is useful for waiting for a specific status or processing states.

```ahk
str status := "pending"

while status = "pending" {
    print("Waiting for approval...")
    ; In a real script, logic here would eventually change status
    status := "approved" 
}
print("Approved.")
```

---

### **<a name="8-loops"></a>8. Loops: Counted & Infinite**
[Go Back](#toc)

HT-Bash simplifies looping. Use `Loop, N` for a fixed number of iterations, or `Loop` (alone) for an infinite loop. The internal variable `A_Index` tracks the current iteration (starting at 0).

**Syntax Reference:**

| Type | Syntax | Internal Var |
| :--- | :--- | :--- |
| **Counted** | `Loop, 5 { ... }` | `A_Index` |
| **Infinite** | `Loop { ... }` | `A_Index` |
| **Control** | `break` / `continue` | N/A |

**Example 1: Fixed Count Loop**
This loop runs exactly 3 times. `A_Index` will be 0, 1, and then 2. We calculate a display number (1-3) inside the loop for user friendliness.

```ahk
str msg := ""
int display_num := 0
print("Repeating task 3 times:")
Loop, 3 {
    display_num := A_Index + 1
    msg := "Iteration number: " . display_num
    print(msg)
}
```

**Example 2: Infinite Loop with Break**
Sometimes you don't know how many times you need to loop. Use an infinite `Loop` and the `break` keyword to exit when a condition is met.

```ahk
int throughput := 0
print("Ramping up throughput...")

Loop {
    throughput += 10
    print(throughput)
    
    ; Break the loop if we hit the limit
    if (throughput = 50) {
        print("Max throughput reached.")
        break
    }
}
```

**Example 3: Skipping Iterations (Continue)**
The `continue` keyword skips the rest of the current loop cycle and jumps to the next one. Here, we use it to print only even numbers by skipping the odd ones.

```ahk
int count := 6

print("Even numbers only:")
Loop, count {
    int remainder := A_Index % 2
    
    ; If remainder is not 0, it's odd. Skip it.
    if (remainder != 0) {
        continue
    }
    print(A_Index)
}
```

---

### **<a name="9-parsing"></a>9. Loops: String Parsing**
[Go Back](#toc)

The `Loop, Parse` construct is designed to split a string by a specific delimiter character. The current piece of the string is available in `A_LoopField`.

**Syntax Reference:**

```ahk
Loop, Parse, InputVar, "Delimiter" {
    print(A_LoopField)
}
```

**Example 1: CSV Parsing**
Parsing Comma-Separated Values is a common task. Here we split a single string of fruits into individual items using the comma `,` delimiter.

```ahk
str csv_data := "apple,banana,cherry"
str fruit := ""

print("Parsing CSV data:")
Loop, Parse, csv_data, "," {
    fruit := A_LoopField
    print(fruit)
}
```

**Example 2: Parsing Newlines**
When reading files (via `run`), data often comes in line-by-line separated by `\n`. This example simulates processing a file list.

```ahk
str file_list := "file1.txt\nfile2.txt\nfile3.txt"
str current_file := ""

print("Processing files:")
Loop, Parse, file_list, "\n" {
    current_file := A_LoopField
    print(current_file)
}
```

**Example 3: Parsing Paths**
System paths are often separated by colons `:`. We can parse a path string to inspect individual directories.

```ahk
str system_path := "/bin:/usr/bin:/usr/local/bin"
str dir := ""

Loop, Parse, system_path, ":" {
    dir := "Found directory: " . A_LoopField
    print(dir)
}
```

---

### **<a name="10-arrays-basic"></a>10. Arrays: Creation & Methods**
[Go Back](#toc)

Arrays are ordered lists of data. In HT-Bash, array definitions **must be on a single line**. You must use the `arr` keyword.

**Syntax Reference:**

| Action | Syntax |
| :--- | :--- |
| **Create** | `arr x := ["a", "b"]` |
| **Add** | `x.add("c")` |
| **Remove** | `x.pop()` |
| **Get** | `var v := x[0]` |
| **Count** | `int s := x.size()` |

**Example 1: Definition and Access**
We create an array of colors. Note that the definition is on one line. We then access the first element using index `[0]`.

```ahk
arr colors := ["red", "green", "blue"]

; Access index 0
str primary := colors[0]
str msg := "Primary color: " . primary
print(msg)
```

**Example 2: Adding and Removing Items**
Arrays are dynamic. `.add()` puts an item at the end. `.pop()` removes the last item. Note that `.pop()` returns nothing; it just modifies the array.

```ahk
arr stack := []

stack.add("Task1")
stack.add("Task2")
str size_msg := "Stack size: "
size_msg .= stack.size()
print(size_msg) ; Prints 2

stack.pop() ; Removes Task2
print("Pop called.")
```

**Example 3: Iterating with a Loop**
To inspect every item in an array, use a standard `Loop` combined with the `.size()` method and `A_Index`.

```ahk
arr servers := ["srv-1", "srv-2", "srv-3"]
str log := ""
str current_srv := ""

Loop, servers.size() {
    ; Use A_Index to get the current item
    current_srv := servers[A_Index]
    log := "Connecting to: " . current_srv
    print(log)
}
```

---

### **<a name="11-arrays-advanced"></a>11. Arrays: Advanced (Passing, Returning, Copying)**
[Go Back](#toc)

This section details how to move arrays between functions, which requires specific syntax.

**Syntax Reference:**

| Action | Syntax |
| :--- | :--- |
| **Define the Function** | `func funcName(myArray[])` or  `func funcName(myArray[@])` |
| **Pass to Function** | `Func(myArray[@])` |
| **Return from Function** | `return_arr myArray[@]` |
| **Capture Return** | `new := @Func()` |
| **Duplicate/Clone** | `arr copy := (original[@])` |

**Example 1: Passing an Array**
You must expand the array using `[@]` when passing it to a function. If you forget this, only the first element will be passed.

```ahk
func ProcessList(items[]) {
    local int count := items.size()
    local str msg := "Processing " . count . " items."
    print(msg)
}

arr data := [100, 200, 300]
; Pass the array correctly
ProcessList(data[@])
```

**Example 2: Returning and Capturing an Array**
Functions return arrays using `return_arr`. The caller captures the array using the `@` prefix before the function name.

```ahk
func GetDefaultConfig() {
    arr defaults := ["verbose=true", "log=file"]
    return_arr defaults[@]
}

; Capture the returned array
arr config
config := @GetDefaultConfig()
print(config[0])
```

**Example 3: Duplicating an Array**
To create a separate copy of an array (so modifying one doesn't affect the other), you must re-wrap the expanded array in brackets.

```ahk
arr master_list := ["a", "b"]

; Create a clone
arr backup_list
backup_list := (master_list[@])

; Modify the backup
backup_list.add("c")

; Master list size is still 2, Backup is 3.
print(master_list.size())
print(backup_list.size())
```

---

### **<a name="12-functions-def"></a>12. Functions: Definition & Parameters**
[Go Back](#toc)

Functions allow you to encapsulate logic. Parameters act as local variables.

**Syntax Reference:**

```ahk
func Name(param1, param2 := "default") {
    ; code
}
```

#### **⚠️ Operational parameters whit arrays is NOT allowed.**

**Example 1: Simple Function**
A basic function definition. Note the K&R style brace `{` on the same line as the function name.

```ahk
func SayHello() {
    print("Hello from HT-Bash")
}
SayHello()
```

**Example 2: Parameters**
Parameters are variables passed into the function. They allow the function to work with dynamic data.

```ahk
func AddUser(username, id) {
    local str msg := "Adding user " . username . " with ID " . id
    print(msg)
}
AddUser("alice", 101)
```

**Example 3: Default Parameter Values**
You can define optional parameters by assigning them a value in the definition. If the caller doesn't provide a value, the default is used.

```ahk
func Alert(message, severity := "INFO") {
    local str log := "[" . severity . "] " . message
    print(log)
}

Alert("System boot")           ; Uses default INFO
Alert("Disk crash", "CRITICAL") ; Uses CRITICAL
```

---

### **<a name="13-functions-return"></a>13. Functions: Return Values**
[Go Back](#toc)

Functions can calculate and return data to the caller.

**Syntax Reference:**

| Return Type | Function Syntax | Caller Syntax |
| :--- | :--- | :--- |
| **Scalar** | `return x` | `var y := Func()` |
| **Array** | `return_arr x[@]` | `arr y := @Func()` |

**Example 1: Returning an Integer**
Here, a function performs a calculation and returns the result. The caller assigns this result to a variable.

```ahk
func Square(n) {
    local int res := n * n
    return res
}

int val := Square(4)
print(val) ; Prints 16
```

**Example 2: Returning a String**
Functions can also construct and return strings.

```ahk
func GetStatus() {
    return "Operational"
}

str current_status := GetStatus()
print(current_status)
```

**Example 3: Returning Multiple Items (via Array)**
Since a function can only return one "thing," use an array to return multiple pieces of data.

```ahk
func GetCoordinates() {
    arr coords := [10, 20] ; x, y
    return_arr coords[@]
}

arr point
point := @GetCoordinates()
print(point[0]) ; x
print(point[1]) ; y
```

---

### **<a name="14-bash"></a>14. Bash Integration (`run`)**
[Go Back](#toc)

The `run` keyword executes raw Bash commands. This is how you interact with the operating system.

**Syntax Reference:**

| Action | Syntax | Notes |
| :--- | :--- | :--- |
| **Execute** | `run cmd` | Result is discarded. |
| **Capture** | `run v=$(cmd)` | Result stored in Bash var `$v`. |

**Example 1: Executing Commands**
Use `run` to perform actions like creating directories or deleting files. The output is printed to the terminal if not captured.

```ahk
print("Setting up environment...")
run mkdir -p /tmp/app_data
run touch /tmp/app_data/init.lock
```

**Example 2: Capturing Output**
To use the result of a Bash command in your script, you must capture it into a Bash variable using `$()`. Note that you use `$var` to read it.

```ahk
run current_user=$(whoami)
run disk_free=$(df -h / | tail -1 | awk '{print $(NF-2)}')

run echo "User $current_user has $disk_free free on the root filesystem"
```

**Example 3: Conditional Bash Logic**
You can write raw Bash logic statements using `run` if you need to check specific file attributes (like existence) that HT-Bash doesn't natively support.

```ahk
str target := "/etc/passwd"

; Raw bash 'if' check
run if [ -w "$target" ]; then echo "Writable"; else echo "ReadOnly"; fi
```

---

### **<a name="15-ex1"></a>15. Master Example 1: Log Rotation System**
[Go Back](#toc)

This script manages application logs. It lists files, checks their size, and compresses them if they exceed a limit. It demonstrates parsing loops, numeric logic, and file system interaction.

```ahk
; ===================================================
; Log Rotation Master Script (Fixed)
; ===================================================

str log_directory := "/var/log"
int size_limit_kb := 5000 ; 5 MB

func ArchiveFile(file_name) {
    local str full_path := log_directory . "/" . file_name
    local str archive_path := full_path . ".gz"
    local str msg := "Archiving: " . file_name
    
    print(msg)
    
    ; Compress safely
    run gzip -c "$full_path" > "$archive_path"

    ; TRUE truncate (no newline, safe quoting)
    run : > "$full_path"
}

func AnalyzeFile(file_name) {
    local str full_path := log_directory . "/" . file_name
    local str msg := ""

    ; Real file size in KB
    run size=$(stat -c %s "$full_path")
    run size=$((size / 1024))
    
    if (size > size_limit_kb) {
        ArchiveFile(file_name)
    } else {
        msg := "Skipping " . file_name . " (Size: " . size . "KB)"
        print(msg)
    }
}

; --- Main Execution ---

print("Starting rotation job...")

run files=$(find "$log_directory" -maxdepth 1 -name "*.log" -printf "%f\n")

str current_file := ""

Loop, Parse, files, "\n" {
    current_file := A_LoopField
    
    if current_file != "" {
        AnalyzeFile(current_file)
    }
}

print("Job complete.")
```

---

### **<a name="16-ex2"></a>16. Master Example 2: Service Health Monitor**
[Go Back](#toc)

This script monitors a list of services. It demonstrates array handling (passing and returning), while loops for retries, and error reporting.

```ahk
; ===================================================
; Service Health Monitor
; ===================================================

arr services_to_watch := ["nginx", "postgresql", "redis"]
int max_retries := 3

func AlertAdmin(service_name) {
    run timestamp=$(date)
    local str alert := "CRITICAL ALERT: " . service_name . " down at " . timestamp
    print(alert)
    ; Imagine a 'run mail' command here
}

func CheckServiceStatus(svc) {
    local int attempts := 0
    local str status := "DOWN"
    local str info := ""
    
    ; Numeric While Loop: Parentheses REQUIRED
    while (attempts < max_retries) {
        attempts += 1
        
        info := "Checking " . svc . " (Attempt " . attempts . ")..."
        print(info)
        
        ; Check service status (0 = running)
        run systemctl is-active --quiet $svc
        run code=$?
        
        ; Numeric Comparison
        if (code = 0) {
            status := "UP"
            break ; Exit loop early on success
        }
        
        ; Wait before retry
        run sleep 2
    }
    
    return status
}

; --- Main Execution ---

print("Starting Service Monitor...")

str svc := "" 
str result := "" 
str msg := "" 

Loop, services_to_watch.size() {
    svc := services_to_watch[A_Index]
    result := CheckServiceStatus(svc)
    msg := ""

    ; String Comparison: Parentheses FORBIDDEN
    if result = "UP" {
        msg := "Service " . svc . " is healthy."
        print(msg)
    } else {
        AlertAdmin(svc)
    }
}

print("Monitor run finished.")
```

---

### **<a name="17-caveats"></a>17. Master Caveat List**
[Go Back](#toc)

1.  **Arguments:** **NO EXPRESSIONS**. Calculate `x := 1+1` first, then call `Func(x)`.
2.  **Logic:** Numbers use `()`, Strings **DO NOT**.
3.  **Whitespace:** Mandatory around all operators (`x := 1`).
4.  **Local:** Use `local` keyword inside functions, never outside.
5.  **Arrays:** Definition `[...]` must be on one line.
6.  **Passing Arrays:** Use `Func(arr[@])`.
7.  **Returning Arrays:** Use `return_arr` and `arr x := @Func()`.
8.  **Bash:** `run var=$(cmd)` creates a Bash variable `$var`.
9.  **Modulo:** Use `%` for remainder.
10. **Power:** Use `**` for exponents.
11. **Indexes:** `A_Index` and array indexes are 0-based.