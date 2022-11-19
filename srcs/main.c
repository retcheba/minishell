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

static void	ft_init_minishell(t_struct *mini, char **envp)
{
	printf("\033[H\033[2J\033[1;96m-----------------------------------------");
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
	printf("\033[1;96m--------------------------\033[0m\n\n");
	ft_init_env(mini, envp);
	ft_init_export(mini, envp);
	mini->envp = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_free_the_free_list(t_struct *mini)
{
	t_list	*begin;

	begin = mini->free_list;
	while (mini->free_list)
	{
		free(mini->free_list->content);
		mini->free_list = mini->free_list->next;
	}
	mini->free_list = begin;
	ft_free_list(mini->free_list);
}

static void	ft_exit(t_struct *mini)
{
	printf ("exit\n");
	free(mini->buff);
	ft_free_tab(mini->tab);
	ft_free_list(mini->lst1);
	ft_free_the_free_list(mini);
	ft_free_list(mini->env);
	ft_free_list(mini->export);
	if (mini->envp != NULL)
		ft_free_tab(mini->envp);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	mini;

	(void)argc;
	(void)argv;
	ft_init_minishell(&mini, envp);
	while (1 == 1)
	{
		mini.buff = readline("\033[1;91mminishell\033[0m  ");
		add_history(mini.buff);
		if (mini.buff[0] != 0)
		{
			parsing(&mini);
			mini.envp = ft_envp(&mini);
			replace_env_equivalent(&mini, mini.envp);
			ft_tag_word(&mini);
			what_to_execute(&mini, mini.envp);
			if (mini.lst1->tag == EXIT)
				ft_exit(&mini);
			ft_free_tab(mini.tab);
			ft_free_list(mini.lst1);
		}
	}
	return (0);
}
