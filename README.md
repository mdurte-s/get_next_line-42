*This project has been created as part of the 42 curriculum by mdurte-s.*

## Get Next Line
### Description

This is a C project that implements a function to read files line by line in a memory-efficient way. The core function `get_next_line()` reads from a file descriptor and returns one complete line at a time, including the newline character if present.

The **goal** of this project is to:
- Understand file I/O operations in C;
- Implement efficient buffer management using static variables;
- Handle dynamic memory allocation and deallocation;
- Process data sequentially from file descriptors;
- Manage edge cases such as empty files, missing newlines, and read errors.

**Key Features:**

- **Single line reading**: Returns exactly one line per function call;
- **Multiple file descriptor support**: Can handle multiple files simultaneously using static storage;
- **Configurable buffer size**: Uses a `BUFFER_SIZE` macro for flexible memory allocation;
- **Bonus version**: Extended version supporting multiple file descriptors without conflicts;
- **Comprehensive test suite**: Includes test files with various edge cases (empty files, files with/without newlines, large lines, etc.).

### Instructions

**Compilation | Basic Version (Mandatory)**
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line_utils.c
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line_main.c
gcc -o get_next_line get_next_line.o get_next_line_utils.o get_next_line_main.o
```

**Compilation | Bonus Version**
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line_bonus.c
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line_utils_bonus.c
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line_main.c
gcc -o get_next_line get_next_line_bonus.o get_next_line_utils_bonus.o get_next_line_main.o
```

**Basic Usage**
```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

**Buffer Size Configuration**

The `BUFFER_SIZE` macro can be adjusted at compile time:
```bash
gcc -D BUFFER_SIZE=1024 ...      # 1KB buffer
gcc -D BUFFER_SIZE=4096 ...      # 4KB buffer
gcc -D BUFFER_SIZE=1 ...         # 1 byte buffer (for testing)
```

### Algorithm Explanation and Justification

The `get_next_line()` function uses a **static buffer approach** to efficiently read and return one line at a time from any file descriptor. Here's how it works:

**Core Components:**

1. **Static Stash Buffer**
   ```c
   static char *stash;
   ```
   - Maintains data between function calls
   - Allows reading multiple lines from the same file sequentially
   - Each call picks up from where the previous one left off

2. **Three-Phase Algorithm**

   **Phase 1: Read and Accumulate (read_and_stash)**
   - Reads chunks of size `BUFFER_SIZE` from the file descriptor
   - Concatenates each chunk to the stash buffer
   - Continues until a newline character is found or EOF is reached
   - Handles read errors gracefully

   **Phase 2: Extract Line (extract_line)**
   - Scans the stash for a newline character
   - Allocates memory for the extracted line (including the newline)
   - Returns the complete line ready for the caller

   **Phase 3: Update Stash (new_stash)**
   - Removes the returned line from the stash
   - Preserves remaining data for the next function call
   - Frees memory of processed data

**Why This Algorithm?**

1. **Memory Efficiency**: The algorithm only reads what's needed from disk. Using a configurable `BUFFER_SIZE` allows users to balance memory usage and I/O efficiency based on their requirements.

2. **State Preservation**: The static variable maintains context between calls, enabling seamless sequential line reading without requiring the caller to manage buffer state.

3. **Handling Multiple Files**: Each call to `get_next_line()` operates on a different file descriptor, allowing multiple files to be read concurrently (though with the caveat that only one static stash is maintained in the mandatory version).

4. **Edge Case Management**:
   - **Empty files**: Returns `NULL` immediately
   - **Missing newlines**: Returns the entire remaining content as the final line
   - **Large lines**: Works regardless of line length (only limited by available memory)
   - **Read errors**: Properly frees memory and returns `NULL`

**Memory Management**

The algorithm uses careful memory management:
- **ft_strjoin()**: Safely concatenates strings with proper allocation
- **ft_strlcpy()** and **ft_strlcat()**: Prevent buffer overflows
- **clean_data()**: Ensures all temporary allocations are freed

**Time and Space Complexity**

- **Time Complexity**: O(n) where n is the total number of characters read from the file
- **Space Complexity**: O(m) where m is the maximum size of the stash buffer at any point, bounded by line length + `BUFFER_SIZE`

**Bonus Version Enhancement**

The bonus version removes the single static stash limitation by allowing multiple file descriptors to maintain their own stash independently, using a more sophisticated state management approach.

### Resources

- Manual pages: `read` (file descriptor reading) and `open` (file descriptor operations);
- Oficial 42 get_next_line Subject;
- Peer-to-Peer Learning.

### AI Usage

AI tools were used in the development of this project to understand how to use static variables. 

## Notes

- The `BUFFER_SIZE` macro can be defined at compile time;
- The minimum valid `BUFFER_SIZE` is 1 byte;
- Negative file descriptors or `BUFFER_SIZE <= 0` return `NULL`;
- The function returns `NULL` at EOF or on error;
- Memory must be freed by the caller for returned lines;
- Statically allocated memory is not freed (by design in the mandatory version).