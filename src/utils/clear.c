/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:39:22 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/04 11:28:52 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	clear_arr(env->env_var);
}

void	clear_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

void	quit_func(t_env *env, char *msg, int fail)
{
	clear_env(env);
	if (fail == -1)
	{
		printf("%s %s\n", "ERROR : ", msg);
		exit(EXIT_FAILURE);
	}
	else if (!fail)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("%s %s\n", "ERROR : ", msg);
		exit(fail);
	}
}

int	valid_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '?' || c == '_' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_tolower(int c)
{
	if ((c >= 65) && (c <= 90))
		c += 32;
	return (c);
}
