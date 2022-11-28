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

int	g_status = 0;

	/*
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
	*/

static void	ft_init_minishell(t_struct *mini, char **envp)
{
	ft_init_env(mini, envp);
	ft_init_export(mini, envp);
	mini->envp = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

static int	is_empty_buff(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] != ' ' && buff[i] != '	')
			return (1);
		i++;
	}
	return (0);
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
		if (is_empty_buff(mini.buff))
		{
			mini.envp = ft_envp(&mini);
			if (parsing(&mini, mini.envp))
			{
				ft_tag_word(&mini);
				what_to_execute(&mini);
				if (mini.lst1->tag == EXIT && check_exit_args(&mini))
					ft_exit(&mini);
			}
			ft_free_tab(mini.tab);
			ft_free_list(mini.lst1);
		}
		free(mini.buff);
	}
	return (0);
}
