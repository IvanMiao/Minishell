#include "src.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*s;
	char	cwd[1024];

	(void)env;
	(void)ac;
	(void)av;
	controls();
	env = set_env(envp);
	while (1)
	{
		s = readline("minishell$ ");
		ctrl_d(s);
		if (!ft_strncmp(s, "cd ", 3))
			ft_cd(s + 3);
		getcwd(cwd, sizeof(cwd));
		printf("path now: %s\n", cwd);
		if (!ft_strncmp(s, "env", 3))
			ft_env(env);
		if (!ft_strncmp(s, "export ", 7))
			ft_export(env, s + 7);
		if (!ft_strncmp(s, "unset ", 6))
			ft_unset(env, s + 6);
	}
	return (0);
}