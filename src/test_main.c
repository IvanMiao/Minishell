#include "src.h"

void	print_token(t_token *token)
{
	while (token)
	{
		printf("Token : [%s] (type %d, value %d)\n", token->str, token->type, token->value);
		token = token->next;
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
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_token	*token;
	char	*s;
	
	//char *str = "cat < input.txt | grep hello > output.txt";
	(void)ac;
	(void)av;
	controls();
	env = set_env(envp);
	while (1)
	{
		s = readline("minishell$ ");
		ctrl_d(s);

		printf ("Entree : %s\n", s);
		token = init_tokens(s);
		if (token)
			print_token(token);
		test_builtin(s, env);
		token_lstclear(&token);
		// need to fix: echo, exit
	}
	return (0);
}