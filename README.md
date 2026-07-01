<p align="center">
  <i>This project has been created as part of the 42 curriculum by eroque-d</i>
</p>
<h1 align="center">Get Next Line</h1>
<p align="center">
  <strong>Reading a line from a file descriptor is way too tedious.</strong>
</p>

## Description

`get_next_line` is a function that reads a file line by line from a file descriptor (`fd`). Each call to the function returns the next line found in the file, including the newline character `\n` if present, until the End of File (EOF) is reached.

### Functions

#### Core & Auxiliar functions

| Function | Description | Link |
| --- | --- | --- |
| **get_next_line** | Main function that orchestrates the buffer reading, line extraction, and state preservation. | [get_next_line](./get_next_line.c) |
| **read_and_stash** | Reads from the file descriptor using a specified `BUFFER_SIZE` and appends data to the stash. | [get_next_line.c](./get_next_line.c) |
| **extract_line** | Extracts the full line (up to the `\n` or EOF) from the accumulated stash to return it. | [get_next_line.c](./get_next_line.c) |
| **clean_stash** | Cleans the stash by removing the returned line and keeping only the remaining unread bytes. | [get_next_line.c](./get_next_line.c) |
| **ft_strchr** | Scans the stash or buffer to find the presence of a newline character (`\n`). | [get_next_line_utils.c](./get_next_line_utils.c) |
| **ft_strjoin_gnl** | Concatenates the newly read buffer into the persistent stash efficiently. | [get_next_line_utils.c](./get_next_line_utils.c) |

---

## Algorithm Explanation

The core challenge of `get_next_line` is managing an arbitrary `BUFFER_SIZE` while guaranteeing that only one line is returned per call, without losing bytes that belong to subsequent lines. 

The strategy selected relies on a **Static Accumulator (Stash)** combined with a **Strict $O(1)$ Buffer Search** optimization:

1. **Static Persistence:** A `static char *` pointer preserves data across multiple function calls. If a `read()` operation fetches more characters than a single line needs, the leftover bytes stay in the static memory for the next call.
2. **Buffer-Only Search ($O(1)$ Optimization):** To prevent performance drops and **TIMEOUT** errors on huge lines (especially with `BUFFER_SIZE=1`), the algorithm avoids scanning the entire growing stash for a `\n` inside the loop. Instead, it checks the stash once at entry, and during the read loop, it scans **only the newly read buffer block** via `ft_strchr(buffer, '\n')`.
3. **Data Segregation:** Once a newline or EOF is flagged:
   - `extract_line` copies everything up to `\n` into a new string to be returned to the user.
   - `clean_stash` frees the old block and reallocates the static pointer containing only the trailing bytes.

### Bonus Feature: Multiple File Descriptors
For the bonus implementation, the algorithm scales from a single static pointer to an array of static pointers (`static char *stash[FD_LIMIT]`). This tracks the reading state of up to `4096` different file descriptors concurrently, preventing cross-file data corruption when alternating calls between different files.

---

## Instructions

How to compile and use the `get_next_line` function in your projects!

Since `get_next_line` is integrated directly as source files rather than a separate compiled `.a` archive, you compile it alongside your target source code.

To compile your project with a custom `BUFFER_SIZE` (e.g., 42):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o program

```

To compile the **bonus version** (Multiple File Descriptors support):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o program

```

### Basic Usage

Include the header file in your source:

```c
#include "get_next_line.h"

```

Iterate through a file descriptor until the function returns `NULL`:

```c
int   fd = open("test.txt", O_RDONLY);
char  *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line); // Always free the returned line to avoid leaks!
}
close(fd);

```

---

## Resources

### Links

* [Unix File Descriptors](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/): Understanding low-level system inputs/outputs.
* [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/): Documentation about how static variables preserve state.

### AI

AI was used in this project solely for the following purposes:

* Troubleshooting algorithmic time complexity bottlenecks (helps fix `TIMEOUT` issues).
* Verifying proper standard-conforming edge-case behavior (e.g., handling unexpected EOF without trailing newlines).
* It helps explain some concepts.

---

## Timeline

| Event | Date |
| --- | --- |
| Started the `GNL` lists | `2026/06/14` |
| Last list completed | `2026/06/30` |

---

## License

This repository follows the [42 Unlicense](./LICENSE).

Feel free to open issues, suggest improvements or send pull requests! ദ്ദി˙ ᴗ ˙ )
