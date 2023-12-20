/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:35:09 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:26:20 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/** @brief Wait for all child processes to finish
 * @param cmd_tab cmd_tab table used to iterate through the child processes.
 * @param env contains the last status result if wait failed */
int	ft_wait4child(t_main *cmd_tab, t_env *env)
{
	int	i;
	int	result;

	i = 0;
	while (cmd_tab[i].cmd)
	{
		wait(&result);
		i++;
	}
	if (cmd_tab[i - 1].pid == 0)
		return (env->status);
	ft_check4tmp(cmd_tab);
	return (WEXITSTATUS(result));
}

char	*ft_pathjoin(char *p1, char *p2)
{
	char	*tmp2;
	char	*tmp1;

	if (!p2 || !p1)
		return (NULL);
	if (!str_ncmp(p1, "/", 1))
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2));
		else
		{
			tmp1 = ft_strjoin(p1, "/");
			tmp2 = ft_strjoin(tmp1, p2);
			free(tmp1);
			return (tmp2);
		}
	}
	else
	{
		if (p2[0] == '/')
			return (ft_strjoin(p1, p2 + 1));
		else
			return (ft_strjoin(p1, p2));
	}
}

int	ft_check4permision(struct stat file)
{
	if ((file.st_mode > 0) && (S_IEXEC & file.st_mode) && S_ISREG(file.st_mode))
	{
		if (file.st_mode & S_IXUSR)
			return (1);
		else
			putstr_fd("File not able to be executed", 2);
	}
	else
		putstr_fd("File does not exist", 2);
	return (0);
}

int	ft_binary_path(t_main cmdtb, char *expath, char **path, t_env *env)
{
	struct stat	file;
	int			i;

	i = 0;
	while (path && path[i])
	{
		expath = ft_pathjoin(path[i], cmdtb.cmd);
		if (lstat(expath, &file) != -1)
		{
			clear_arr(path);
			if (ft_check4permision(file))
				return (ft_exe_path(expath, env, cmdtb));
		}
		else
			free(expath);
		i++;
	}
	putstr_fd("minishell: command not found: ", 2);
	putendl_fd(cmdtb.cmd, 2);
	return (127);
}

int	ft_exe_cmd(t_main cmd_tab, t_env *env)
{
	int		status;
	char	*exe_path;
	char	*tmp;
	char	**path;

	ft_str2lowercase(cmd_tab.cmd);
	if (!str_ncmp(cmd_tab.cmd, "echo", 4) && 4 == str_len(cmd_tab.cmd))
		return (echo_func(cmd_tab));
	else if (!str_ncmp(cmd_tab.cmd, "pwd", 3) && str_len(cmd_tab.cmd) == 3)
		return (pwd_func(env));
	else if (!str_ncmp(cmd_tab.cmd, "env", 3) && str_len(cmd_tab.cmd) == 3)
		return (env_func(env));
	exe_path = ft_check4script(cmd_tab.cmd, env);
	if (exe_path)
		return (ft_exe_path(exe_path, env, cmd_tab));
	tmp = ft_find_env_val("PATH", env->env_var);
	if (!tmp)
		return (127);
	path = ft_split(tmp, ':');
	free(tmp);
	status = ft_binary_path(cmd_tab, exe_path, path, env);
	return (status);
}
