/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:10:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 15:04:46 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H

# define FAIL	-1

# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define BLUE		"\e[34m"
# define ENDCOLOR	"\e[0m"

# include "utils/utils.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>

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
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

// ----end token struct----

typedef struct s_env
{
	char			*content;
	char			*name;
	char			*word;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char	*pathname;
	char	**argv;
	char	**envp;
	char	*infile;
	char	*outfile;
	char	*delimiter;
	bool	append;
}		t_cmd;

typedef struct	s_shell
{
	char	*str;
	t_token	*token;
	t_env	*env;
	t_cmd	*cmd;
	int		exit_code;
}		t_shell;

// env
t_env	*env_lstnew(char *content);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_lstdelone(t_env **lst, t_env *target);
t_env	*set_env(char **envp);
char	*ft_get_env(t_env *env, char *name);
void	env_free(t_env *env);

// builtins
int		ft_pwd(char **argv);
int		ft_echo(t_token *token);
int		ft_cd(t_token *token, t_env *env);
int		ft_exit(t_token *token);
int		ft_env(t_env *env);
int		ft_export(t_env *env, t_token *token);
int		ft_unset(t_env *env, char *argument);

int		count_args(t_token *token);

// signals
void	controls(void);
void	ctrl_d(char *s, t_env *env);
void	ctrl_c(int code);

// parsing
t_token	*token_lst(char *str, t_tokentype type, int value);
t_token	*token_lstlast(t_token *lst);
void	token_lstadd_back(t_token **lst, t_token *new);
void	token_lstclear(t_token **lst);
t_token	*init_tokens(t_shell *shell);

int		check_quotes(char *str);
int		update_state(int *state, char *str, int *i);
char	*update_clean_word(char *clean_word, char *str, int *i);
char	*expand_dollar(t_shell *shell, int *i, char *clean_word, int *state);

int		check_syntax(t_token *token);

// exec
int		is_directory(t_cmd *cmd);
char	**get_real_cmd(t_token *token, t_env *env);
char	**get_env(t_env *env);
char	*get_pathname(t_env *env, char *first_cmd);
char	*get_infile(t_token *token);
char	*get_outfile(t_token *token);
char	*get_delimiter(t_token *token);
bool	check_append(t_token *token);
void	free_cmd(t_cmd *cmd);

int		exec_builtin(t_cmd *cmd, t_env *env, t_token *token);
int		exec_simple_cmd(t_token *token, t_env *env, int *prev_pipe);
int		ft_exec(t_token *token, t_env *env);

int		pipex(t_token *token, t_env *env);
void	handle_here_doc(t_token *token, t_env *env, t_cmd *cmd);

void	print_last_status(t_token *token, int value);
int		open_file(char *file, int value);
void	errors(int value);
void	error_here_doc(char *str);

void	free_all(t_env *env, t_token *token, t_cmd *cmd);

#endif