/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:41:13 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:25:05 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief  Returns the count until first char occurrence.
 * @param str String to examinate.
 * @param c Occurence to search for. */
size_t	str_len2char(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

/** @brief  Converts our cmd_tab table to an **arglist for execve.
 * @param cmd_tab Contains all the neede information.
 * @param env Just used for quitting the program, if something fails. */
char	**ft_cmd2arglist(t_main cmd_tab, t_env *env)
{
	char	**arglist;
	int		i;
	int		j;

	i = 0;
	while (cmd_tab.args[i])
		i++;
	arglist = (char **)malloc(sizeof(char *) * (i + 3));
	if (!arglist)
		quit_func(env, "Malloc in cmd2arglist failed", -1);
	arglist[0] = str_dup(cmd_tab.cmd);
	i = 0;
	if (cmd_tab.options)
		arglist[++i] = ft_strjoin("-", cmd_tab.options);
	if (cmd_tab.args)
	{
		j = 0;
		while (cmd_tab.args[j])
			arglist[++i] = str_dup(cmd_tab.args[j++]);
	}
	arglist[++i] = 0;
	return (arglist);
}

/** @brief Removes if (file) the temp created by the EOF operator.
 * @param tmpfile Name of the file.*/
void	ft_check4tmp(t_main *cmd_tab)
{
	int		i;
	char	*tmpfile;
	char	*itoa;

	i = 0;
	while (cmd_tab[i].cmd)
	{
		itoa = ft_itoa(i);
		tmpfile = ft_strjoin(".tmp", itoa);
		if (access(tmpfile, F_OK) != -1)
		{
			if (unlink(tmpfile) != 0)
				putstr_fd("tmp file has not been eliminated", 2);
		}
		free(tmpfile);
		free(itoa);
		i++;
	}
}

/** @brief Strings are offset to fill the freed index.
 * @param cmd_tab Contains all the neede information.
 * @param env Just used for quitting the program, if something fails. */
void	ft_rearrange(char **strarray, int size, int freed_idx)
{
	int	curr_index;
	int	next_index;

	curr_index = freed_idx;
	next_index = curr_index + 1;
	if (strarray[freed_idx] == NULL)
	{
		while (next_index < size)
		{
			if (strarray[next_index] != NULL)
			{
				strarray[curr_index] = strarray[next_index];
				strarray[next_index] = NULL;
				curr_index++;
			}
			next_index++;
		}
	}
	return ;
}

/** @brief  Function to find an environment variable.
 * @param var name of variable to search for.
 * @param env 2darray with all the env vars. */
size_t	ft_2darray_size(char **db_array)
{
	size_t	size;

	size = 0;
	while (db_array[size] != NULL)
		size++;
	return (size);
}
