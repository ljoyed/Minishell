/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:52:59 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/04 11:19:11 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_open_setup(char *filename, char *itoa)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		putendl_fd("Error creating tmp in heredoc", 2);
		return (-1);
	}
	free(itoa);
	return (fd);
}

static void	ft_heredoc_setup(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		putendl_fd("Error opening temporary file for input redirection", 2);
		return ;
	}
	dup2(fd, 0);
	free(filename);
	close(fd);
}

static void	heredoc_loop(char *eof, int fd, t_main *cmd, int i)
{
	char	*input;

	while (1)
	{
		input = readline("heredoc> ");
		if (!eof)
		{
			if (str_ncmp(input, cmd->args[i + 1], sizeof(input)) == 0)
			{
				free(input);
				break ;
			}
		}
		else
		{
			if (str_ncmp(input, eof, sizeof(input)) == 0)
			{
				free(input);
				break ;
			}
		}
		putstr_fd(input, fd);
		putstr_fd("\n", fd);
		free(input);
	}
}

void	ft_redir_heredoc(t_main *cmd, int i, int cmd_idx, size_t size)
{
	int		fd;
	char	*filename;
	char	*eof;
	char	*itoa;

	itoa = ft_itoa(cmd_idx);
	filename = ft_strjoin(".tmp", itoa);
	fd = ft_open_setup(filename, itoa);
	if (cmd->args[i][2] != '\0')
		eof = str_dup(cmd->args[i] + 2);
	else
		eof = NULL;
	heredoc_loop(eof, fd, cmd, i);
	close(fd);
	ft_heredoc_setup(filename);
	free(cmd->args[i]);
	cmd->args[i] = 0;
	if (eof)
		free(eof);
	else
	{
		free(cmd->args[i + 1]);
		cmd->args[i + 1] = 0;
	}
	ft_rearrange(cmd->args, size, i);
}
