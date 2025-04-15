#include "src/src.h"

int	empty_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i == ft_strlen(str));
}

int	check_main(t_token **token, char *history)
{
	if (!*token || empty_line(history))
	{
		if (*token)
			token_lstclear(token);
		free(history);
		return (1);
	}
	if (check_syntax(*token))
	{
		token_lstclear(token);
		free(history);
		return (1);
	}
	return (0);
}

int	exit_history(int value)
{
	rl_clear_history();
	return (value);
}

static void	print_token(t_token *token)
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
	printf("---------------\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*history;
	t_env	*env;
	t_token	*token;
	int		exit_code;

	if (argc != 1)
		return(ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	controls();
	env = set_env(envp);
	while (1)
	{
		history = readline("minishell$ ");
		if (!history)
			exit_history(1);
		ctrl_d(history, env);
		add_history(history);
		token = init_tokens(history, env);
		if (token)
			print_token(token);
		if (check_main(&token, history))
			continue ;
		exit_code = pipex(token, env);
		token_lstclear(&token);
		free(history);
		printf("----exit code----\n%d\n", exit_code);
	}
	env_free(env);
	return (0);
}

/*
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

		token = init_tokens(s, env);
		if (check_main(&token, s))
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
*/