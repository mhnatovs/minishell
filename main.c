#include "minishell.h"

int	g_status = 0;

// char	*check_quotes(char *line, char **envp)
// {
// 	int		i;
// 	t_quotes	status;

// 	status = NOT_IN_QUOTES;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'' && status == NOT_IN_QUOTES)
// 			status = IN_SINGLE_QUOTES;
// 		else if (line[i] == '\'' && status == IN_SINGLE_QUOTES)
// 			status = NOT_IN_QUOTES;
// 		else if (line[i] == '"' && status == NOT_IN_QUOTES)
// 			status = IN_DOUBLE_QUOTES;
// 		else if (line[i] == '"' && status == IN_DOUBLE_QUOTES)
// 			status = NOT_IN_QUOTES;
// 		// else if (line[i] == '$' && status != IN_SINGLE_QUOTES)
		
// 		i++;
// 	}
// }

// char **ft_split_args(char *line)
// {
// 	char	**res;
// 	int		i;

// 	i = 0;
	
// }

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
		args = lexer_split(line);
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
		free_split(expanded);
		free_split(args);
		free(line);
		// printf("DEBUG g_status = %d\n", g_status);
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
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
open
close
wait
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
getcwd
chdir
stat
lstat
fstat
unlink
dup
dup2
pipe,
opendir
readdir
closedir
strerror
isatty
ttyname
ttyslot
ioctl
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs
*/
