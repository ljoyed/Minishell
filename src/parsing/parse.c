/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:44:22 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:13:58 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inp_trim(char **inp)
{
	char	*res;
	char	quote;

	res = (char *)malloc(str_len(*inp) + 1);
	if (!res)
		quit_func(0, "failed to trim input", 2);
	trimmer(inp, &quote, &res);
	free(*inp);
	if (quote != '\0')
	{
		free(res);
		*inp = 0;
	}
	else
		*inp = res;
}

void	vars_to_inp(t_env *env, char **inp, char **res,
	t_data	*data)
{
	int		k;
	int		h;
	char	*key;
	char	*val;

	k = data->x + 1;
	while (valid_char((*inp)[k]) && !is_a_quote((*inp)[k])
		&& (*inp)[k])
		k++;
	key = sub_str(*inp, data->x + 1, k - data->x - 1);
	if (str_ncmp(key, "?", 1) == 0)
		val = ft_itoa(env->status);
	else
		val = get_env_var(env, key);
	h = 0;
	if (val)
		while (val[h])
			(*res)[data->y++] = val[h++];
	data->x += str_len(key) + 1;
	free(key);
	free(val);
}

void	parsing_vars(t_env *env, char **inp, char **res)
{
	t_data	data;

	data.x = 0;
	data.y = 0;
	while ((*inp)[data.x])
	{
		if ((*inp)[data.x] == '\'' && !is_quote_closed(*inp, data.x))
		{
			(*res)[data.y++] = (*inp)[data.x++];
			while ((*inp)[data.x] && (*inp)[data.x] != '\'')
				(*res)[data.y++] = (*inp)[data.x++];
			if ((*inp)[data.x] == '\'')
				(*res)[data.y++] = (*inp)[data.x++];
		}
		else if ((*inp)[data.x] == '$' && (*inp)[data.x + 1] != ' ')
		{
			vars_to_inp(env, inp, res, &data);
		}
		else
			(*res)[data.y++] = (*inp)[data.x++];
	}
	(*res)[data.y] = '\0';
}

void	parse_vars(t_env *env, char **inp)
{
	char	*res;

	res = (char *)malloc(str_len(*inp) * sizeof(char *));
	if (!res)
		quit_func(env, "failed to alloc in interprete var", 2);
	parsing_vars(env, inp, &res);
	free(*inp);
	*inp = res;
}

t_main	*parse(t_env *env, char **inp)
{
	inp_trim(inp);
	if (!*inp || !**inp)
		return (0);
	parse_vars(env, inp);
	if (!inp)
		quit_func(env, "failed to interprete var", 2);
	return (comm_tbl(inp));
}
