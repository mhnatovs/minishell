/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:08:57 by mhnatovs          #+#    #+#             */
/*   Updated: 2025/12/22 17:08:59 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char **envp)
{
	int		i;

	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	if (!full)
		return (NULL);
	free(tmp);
	return (full);
}
static void free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while(arr[i])
		free(arr[i++]);
	free(arr);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	**directories;
	char	*cmd_path;
	int		i;

	i = 0;
	path = get_path(envp);
	if (!path)
		return (NULL);
	directories = ft_split(path, ':');
	if(!directories)
		return (NULL);
	while(directories[i])
	{
		cmd_path = join_path(directories[i], cmd);
		if (!cmd_path)
			return (free_split(directories), NULL);
		if(access(cmd_path, X_OK) == 0)
			return (free_split(directories), cmd_path);
		free(cmd_path);
		i++;
	}
	free_split(directories);
	return (NULL);
}
