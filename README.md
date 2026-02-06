# get_next_line
# get_next_line

## 📌 Description

`get_next_line` is a function that reads a file descriptor line by line. Each call returns the next line from the given file until the end of file (EOF) is reached.

This project is part of the **42 School curriculum** and focuses on file handling, static variables, memory management, and buffer manipulation in C.

---

## 📂 Function Prototype

```c
char *get_next_line(int fd);
```

---

## ⚙️ How It Works

* Reads data from a file descriptor using `read()`
* Stores remaining data between calls using a `static` variable
* Extracts one line at a time
* Returns the line including the newline character (`\n`) if present
* Returns `NULL` when no more lines are available or on error

---

## 📋 Features

✅ Reads one line at a time

✅ Works with any valid file descriptor

✅ Handles multiple file descriptors (if bonus implemented)

✅ Efficient memory management

✅ Supports variable buffer sizes

* Multiple file descriptors simultaneously
  
* Separate static buffers per `fd`
  
---

## 🧩 Buffer Size

The reading size is defined using `BUFFER_SIZE`:

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
```

You can modify it when compiling:

```bash
cc -D BUFFER_SIZE=1000 *.c
```

---

## 📁 Project Structure

```
get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
└── README.md
```

---

## 🔧 Usage

### Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## 🧠 Algorithm Overview

1. Read from `fd` into a buffer
2. Append buffer to a static string
3. Check for `\n`
4. Extract line if found
5. Save remaining data
6. Return extracted line

---

## 🗃️ Memory Management

* All returned lines are dynamically allocated
* The caller must free each line
* Internal buffers are freed at EOF

⚠️ Failing to free returned lines will cause memory leaks.

---

## ❗ Return Values

| Return Value | Meaning               |
| ------------ | --------------------- |
| Line string  | A valid line was read |
| `NULL`       | EOF or error          |

---

## 🚫 Error Handling

* Returns `NULL` if:

  * `fd` is invalid
  * `read()` fails
  * Memory allocation fails

---

## 📚 Allowed Functions

* `read`
* `malloc`
* `free`

---

## 📖 Norm Compliance

This project follows the **42 Norm**:

* Max 25 lines per function
* Max 5 functions per file
* Proper indentation
* No forbidden functions

---

## ✅ Testing

Recommended tests:

```bash
./a.out < file.txt
./a.out /dev/stdin
./a.out /dev/random
```

Use Valgrind:

```bash
valgrind --leak-check=full ./a.out
```

---

## 📜 License

This project is for educational purposes under the 42 School curriculum.

---
