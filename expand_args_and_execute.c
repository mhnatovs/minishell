#include "minishell.h"

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

char	*get_env_value(char *arg)
{
	char	*str;

	str = getenv(arg);//sets pointer to evnironment variable's value
	if (!str)
		return (ft_strdup(""));
	return (ft_strdup(str));
}

char	*expanded_arg(char *arg)
{
	if (ft_strcmp(arg, "$?") == 0)
		return (ft_itoa(g_status));
	if (arg[0] == '$' && arg[1])
		return (get_env_value(arg + 1));
	return (ft_strdup(arg));
}

char	**expanded_args(char **args)
{
	int		i;
	char	**ptrs;
	int		size;

	i = 0;
	size = count_args(args);
	ptrs = malloc(sizeof(char *) * (size + 1));
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
