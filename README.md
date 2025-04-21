# Minishell

## Git

Pour recuperer les dernieres versions du projet :
- `git pull`
- `git merge *fichier d'origine*`

## Test

For test:
- `make test`
- `./test_minishell`

test with valgrind:
- `make val`

delete `test_minishell` and `readline.supp`:
- `make fclean`

## TODO

### New Features


### Fix
1. `$?`(in ~~tokenization~~ and in exec)
2. **!!** exit.c cd.c export.c with directions (modify count_args()) `export > a hola=bonjour`
3. builtin functions & system binaries in a single command
4. Error messages: 1.cmd, no such file or directory 2. open error, permisson 3. ...
5. redirections in pipex(like, two pipes, three commands, but there's a redirection in second command)
6. heredoc with dollar expansion
7. multiple herdocs(?)

ref:
[Shell Operation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Shell-Operation.html), 
[Exit Status](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Exit-Status.html)


### Test
1. (Write a bash script for testing?) 