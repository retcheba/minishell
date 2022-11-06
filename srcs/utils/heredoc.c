/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:16:56 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 05:15:32 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(char *stop)
{
	int		fd_heredoc[2];
	char	*buff;

	buff = NULL;
	if (pipe(fd_heredoc) != -1)
	{
		while (1 == 1)
		{
			buff = readline(">");
			if (ft_strstr(buff, stop))
			{
				free(buff);
				close (fd_heredoc[1]);
				return (fd_heredoc[0]);
			}
			ft_putendl_fd(buff, fd_heredoc[1]);
		}
	}
	perror("Error");
	return (-1);
}
