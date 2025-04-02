/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:10:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/02 17:15:25 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H

# define FAIL -1

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

// ----a enum for tokenization-----

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
	INFILE,
	OUTFILE,
	QUOTE,
	DOLLAR,
	END
}		t_tokentype;

typedef struct s_token
{
	t_tokentype		type;
	char			*str;
	int				value;
	struct s_token	*next;
}		t_token;

// ----end token struct----

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
void	env_free(t_env *env);

// builtins
int		ft_pwd(void);
void	ft_echo(char *command);
int		ft_cd(char *path);
int		ft_exit(int argc, char **argv);
int		ft_env(t_env *env);
int		ft_export(t_env *env, char *argument);
int		ft_unset(t_env *env, char *argument);

// signals
void	controls(void);
void	ctrl_d(char *s, t_env *env);
void	ctrl_c(int code);

// parsing
int		check_quotes(char *str);
char	*remove_quotes(char *str);
t_token	*token_lst(char *str, t_tokentype type, int value);
t_token	*token_lstlast(t_token *lst);
void	token_lstadd_back(t_token **lst, t_token *new);
void	token_lstclear(t_token **lst);
t_token	*init_tokens(char *str);

#endif