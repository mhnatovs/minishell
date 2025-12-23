/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:15:14 by mhnatovs          #+#    #+#             */
/*   Updated: 2025/12/23 20:00:40 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	execute(char **args, char **envp)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_cmd_path(args[0], envp);
	if (!cmd_path)
	{
		printf("%s: command not found\n", args[0]);
		g_status = 127;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, envp);
		perror("execve");
		exit(126);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
}
int	count_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
char	*expanded_arg(char *arg)
{
	if (ft_strcmp(arg, "$?") == 0)
		return ft_itoa(g_status);
	return (ft_strdup(arg));
}

char	**expanded_args(char **args)
{
	int		i;
	char	**ptrs;
	int		size;

	i = 0;
	size = count_args(args);
	ptrs = malloc(sizeof(char *) * size + 1);
	if (!ptrs)
		return (NULL);
	while (args[i])
	{
		ptrs[i] = expanded_arg(args[i]);
		i++;
	}
	ptrs[i] = NULL;
	return (ptrs);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	**expanded;

	(void) argv;
	if (argc != 1)
		return (1);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		args = ft_split(line, ' ');
		if (!args || !args[0])
		{
			free_split(args);
			free(line);
			continue ;
		}
		expanded = expanded_args(args);
		if (!expanded || !expanded[0])
		{
			free_split(expanded);
			free_split(args);
			free(line);
			continue ;
		}
		execute(expanded, envp);
		free_split(args);
		free(line);
		printf("DEBUG g_status = %d\n", g_status);
	}
	return (0);
}

// void debug_path(char **envp)
// {
//     char *path;
//     char **dirs;
//     int i;

//     path = get_path(envp);
//     dirs = ft_split(path, ':');
//     i = 0;
//     while (dirs[i])
//     {
//         printf("DIR: %s\n", dirs[i]);
//         i++;
//     }
// }
// int main(int argc, char **argv, char **envp)
// {
// 	char *path;

// 	(void)argc;
// 	// (void)argv;

// 	path = get_path(envp);
// 	// if (path)
// 	// 	printf("PATH = %s\n", path);
// 	// else
// 	// 	printf("PATH not found\n");
// 	// debug_path(envp);
// 	char *cmd_path = find_cmd_path(argv[1], envp);
// 		printf("%s\n", cmd_path);
// 	return 0;
// }
/*
readline
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
printf
malloc
free
write
access
open, read
close
fork
wait
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
exit
getcwd
chdir
stat
lstat
fstat
unlink
execve
dup
dup2
pipe,
opendir
readdir
closedir
strerror
perror
isatty
ttyname
ttyslot
ioctl
getenv
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
*/
