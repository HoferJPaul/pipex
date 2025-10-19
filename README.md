# 🛠️ Pipex

**Pipex** is a C program that replicates the behavior of UNIX shell piping. It uses system calls like `fork`, `execve`, `pipe`, and `dup2` to execute a sequence of commands with input/output redirection — mimicking the shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

---

## 📌 Project Overview

This project is part of the 42 core curriculum and aims to deepen your understanding of:

- UNIX process creation
- Pipes and file descriptors
- Input/output redirection
- Command execution (`execve`)
- Error handling and memory management

---

## 🚀 How It Works

### ✅ Mandatory Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

This should behave **exactly** like:

```bash
< file1 cmd1 | cmd2 > file2
```

### 💡 Example

```bash
./pipex infile "grep error" "wc -l" outfile
```

Will behave like:

```bash
< infile grep error | wc -l > outfile
```

---

## 🔧 Allowed Functions

- `open`, `close`, `read`, `write`
- `malloc`, `free`, `access`, `perror`, `strerror`
- `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`
- `wait`, `waitpid`, `unlink`
- Your own `libft` functions (copied into the repo)

---

## 📁 File Structure

```
pipex/
├── pipex.h           # Header file with function prototypes and includes
├── main.c            # Entry point
├── utils.c           # Main logic for pipes, processes, redirection
├── path.c            # Path resolution, command parsing
├── Makefile
└── libft/            # Your libft folder
```

---

## 🧪 Testing

### Create Input File

```bash
echo -e "hello\nworld\nerror\n42" > infile
```

### Run Program

```bash
./pipex infile "grep o" "wc -l" outfile
```

### Compare with Shell

```bash
< infile grep o | wc -l > expected
diff outfile expected
```

---

## 📌 Compilation

Use the provided `Makefile`:

```bash
make      # Builds the project
make clean   # Removes object files
make fclean  # Removes all generated files
make re      # Rebuilds everything from scratch
```

---

## ⚠️ Error Handling

- Handles invalid commands and missing files gracefully
- Provides informative error messages using `perror()`
- No memory leaks (verified with `valgrind`)
- Failsafe against segmentation faults and double frees

---

## 👨‍💻 Author

Paul Hofer  
[github.com/HoferJPaul](https://github.com/HoferJPaul)

---

## 📜 License

This project is part of the 42 School curriculum and provided under its terms of use.
