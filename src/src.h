/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:10:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/03/31 17:24:21 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H

# include "utils/utils.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define FAIL -1

// ----a simple enum for tokenization-----

typedef enum e_tokentype
{
	CMD,
	OPTION,
	WORD,
	PIPE,
	R_IN,
	R_OUT,
	R_DELIMITER,
	R_REDIRECTION,
	QUOTE,
	DOLLAR,
	END
}		t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*str;
	char		*value;
}		t_token;

// ----end example----

typedef struct s_env
{
	char			*content;
	char			*name;
	char			*word;
	struct s_env	*next;
}		t_env;

// env
t_env	*env_lstnew(char *content);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstdelone(t_env **lst, t_env *target);
t_env	*set_env(char **envp);

// builtins
int		ft_pwd(void);
void	ft_echo(int argc, char **argv);
int		ft_cd(char *path);
int		ft_exit(int argc, char **argv);
int		ft_env(t_env *env);
int		ft_export(t_env *env, char *argument);
int		ft_unset(t_env *env, char *argument);

// signals
void	controls(void);
void	ctrl_d(char *s);
void	ctrl_c(int code);

#endif