/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:37:35 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:09:21 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_func(t_env *env, t_main ptr)
{
	int	res;

	if (ptr.args[0] == NULL)
	{
		clear_env(env);
		exit(0);
	}
	if (ptr.args[0] && ptr.args[1] && !is_num(ptr.args[1]))
	{
		putstr_fd("Too many arguments\n", 2);
		exit (0);
	}
	if (ptr.args[0] && ptr.args[1] && is_num(ptr.args[1]))
	{
		putstr_fd("Too many arguments\n", 2);
		return (1);
	}
	else
	{
		clear_env(env);
		res = ft_atoi(ptr.args[0]);
		if (res < 0)
			exit(256 + res);
		exit(res);
	}
}
