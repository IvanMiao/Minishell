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
2. handle single quote vs double quote correctly; ensure quote content is treated as a correct argument, like `echo "    a     b    "`
3. several redirections in a single command
4. builtin functions & system binaries in a single command
5. Error messages

### Test
1. (Write a bash script for testing?) 