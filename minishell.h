/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:15:25 by mhnatovs          #+#    #+#             */
/*   Updated: 2025/12/25 19:00:52 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//Exit status of the most-recently-executed command
// int	g_status;

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }		t_list;

// typedef struct s_prompt
// {
// 	t_list	*cmds;//Linked list containing a t_mini node with all commands separated by pipes
// 	char	**envp;//Up-to-date array containing keys and values for the shell environment
// 	pid_t	pid;//Process ID of the minishell instance
// }		t_prompt;

// typedef struct s_mini
// {
// 	char	**full_cmd;//Equivalent of the typical argv, containing the command name and its parameters when needed
// 	char	*full_path;//If not a builtin, first available path for the executable denoted by argv[0] from the PATH variable
// 	int	infile;//Which file descriptor to read from when running a command (defaults to stdin)
// 	int	outfile;//Which file descriptor to write to when running a command (defaults to stdout)
// }		t_mini;
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