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
1. redirections in pipex(like, two pipes, three commands, but there's a redirection in second command)
2. ctrl c in heredoc
3. norm

### to test
1. multiple heredoc, heredoc with dollar expansion
2. `unset` with invalid vars
3. builtin with directions `echo >a ok`, `>>a echo bonjour >b`, `>b echo >>a bonjour`

ref:
[Shell Operation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Shell-Operation.html), 
[Exit Status](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Exit-Status.html)
