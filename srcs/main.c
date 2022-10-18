/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:15:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/18 16:55:21 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*buff;
	char	**cmd;
	char	*cmd_path;
	pid_t	pid;

	(void)argc;
	(void)argv;
	cmd = malloc(sizeof(char *) * 2);
	cmd[1] = NULL;
	while (1 == 1)
	{
		buff = NULL;
		buff = readline("minishell> ");
		add_history(buff);
		if (ft_strncmp(buff, "exit", ft_strlen(buff)) == 0)
		{
			printf ("exit\n");
			exit(0);
		}
		if (ft_strncmp(buff, "ls", ft_strlen(buff)) == 0)
		{
		cmd[0] = buff;
		cmd_path = get_cmd_path(cmd[0], envp);
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
			execve(cmd_path, cmd, envp);
		waitpid(pid, NULL, 0);
		}
	}
	return (0);
}
