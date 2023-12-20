/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:43:53 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:13:06 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_checker(char **inp, int i, char *quote)
{
	if (*quote == '\0' && is_a_quote((*inp)[i]))
	{
		*quote = (*inp)[i];
	}
	else if (*quote == (*inp)[i])
	{
		*quote = '\0';
	}
}

void	trimmer(char **inp, char *quote, char **res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	*quote = '\0';
	while ((*inp)[i] && trim_char((*inp)[i]))
		i++;
	while ((*inp)[i])
	{
		while ((*inp)[i] && (!trim_char((*inp)[i]) || *quote))
		{
			quote_checker(inp, i, quote);
			(*res)[j] = (*inp)[i];
			j++;
			i++;
		}
		while ((*inp)[i] && trim_char((*inp)[i]))
			i++;
		if ((*inp)[i])
			(*res)[j++] = ' ';
	}
	(*res)[j] = '\0';
}

int	trim_char(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	is_a_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_quote_closed(char *str, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count % 2);
}
