# minishell

A simplified Unix shell recreated as part of the 42 school curriculum. This project is designed to deepen understanding of processes, file descriptors, environment variables, parsing, and signal handling.

---

## 🛠️ Project Goals

Recreate a minimal version of `bash` that supports:

- Execution of binaries in `$PATH`
- Built-in commands
- Pipes and redirections
- Environment variable handling
- Signal management (e.g. `Ctrl+C`, `Ctrl+D`)
- Proper memory management

---

## ✅ Features Implemented

- [x] Prompt display (`minishell$`)
- [x] `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- [x] Execution of external programs
- [x] Input/output redirection (`<`, `>`, `>>`)
- [x] Pipes (`|`)
- [x] Environment variable expansion (`$VAR`)
- [x] Quote handling (`'`, `"`)
- [x] Error handling and exit codes
- [x] Signal handling (`SIGINT`, `SIGQUIT`, `EOF`)
- [x] Exit status tracking (`$?`)

---

## 🚫 Forbidden Functions

Only the following libc functions and system calls are allowed:

- `read`, `write`, `open`, `close`, `fork`, `wait`, `waitpid`, `signal`, `kill`
- `exit`, `malloc`, `free`, `getcwd`, `chdir`, `execve`, `dup`, `dup2`
- `pipe`, `opendir`, `readdir`, `closedir`, `stat`, `lstat`, `fstat`
- `perror`, `strerror`, `isatty`, `ttyname`, `ttyslot`
- `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`
- `tgetstr`, `tgoto`, `tputs`

---

## 📦 Build Instructions

```bash
git clone git@github.com:HannahLisaWild/minishell.git
cd minishell
make
