# Simple Shell Program

This is a simple shell program written in C. It provides a basic command-line interface for executing commands, built-in shell commands, environment variable substitution, and background execution.

## Features

- Allows execution of external commands
- Supports built-in shell commands like `cd`, `echo`, and `export`
- Performs environment variable substitution
- Supports background execution using `&`
- Logs child process termination events to a file (`child_state.log`)

## Usage

1. **Compilation**: Compile the program using a C compiler (e.g., `gcc`):

2. **Execution**: Run the compiled executable:

3. **Command Syntax**:
- External commands: Simply type the command name followed by any arguments.
- Built-in shell commands:
  - `cd`: Change directory. Usage: `cd [directory]` or `cd ~` for the home directory.
  - `echo`: Print text. Usage: `echo [text]`.
  - `export`: Set environment variables. Usage: `export [variable]=[value]`.

4. **Background Execution**: Append `&` to the command to run it in the background.

5. **Exit**: Type `exit` to exit the shell.

## License

This project is licensed under the [MIT License](LICENSE).
