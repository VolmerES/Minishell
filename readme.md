# Minishell

![42 Cursus](https://img.shields.io/badge/42-Cursus-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-blue?style=for-the-badge&logo=c)

## 🗣️ About

**Minishell** is a shell written in C as a team project of the 42 Madrid common core (grade: **100/100**). It provides a basic command-line interface where users can execute commands and interact with the operating system, mimicking the behavior of bash.

## ✨ Features

- **Command Execution**: Runs external programs from `PATH` and the built-ins `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit`.
- **Redirection**: Handle input (`<`, `<<`) and output (`>`, `>>`) redirections.
- **Pipes**: Chain multiple commands using pipes (`|`).
- **Environment Variables**: Manage environment variables with `export` and `unset`, and expand them with `$`.
- **Signal Handling**: `Ctrl+C`, `Ctrl+D` and `Ctrl+\` behave as they do in bash.
- **Command History**: Previous commands with the arrow keys, through readline.

## 🏗️ Architecture

The parsing logic is a critical component of Minishell. The following diagram illustrates how the command line input is processed:

![Parsing Diagram](Minishell%20Readme/Code.png)

## 🚀 Getting Started

### Prerequisites

- GCC or Clang
- Make
- Readline library

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/VolmerES/Minishell.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Minishell
   ```
3. Compile the project:
   ```bash
   make
   ```

## 🛠️ Usage

Run the shell:

```bash
./minishell
```

### Examples

Execute commands:

```bash
minishell$ ls -l
```

Redirection:

```bash
minishell$ grep "error" < log.txt > errors.txt
```

Pipes:

```bash
minishell$ ps aux | grep minishell
```

Environment Variables:

```bash
minishell$ export MY_VAR="Hello World"
minishell$ echo $MY_VAR
```

## Authors

- **Luis David Díaz** (`ldiaz-ra`) · [@davidiaz1251](https://github.com/davidiaz1251)
- **Juan Bautista Delorme** (`jdelorme`) · [@VolmerES](https://github.com/VolmerES) · [Portfolio](https://juandelorme-portfolio.volmer.es)
