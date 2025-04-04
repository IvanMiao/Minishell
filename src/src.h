/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:10:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/04 13:09:33 by cgerner          ###   ########.fr       */
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
# include <fcntl.h>
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

// parsing
int		open_file(char *file, int value);
void	x_cmd(char *cmd, char **envp);
void	error_here_doc(char *str);
void	here_doc(char *limiter);
void	errors(int value);
void	ft_free(char **s);
char	*find_full_path(char *cmd, char **paths);
char	*find_path(char *cmd, char **envp);
void	ft_exec(char *cmd_shell, char **envp);
int		check_command(t_token *token);
int		check_command_in(t_token *token);
int		check_command_out(t_token *token);
int		check_command_delimiter(t_token *token);
int		check_command_redirection(t_token *token);
int		check_quotes(char *str);
char	*remove_quotes(char *str);
t_token	*token_lst(char *str, t_tokentype type, int value);
t_token	*token_lstlast(t_token *lst);
void	token_lstadd_back(t_token **lst, t_token *new);
void	token_lstclear(t_token **lst);

#endif