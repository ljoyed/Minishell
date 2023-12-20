/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:43:20 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:12:31 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**is_valid_input(char **inp)
{
	char		**inp_split;
	int			i;
	int			j;
	int			space;

	ignore_pipe(inp);
	inp_split = ft_split(*inp, '|');
	inp_split = add_pipe(inp_split);
	i = 0;
	while (inp_split[i])
	{
		j = 0;
		space = 1;
		while (inp_split[i][j])
		{
			if (inp_split[i][j++] != ' ')
				space = 0;
		}
		if (space)
			return (0);
		i++;
	}
	return (inp_split);
}

void	ignore_pipe(char **inp)
{
	int	i;
	int	j;

	i = 0;
	while ((*inp)[i])
	{
		if (is_a_quote((*inp)[i]))
		{
			j = i + 1;
			while ((*inp)[j] != (*inp)[i] && (*inp)[j])
			{
				if ((*inp)[j] == '|')
					(*inp)[j] = 26;
				j++;
			}
			i = j + 1;
		}
		else
			i++;
	}
}

char	**add_pipe(char **inp)
{
	int	i;
	int	j;

	i = 0;
	while (inp[i])
	{
		j = 0;
		while (inp[i][j])
		{
			if (inp[i][j] == 26)
				inp[i][j] = '|';
			j++;
		}
		i++;
	}
	return (inp);
}

int	num_of_args(char *str, int i)
{
	int		j;
	int		res;

	res = 0;
	while (str && str[i])
	{
		j = 1;
		if (is_a_quote(str[i]))
		{
			while (str[i + j] != str[i] && str[i + j])
				j++;
			res++;
		}
		else
		{
			while (str[i + j] != ' ' && str[i + j])
				j++;
			res++;
		}
		while ((--j + 2) && str[i])
			i++;
	}
	return (res);
}

void	add_args(t_main *command, int *k, char *arg)
{
	if (arg[0] != 0)
		command->args[(*k)++] = arg;
	else
		free(arg);
}
