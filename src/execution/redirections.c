/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:31:14 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:18:02 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_redir_helper(t_main *cmd, int nb_char, int i, int *fd)
{
	char	*newarg;

	if (cmd->args[i][nb_char] != '\0')
	{
		newarg = str_dup(cmd->args[i] + nb_char);
		if (nb_char == 2)
			*fd = open(newarg, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			*fd = open(newarg, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		free(cmd->args[i]);
		free(newarg);
		cmd->args[i] = 0;
	}
	else
	{
		if (nb_char == 2)
			*fd = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			*fd = open(cmd->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		free(cmd->args[i]);
		free(cmd->args[i + 1]);
		cmd->args[i] = 0;
		cmd->args[i + 1] = 0;
	}
}

void	ft_redir_stdout(t_main *cmd_tab, int i, size_t size)
{
	int		fd;

	if (str_ncmp(cmd_tab->args[i], ">>", 2) == 0)
		ft_redir_helper(cmd_tab, 2, i, &fd);
	else
		ft_redir_helper(cmd_tab, 1, i, &fd);
	if (fd < 0)
	{
		putstr_fd("Open failed in ft_redir_stdout\n", 2);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_rearrange(cmd_tab->args, size, i);
}

void	ft_redir_stdin(t_main *cmd_tab, int i, size_t size)
{
	int		fd;
	char	*newarg;

	if (cmd_tab->args[i][1] != '\0')
	{
		newarg = str_dup(cmd_tab->args[i] + 1);
		fd = open(newarg, O_RDONLY, 0777);
		free(newarg);
		free(cmd_tab->args[i]);
		cmd_tab->args[i] = 0;
	}
	else
	{
		fd = open(cmd_tab->args[i + 1], O_RDONLY, 0777);
		free(cmd_tab->args[i]);
		free(cmd_tab->args[i + 1]);
		cmd_tab->args[i] = 0;
		cmd_tab->args[i + 1] = 0;
	}
	if (fd == -1)
		return (putstr_fd("Open failed in ft_redir_stdin\n", 2));
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_rearrange(cmd_tab->args, size, i);
}
