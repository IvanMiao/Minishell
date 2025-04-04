#include "src.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*s;

	(void)ac;
	(void)av;
	controls();
	env = set_env(envp);
	while (1)
	{
		s = readline("minishell$ "); // "$path"  '$path'
		ctrl_d(s);
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
		// need to fix: echo, exit
	}
	return (0);
}