#include "src.h"

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

int	test_builtin(char *s, t_env *env)
{
	if (!ft_strncmp(s, "cd ", 3))
		ft_cd(s + 3);
	if (!ft_strncmp(s, "pwd", 3))
		ft_pwd();
	if (!ft_strncmp(s, "env", 3))
		ft_env(env);
	if (!ft_strncmp(s, "export ", 7))
		ft_export(env, s + 7);
	if (!ft_strncmp(s, "unset ", 6))
		ft_unset(env, s + 6);
	if (!ft_strncmp(s, "echo ", 5))
		ft_echo(s + 5);
	// need to fix: echo(guillemets), exit
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_token	*token;
	char	*s;

	(void)ac;
	(void)av;
	controls(); // init sigals
	env = set_env(envp); // init env
	while (1)
	{
		s = readline("minishell$ ");
		ctrl_d(s, env);

		token = init_tokens(s);
		if (token)
			print_token(token);
		if (token->type == DOLLAR)
			printf("token str: %s, the dollar variable is: %s\n", token->str, explain_dollar(env, token));
		if (!strncmp(s, "getenv ", 7))
			printf(GREEN"get env_var!\nname: %s\nword: %s\n"ENDCOLOR, s+7, ft_get_env(env, s+7));
		test_builtin(s, env);
		token_lstclear(&token);
	}
	env_free(env);
	return (0);
}
