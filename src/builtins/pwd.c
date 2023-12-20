/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:38:27 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:10:00 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_func(t_env *env)
{
	char	*str;

	str = get_env_var(env, "PWD");
	if (!str || str[0] == '\0')
	{
		putstr_fd("PWD variable is unset", 2);
		if (str[0] == '\0')
			free(str);
		return (2);
	}
	putstr_fd(str, 1);
	putstr_fd("\n", 1);
	free(str);
	return (0);
}
