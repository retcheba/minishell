/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:15:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/09 00:40:27 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_minishell(char *username)
{
	printf("\033[H\033[2J");
	printf("\033[1;96m-----------------------------------------");
	printf("\033[1;96m--------------------------\033[0m\n");
	printf("\033[91m███╗   ███╗██╗███╗   ██╗██╗");
	printf("███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\033[0m\n");
	printf("\033[1;96mMade by: subrandt & retcheba\033[0m\n");
	printf("\033[1;96m-----------------------------------------");
	printf("\033[1;96m--------------------------\033[0m\n");
	printf("\nWelcome %s\n", username);
}

static void	ft_exit(t_struct *mini)
{
	printf ("exit\n");
	free(mini->buff);
	ft_free_tab(mini->tab);
	ft_free_list(mini->lst1);
	ft_free_list(mini->env);
	ft_free_list(mini->export);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	mini;
	char		*username;

	(void)argc;
	(void)argv;
	username = getenv("USER");
	ft_init_minishell(username);
	ft_init_env(&mini, envp);
	ft_init_export(&mini, envp);
	while (1 == 1)
	{
		mini.buff = readline("\033[1;91mminishell\033[0m  ");
		add_history(mini.buff);
		if (mini.buff[0] != 0)
		{
			parsing(&mini);
			ft_tag_word(&mini);
			what_to_execute(&mini, envp);
			if (mini.lst1->tag == EXIT)
				ft_exit(&mini);
			ft_free_tab(mini.tab);
			ft_free_list(mini.lst1);
		}
	}
	return (0);
}
