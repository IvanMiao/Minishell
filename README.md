# Minishell

## Test

For test:
- `make test`
- `./test_minishell`

delete `test_minishell`:
- `make fclean`

## TODO

### New Features
1. `history`
2. executing commands with pipe(s)

### Fix
1. `$?` & exit.c 
2. handle single quote vs double quote correctly; ensure quote content is treated as a correct argument, like `echo "    a     b    "`, and `"  echo   "` will cause command not found
3. several redirections in a single command
4. builtin functions & system binaries in a single command
5. Error messages

ref:
[Shell Operation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Shell-Operation.html)
[Exit Status](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/html_node/Exit-Status.html)



### Test
1. (Write a bash script for testing?) 