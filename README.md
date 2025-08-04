# 🐚 Minishell – A Tiny Bash-like Shell in C

`minishell` is a **Unix shell** implementation written in C as part of the 42 school curriculum.  
It was developed in collaboration with [Vale-Flo](https://github.com/Vale-Flo) and follows most of the behavior of the Bash shell, including built-in commands, piping, redirections, and environment variable handling.

---

## 🛠️ Skills & Concepts

- Process management (`fork`, `execve`, `wait`)
- Signal handling (`SIGINT`, `SIGQUIT`)
- File descriptors and redirections
- Pipes (`|`)
- Parsing and tokenization
- Built-in command execution
- Memory management and garbage collection
- Environment variables and shell levels

---

## ⚙️ How to Use

### 1. Clone and Build

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make
```
### 2. Run the Shell
```
./minishell
```
You’ll see a custom shell prompt:
```
minishell$ echo Hello World
Hello World
```

## 💡 Features

  ✅ Prompt and command line input

  ✅ Built-in commands: cd, echo, pwd, export, unset, env, exit

  ✅ Environment variable expansion ($VAR)

  ✅ Redirections: >, >>, <, << (heredoc)

  ✅ Piping: cmd1 | cmd2 | cmd3

  ✅ Signal handling: Ctrl+C, Ctrl+D, Ctrl+\

  ✅ Exit codes and status tracking

  ✅ Handling quotes (' and ")

  ✅ Minimal memory leaks (tested with valgrind)
