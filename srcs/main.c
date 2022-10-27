/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:15:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/25 16:38:50 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_struct	mini;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1 == 1)
	{
		mini.buff = NULL;
		mini.buff = readline("minishell> ");
		add_history(mini.buff);
		if (mini.buff[0] != 0)
		{
			parsing(&mini);
			ft_tag_word(&mini);
			what_to_execute(&mini, envp);
			if (mini.lst1->tag == EXIT)
			{
				printf ("exit\n");
				free(mini.buff);
				ft_free_tab(mini.tab);
				ft_free_list(mini.lst1);
				exit(0);
			}
			ft_free_tab(mini.tab);
			ft_free_list(mini.lst1);
		}
	}
	return (0);
}
