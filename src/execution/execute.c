/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:13:54 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:27:05 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute(t_main *cmd_tab, t_env *env)
{
	int	j;
	int	status;

	j = 0;
	ft_pipecmds(cmd_tab, env);
	while (cmd_tab[j].cmd)
	{
		status = ft_check4builtin(cmd_tab[j], env);
		cmd_tab[j].pid = 0;
		if (status < 0)
			ft_fork_this(cmd_tab, env, j);
		else
			env->status = status;
		j++;
	}
	ft_close_fds_main(cmd_tab);
	return (ft_wait4child(cmd_tab, env));
}

void	ft_fork_this(t_main *cmd_tab, t_env *env, int i)
{
	cmd_tab[i].pid = fork();
	if (cmd_tab[i].pid < 0)
		quit_func(env, "forking failed", 2);
	if (cmd_tab[i].pid == 0)
	{
		ft_close_fd(cmd_tab, i);
		ft_check4redirections(&(cmd_tab[i]), i);
		if (cmd_tab[i + 1].cmd)
			dup2(cmd_tab[i].fd[1], STDOUT_FILENO);
		if (i != 0)
			dup2(cmd_tab[i - 1].fd[0], STDIN_FILENO);
		env->status = ft_exe_cmd(cmd_tab[i], env);
		close(cmd_tab[i].fd[1]);
		if (i != 0)
			close(cmd_tab[i - 1].fd[0]);
		exit(env->status);
	}
}

void	ft_check4redirections(t_main *cmd_tab, int cmd_tab_idx)
{
	int		i;
	size_t	size;

	i = -1;
	size = ft_2darray_size(cmd_tab->args);
	while (cmd_tab->args && cmd_tab->args[++i])
	{
		if (!str_ncmp(cmd_tab->args[i], ">", 1))
		{
			ft_redir_stdout(cmd_tab, i, size);
			break ;
		}
		if (!str_ncmp(cmd_tab->args[i], "<<", 2))
		{
			ft_redir_heredoc(cmd_tab, i, cmd_tab_idx, size);
			break ;
		}
		if (!str_ncmp(cmd_tab->args[i], "<", 1))
		{
			ft_redir_stdin(cmd_tab, i, size);
			break ;
		}
	}
	if (i != (int)size)
		ft_check4redirections(cmd_tab, cmd_tab_idx);
}

char	*ft_check4script(char *cmd, t_env *env)
{
	char	*path;
	char	*env_val;
	char	*temp;

	if (cmd[0] == '.')
	{
		env_val = ft_find_env_val("PWD", env->env_var);
		temp = str_dup(cmd + 1);
		path = ft_strjoin(env_val, temp);
		free(env_val);
		free(temp);
		return (path);
	}
	else if (cmd[0] == '/')
		return (cmd);
	return (0);
}

int	ft_exe_path(char *path, t_env *env, t_main cmd_tab)
{
	int		status;
	pid_t	pid;
	char	**arglist;

	pid = fork();
	arglist = 0;
	status = 0;
	signal_handler();
	if (pid == 0)
	{
		arglist = ft_cmd2arglist(cmd_tab, env);
		status = execve(path, arglist, env->env_var);
	}
	else if (pid < 0)
	{
		free (path);
		putendl_fd("fork in ft_exe_path failed", 2);
		return (-1);
	}
	wait(&status);
	free(path);
	clear_arr(arglist);
	env->status = status;
	return (status);
}
