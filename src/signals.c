/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:44:47 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/04 09:44:27 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal)
	{
		rl_replace_line("", 0);
		putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigquit_handler(int signal)
{
	if (signal)
	{
		exit(EXIT_FAILURE);
	}
}

void	signal_func(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
