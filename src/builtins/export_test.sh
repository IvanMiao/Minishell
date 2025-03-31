gcc -Wall -Werror -Wextra ft_export.c ft_env.c env_list.c libft.a -o exporttest
./exporttest var=foo
./exporttest __var=foo
./exporttest 2var=foo
./exporttest ,.var=foo
./exporttest var.a=foo
./exporttest var-=foo
./exporttest var}a=foo
./exporttest ""