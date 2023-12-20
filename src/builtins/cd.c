/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:04:06 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:08:45 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_func_helper(t_main *ptr, char *home)
{
	if (ptr->args[0] == NULL)
	{
		if (home == NULL)
		{
			putstr_fd("HOME variable is not set\n", 2);
			return (1);
		}
		if (chdir(home) != 0)
		{
			putstr_fd("HOME variable is not valid\n", 2);
			return (1);
		}
	}
	else
	{
		if (chdir(ptr->args[0]) != 0)
		{
			putstr_fd("cd: No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

int	cd_func(t_env *env, t_main ptr)
{
	char	*home;
	char	buffer[1024];
	int		res;

	home = get_env_var(env, "HOME");
	res = cd_func_helper(&ptr, home);
	rem_env_var(env, "PWD");
	add_env_var(env, "PWD", getcwd(buffer, 1024));
	return (res);
}
