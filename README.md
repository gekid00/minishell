# Minishell

A minimal UNIX shell implementation written in C, developed as part of the 42 school curriculum.
It replicates core Bash behavior including command execution, piping, redirections, and
environment variable management.

## Technologies

- C (compiled with `clang`)
- GNU Readline library
- Makefile build system
- Custom libft library

## Build

```bash
make        # compile the project
make clean  # remove object files
make fclean # remove object files and binary
make re     # full recompile
```

**Dependencies:** `libreadline-dev` must be installed on your system.

## Usage

```bash
./minishell
```

Once launched, the shell displays an interactive prompt and supports the following features:

```bash
ls -la                        # execute external commands
echo "hello world"            # builtin: echo (with -n option)
cd /tmp                       # builtin: cd
pwd                           # builtin: pwd
export VAR=value              # builtin: export
unset VAR                     # builtin: unset
env                           # builtin: env
exit                          # builtin: exit

cat file.txt | grep pattern   # pipes
ls > output.txt               # output redirection
cat < input.txt               # input redirection
echo "text" >> log.txt        # append redirection
cat << EOF                    # heredoc
```

## Key Concepts

- **Lexer:** Tokenizes user input into words, operators, and redirections while handling single and double quotes.
- **Parser:** Builds an abstract syntax tree (AST) from the token list, supporting pipes and redirections.
- **Executor:** Walks the AST to execute commands, managing `fork`, `execve`, pipes, and file descriptor redirections.
- **Expander:** Handles `$VAR` expansion and `$?` exit status substitution within double quotes.
- **Signals:** Custom handling of `SIGINT` and `SIGQUIT` to match Bash interactive behavior.
