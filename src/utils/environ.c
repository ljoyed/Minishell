/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:08 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:14:29 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cp_env_var(t_env *env, char **env_var)
{
	int	size;
	int	i;

	size = 0;
	while (env_var[size])
		size++;
	env->env_var = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (env_var[i])
	{
		env->env_var[i] = str_dup(env_var[i]);
		i++;
	}
	env->env_var[i] = 0;
}

char	*get_env_var(t_env *env, char *name)
{
	int			i;
	size_t		tmp;

	i = 0;
	while (env->env_var[i])
	{
		tmp = str_chrn(env->env_var[i], '=');
		if (str_ncmp(env->env_var[i], name, str_len(name)) == 0
			&& tmp == str_len(name))
		{
			return (str_dup(env->env_var[i] + tmp + 1));
		}
		i++;
	}
	return (0);
}

void	add_env_var(t_env *env, char *name, char *val)
{
	int		size;
	int		i;
	char	**res;
	char	*tmp;

	size = 0;
	while (env->env_var[size])
		size++;
	res = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (env->env_var[i])
	{
		res[i] = str_dup(env->env_var[i]);
		i++;
	}
	tmp = ft_strjoin(name, "=");
	res[i] = ft_strjoin(tmp, val);
	free(tmp);
	res[++i] = 0;
	clear_arr(env->env_var);
	env->env_var = res;
}

void	rem_env_var(t_env *env, char *name)
{
	int		size;
	int		i;
	int		j;
	char	**res;
	int		tmp;

	size = 0;
	while (env->env_var[size])
		size++;
	res = (char **)malloc(sizeof(char *) * (size + 1));
	i = -1;
	j = 0;
	while (env->env_var[++i])
	{
		tmp = str_chrn(env->env_var[i], '=');
		if (str_ncmp(env->env_var[i], name, str_len(name)) == 0
			&& (size_t)tmp == str_len(name))
			continue ;
		res[j] = str_dup(env->env_var[i]);
		j++;
	}
	res[j] = 0;
	clear_arr(env->env_var);
	env->env_var = res;
}
