/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:58:47 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/10 17:26:03 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//si export toto - ajout dans export
//si export toto= ou toto=12  ajout dans export et env

void	check_export_args(t_struct *mini, t_list *n)
{
	if (n == NULL)
		print_export(mini->export);//print si export tout seul
	else if (ft_strchr(n->content, '=') != NULL)
	{
		add_link_bottom(mini->export, new_link(n->content, 0));
		printf("content : %s\n", (char *)n->content);
	}
}
