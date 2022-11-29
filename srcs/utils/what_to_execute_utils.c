/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_to_execute_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:09:46 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/29 21:10:18 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_content(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '|' && str[i] != '<' && str[i] != '>')
			return (0);
		i++;
	}
	return (1);
}

int	is_tag(int tag)
{
	if (tag == PIPE || tag == REDIR_IN || tag == DREDIR_IN
		|| tag == REDIR_OUT || tag == DREDIR_OUT)
		return (1);
	return (0);
}
