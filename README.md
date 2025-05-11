# Minishell

## what can minishell do?
- execute commands : `/bin/ls`, `ls`, `ls -la`, ...
- pipes: `ls -la | grep something | cat`, ...
- 4 redirections: `<`, `>`, `<<`, `>>`
- multiple redirections: `<a <b <c cat >d >e >f >>g`, `<<a <<b <<c cat`, ...
- redirections and pipes
- dollar expansion: `$USER`, `$PATH`, ...
- single quotes and double quotes: `echo '$USER'`, `echo "$USER"`, `echo "'$USER'"`, `echo '"$USER"'`
- dollar expansion in heredoc: `<<eof` will do the expansion, while `<<'eof'` do not
- exit code: `$?`
- signals: `CTRL C`, `CTRL D`, `CTRL \` in prompt, in commands, in pipes, in heredoc...
- check syntax error

## built-in functions
- echo && echo -n
- cd
- pwd
- exit
- env
- export
- unset

## Test

For test(show all tokens and commands):
- `make test`
- `./test_minishell`

test with valgrind:
- `make val`

ref:
[Shell Operation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Shell-Operation.html), 
[Exit Status](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Exit-Status.html)
