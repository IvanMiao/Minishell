#include "src/src.h"

void	print_token(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		printf("Token[%d] : [%s] (type %d, value %d)\n",
			i, token->str, token->type, token->value);
		token = token->next;
		i++;
	}
}

int	test_builtin(char *s, t_env *env, t_token *token)
{
	int	flag;

	flag = -1;
	if (!ft_strncmp(s, "cd ", 3))
		flag = ft_cd(s + 3);
	if (!ft_strncmp(s, "pwd", 3))
		flag = ft_pwd();
	if (!ft_strncmp(s, "env", 3))
		flag = ft_env(env);
	if (!ft_strncmp(s, "export ", 7))
		flag = ft_export(env, s + 7);
	if (!ft_strncmp(s, "unset ", 6))
		flag = ft_unset(env, s + 6);
	if (!ft_strncmp(s, "echo", 4))
		flag = ft_echo(token);
	if (!ft_strncmp(s, "exit", 4))
		flag = ft_exit(token);
	return (flag);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_token	*token;
	char	*s;
	int		exit_code;

	(void)ac;
	(void)av;
	exit_code = 0;
	controls(); // init sigals
	env = set_env(envp); // init env
	while (1)
	{
		s = readline("minishell$ ");
		ctrl_d(s, env);

		token = init_tokens(s);
		if (!token || empty_line(s))
			continue ;
		if (token)
			print_token(token);
		if (check_all_commands(token)) // check tokens
		{
			token_lstclear(&token);
			continue ;
		}
		if (token->type == DOLLAR) // try: type $PWD, $PATH, ...
			printf("token str: %s, the dollar variable is: %s\n", token->str, explain_dollar(env, token));
		if (!strncmp(s, "getenv ", 7))// try: type getenv PWD, ...
			printf(GREEN"get env_var!\nname: %s\nword: %s\n"ENDCOLOR, s+7, ft_get_env(env, s+7));
		exit_code = pipex(token, env);
		printf("------------------------\nexit_code: %d\n", exit_code);
		token_lstclear(&token);
		free(s);
	}
	env_free(env);
	return (0);
}
