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


### to test
1. builtin with directions `echo >a ok`, `>>a echo bonjour >b`, `>b echo >>a bonjour`
2. exit code of CTRL C: no cmd, with cmd, with heredoc, with pipes(first cmd), with pipes(last cmd)
3. exit code of exit(): after a error, `exit` without arguments

ref:
[Shell Operation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Shell-Operation.html), 
[Exit Status](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Exit-Status.html)
