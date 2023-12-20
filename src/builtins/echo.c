/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:36:24 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:09:07 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_func_helper(t_main *ptr, int *line)
{
	int	i;

	i = 0;
	if (ptr->options)
	{
		while (ptr->options[i])
		{
			if (ptr->options[i++] != 'n')
			{
				putstr_fd("Unregognized flag\n", 2);
				return (-1);
			}
		}
		if (ptr->options[0] == 'n')
			*line = 0;
	}
	return (0);
}

int	echo_func(t_main ptr)
{
	int	line;
	int	res;
	int	i;

	i = 0;
	line = 1;
	res = echo_func_helper(&ptr, &line);
	if (ptr.args && ptr.args[0] != NULL)
	{
		putstr_fd(ptr.args[i++], 1);
		while (ptr.args[i])
		{
			putstr_fd(" ", 1);
			putstr_fd(ptr.args[i++], 1);
		}
	}
	if (line)
		putstr_fd("\n", 1);
	return (res);
}
