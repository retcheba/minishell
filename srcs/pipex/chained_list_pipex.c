/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:03:40 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/19 23:07:37 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pid	*new_link_pipex(pid_t pid, int ok)
{
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	if (new)
	{
		new->pid = pid;
		new->ok = ok;
		new->next = NULL;
	}
	return (new);
}

t_pid	*add_link_bottom_pipex(t_pid *list, t_pid *new)
{
	t_pid	*begin;

	begin = list;
	while (list->next)
		list = list->next;
	list->next = new;
	return (begin);
}

t_pid	*add_link_top_pipex(t_pid *list, pid_t pid, int ok)
{
	t_pid	*tmp;

	tmp = malloc(sizeof(t_pid));
	if (tmp)
	{
		tmp->pid = pid;
		tmp->ok = ok;
		tmp->next = list;
	}
	return (tmp);
}

void	ft_free_list_pipex(t_pid *list)
{
	t_pid	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
}
