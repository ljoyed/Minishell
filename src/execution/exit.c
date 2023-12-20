/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:37:54 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:27:39 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *s)
{
	write(2, s, str_len(s));
	exit(1);
}

/** @brief  Function to exit the program, ENV freeing is performed.
 * @param s String to be shown when displaying the eroor on terminal.
 * @param status Contains the value to exit the programm. */
void	ft_quitprgm(char *s, int status, t_env	*env)
{
	clear_arr(env->env_var);
	if (status == -1)
	{
		printf("ERROR, %s\n", s);
		exit(EXIT_FAILURE);
	}
	else if (status == 0)
		exit(EXIT_SUCCESS);
	else
	{
		printf("ERROR, %s\n", s);
		exit(status);
	}
}
