/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:54 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/04 11:18:45 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	putchar_fd(char c, int fd)
{
	if (c || fd >= 0)
		write(fd, &c, 1);
}

void	putstr_fd(char *s, int fd)
{
	if (s || fd >= 0)
		write(fd, s, str_len(s));
}

void	putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	putstr_fd(s, fd);
	putchar_fd('\n', fd);
}
