/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:15:14 by mhnatovs          #+#    #+#             */
/*   Updated: 2025/12/22 17:05:20 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	(void) argv;
// 	if (argc != 1)
// 		return (1);
// 		// if (ft_strcmp(argv[1], "./minishell") == 0)
// 		// {
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
		
// 		if (*line)
// 			add_history(line);
// 		free(line);
// 	}
// 	// }
// 	return (0);
// }

void debug_path(char **envp)
{
    char *path;
    char **dirs;
    int i;

    path = get_path(envp);
    dirs = ft_split(path, ':');
    i = 0;
    while (dirs[i])
    {
        printf("DIR: %s\n", dirs[i]);
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
	char *path;

	(void)argc;
	// (void)argv;

	path = get_path(envp);
	if (path)
		printf("PATH = %s\n", path);
	else
		printf("PATH not found\n");
	debug_path(envp);
	char *cmd = find_cmd_path(argv[1], envp);

		printf("%s", cmd);

		
	return 0;
}

/*

PATH=/home/mhnatovs/goinfre/homebrew/bin:
/home/mhnatovs/bin:/home/mhnatovs/bin:
/usr/local/sbin:/usr/local/bin:/usr/sbin:
/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

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
