# Minishell Readme

# Minishell

---

Minishell is a shell implementation written in C as part of the 42Cursus curriculum. It provides a basic command-line interface where users can execute commands and interact with the operating system.

---

## Index

## Features

---

- Command execution: Minishell allows users to execute various commands, including built-in commands and external programs.
- Input/Output redirection: Users can redirect input and output streams using the `<` and `>` operators.
- Pipes: Minishell supports command piping, allowing users to chain multiple commands together.
- Environment variables: Users can set and manipulate environment variables using the `export` command.
- Signal handling: Minishell handles signals such as Ctrl+C and Ctrl+D to provide a smooth user experience.

## Getting Started

---

To get started with Minishell, follow these steps:

1. Clone the repository: `git clone git@github.com:VolmerES/Minishell.git`
2. Navigate to the project directory: `cd minishell`
3. Build the project: `make`
4. Run Minishell: `./minishell`

## Usage

---

Once Minishell is running, you can use it just like any other shell. Here are some examples of commands you can try:

- Execute a command: `ls -l`
- Redirect input: `cat < input.txt`
- Redirect output: `ls > output.txt`
- Pipe commands: `ls -l | grep "file"`
- Set environment variable: `export MY_VAR=Hello`
- Access environment variable: `echo $MY_VAR`

For more information on how to use Minishell, refer to the project documentation or the source code.

## About the code

---

![Untitled](Minishell%20Readme/Code.png)

## Contributing

---

Contributions to Minishell are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

## License

---

Minishell is open-source software licensed under the MIT license. See the [LICENSE](https://www.notion.so/LICENSE) file for more information.
