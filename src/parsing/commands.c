/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:41:23 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:11:39 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main	*comm_tbl(char **input)
{
	char		**res;
	t_main		*ptr;
	int			i;

	res = is_valid_input(input);
	if (!res)
		return (0);
	ptr = malloc(sizeof(t_main)
			* (word_count(*input, '|') + 1));
	i = 0;
	while (res[i])
	{
		ptr[i].cmd = 0;
		ptr[i].options = 0;
		ptr[i].args = 0;
		get_comm(res[i], &(ptr[i]));
		i++;
	}
	ptr[i].cmd = 0;
	clear_arr(res);
	return (ptr);
}

void	get_comm(char *str, t_main *ptr)
{
	int		i;

	i = 0;
	if (str[i] == ' ')
		str++;
	while (str[i] && str[i] != ' ')
		i++;
	ptr->cmd = sub_str(str, 0, i);
	ptr->fd[0] = 0;
	ptr->fd[1] = 1;
	ptr->args = malloc(sizeof(char *)
			* (num_of_args(str, i) + 1));
	ptr->args[0] = 0;
	if (!str[i] || !str[i + 1])
		return ;
	i++;
	update_comm(str, ptr, i);
}

void	update_comm(char *str, t_main *ptr, int i)
{
	int		j;
	int		k;

	k = 0;
	while (str[i])
	{
		j = 1;
		if (str[i] == '-' && str[i + 1] && is_alpha(str[i + 1]))
			get_flag(str, ptr, i, &j);
		else if (is_a_quote(str[i]))
			j = quoted_arg(ptr, str, i, &k);
		else
		{
			while (str[i + j] != ' ' && str[i + j])
				j++;
			add_args(ptr, &k, sub_str(str, i, j));
		}
		while ((--j + 2) && str[i])
			i++;
	}
	ptr->args[k] = 0;
}

void	get_flag(char *str, t_main *ptr, int i, int *j)
{
	char	*str1;
	char	*str2;

	while (str[i + *j] != ' ' && str[i + *j])
		(*j)++;
	if (ptr->options)
	{
		str2 = sub_str(str, i + 1, (*j) - 1);
		str1 = ft_strjoin(ptr->options, str2);
		free(ptr->options);
		free(str2);
		ptr->options = str1;
	}
	else
		ptr->options = sub_str(str, i + 1, (*j) - 1);
}

int	quoted_arg(t_main *ptr, char *str, int i, int *k)
{
	int	j;

	j = 1;
	while (str[i + j] != str[i])
		j++;
	if (str[i] == str[i + 1] && j++)
		ptr->args[(*k)++] = str_dup("\0");
	else
		add_args(ptr, k, sub_str(str, i + 1, j++ - 1));
	return (j);
}
