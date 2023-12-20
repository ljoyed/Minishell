/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:23:56 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:22:55 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief  Creates a pipe for every existing cmd_tab.
 * @param cmd_tab String to be shown when displaying the eroor on terminal.
 * @param env Contains the value to exit the programm. */
void	ft_pipecmds(t_main *cmd_tab, t_env *env)
{
	int	i;

	i = 0;
	while (cmd_tab[i].cmd)
	{
		if (pipe(cmd_tab[i].fd) < 0)
			quit_func(env, "Pipes couldn't be generated", -1);
		i++;
	}
}

/** @brief  Function check for any builtin cmd_tab input
 * @param cmd_tab Current cmd_tab table is passed to be checked.
 * @param env Our env 2D array is passed */
int	ft_check4builtin(t_main cmd_tab, t_env *env)
{
	int	status;

	status = -1;
	ft_str2lowercase(cmd_tab.cmd);
	if (str_ncmp(cmd_tab.cmd, "cd", 3) == 0)
		return (cd_func(env, cmd_tab));
	else if (str_ncmp(cmd_tab.cmd, "unset", str_len(cmd_tab.cmd)) == 0)
		return (unset_func(env, cmd_tab));
	else if (str_ncmp(cmd_tab.cmd, "export", str_len(cmd_tab.cmd)) == 0)
		return (export_func(env, cmd_tab));
	else if (str_ncmp(cmd_tab.cmd, "exit", str_len(cmd_tab.cmd)) == 0)
		return (exit_func(env, cmd_tab));
	return (status);
}

/** @brief  Function to close all unused file descriptors.
 * @param cmd_tab Struct to cmd_tab.
 * @param i Index of cmd_tab struct. */
void	ft_close_fd(t_main *cmd_tab, int i)
{
	int	j;

	j = 0;
	while (cmd_tab[j].cmd)
	{
		if (i != j)
			close(cmd_tab[j].fd[1]);
		if (i -1 != j)
			close(cmd_tab[j].fd[0]);
		j++;
	}
}

/** @brief  Function to close all file descriptors.
 * @param cmd_tab Struct to cmd_tab. */
void	ft_close_fds_main(t_main *cmd_tab)
{
	int	j;

	j = 0;
	while (cmd_tab[j].cmd)
	{
		close(cmd_tab[j].fd[0]);
		close(cmd_tab[j].fd[1]);
		j++;
	}
}

/** @brief  Function to find an environment variable.
 * @param var name of variable to search for.
 * @param env 2darray with all the env vars. */
char	*ft_find_env_val(char *var, char **env)
{
	char	*value;
	size_t	var_len;
	int		i;

	i = 0;
	value = 0;
	while (env[i])
	{
		var_len = str_len2char(env[i], '=');
		if (!str_ncmp(env[i], var, str_len(var))
			&& var_len == str_len(var))
			value = str_dup(env[i] + var_len + 1);
		i++;
	}
	return (value);
}
