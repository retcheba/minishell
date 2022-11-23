/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:07:55 by retcheba          #+#    #+#             */
/*   Updated: 2022/09/28 01:59:45 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	paths = NULL;
}

static char	*ft_strstr_from_begin(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (to_find[i] != str[i])
			return (NULL);
		i++;
	}
	return (str);
}

static void	ft_add_backslash(char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
}

static char	**get_all_paths(char **envp)
{
	char	**paths;
	char	*envp_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		envp_path = ft_strstr_from_begin(envp[i], "PATH=");
		if (envp_path)
		{
			envp_path = ft_substr(envp_path, 5, (ft_strlen(envp[i]) - 5));
			break ;
		}
		i++;
	}
	paths = ft_split(envp_path, ':');
	free(envp_path);
	ft_add_backslash(paths);
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	paths = get_all_paths(envp);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_paths(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free_paths(paths);
	return (NULL);
}
