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

### Fix
1. `<<eof cat | grep a`
2. **!!** exit.c cd.c export.c with directions (modify count_args()) `export > a hola=bonjour`
3. redirections in pipex(like, two pipes, three commands, but there's a redirection in second command)
4. heredoc with dollar expansion - need to test
5. multiple herdocs(?)

ref:
[Shell Operation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Shell-Operation.html), 
[Exit Status](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Exit-Status.html)
