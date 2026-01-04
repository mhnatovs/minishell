#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"

extern int	g_status;

typedef enum	e_quotes
{
	NOT_IN_QUOTES,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES
}	t_quotes;

void	free_split(char **arr);
// int		has_slash(char *str);
char	*get_path(char **envp);
char	*find_cmd_path(char *cmd, char **envp);

void	execute(char **args, char **envp);
int		count_args(char **args);
char	*get_env_value(char *arg);
char	*expanded_arg(char *arg);
char	**expanded_args(char **args);

char	**lexer_split(char *str);
int		ft_isspace(int c);

#endif