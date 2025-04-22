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

static void	print_cmd(t_token *token, t_env *env)
{
	t_token	*start;
	t_cmd	*cmd[1024];
	int		i;

	start = token;
	i = 0;
	while (token)
	{
		if (token->type == PIPE)
		{
			cmd[i] = set_cmd(start, env);
			start = token->next;
			i++;
		}
		token = token->next;
	}
	cmd[i] = set_cmd(start, env);
	for (int k = 0; k <= i; k++)
	{
		printf("------------------------------\n");
		printf(GREEN"cmd path is: %s\n"ENDCOLOR, cmd[k]->pathname);
		for (int j = 0; cmd[k]->argv[j]; j++)
			printf("argv[%d]: %s\n", j, cmd[k]->argv[j]);
		printf("infile is: %s\n", cmd[k]->infile);
		printf("outfile is: %s\n", cmd[k]->outfile);
		printf("delimiter is: %s\n", cmd[k]->delimiter);
		printf("append?: %s\n", cmd[k]->append? "true" : "false");
		printf("------------------------------\n");
	}
	for (int k = 0; k <= i; k++)
		free_cmd(cmd[k]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*history;
	t_env	*env;
	t_token	*token;
	t_shell	shell;

	if (argc != 1)
		return(ft_fprintf(2, "Usage: %s\n", argv[0]), 1);
	controls();
	env = set_env(envp);
	(&shell)->env = env;
	(&shell)->exit_code = 0;
	while (1)
	{
		history = readline("minishell$ ");
		if (!history)
			exit_history(1);
		ctrl_d(history, env);
		add_history(history);
		(&shell)->str = history;
		token = init_tokens(&shell);
		if (token)
			print_token(token);
		if (check_main(&token, history))
			continue ;
		print_cmd(token, env);
		(&shell)->exit_code = pipex(token, env);
		token_lstclear(&token);
		free(history);
		printf("----exit code----\n%d\n", (&shell)->exit_code);
	}
	env_free(env);
	return (0);
}
