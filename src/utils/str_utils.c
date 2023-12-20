/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:49:07 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/03 14:12:21 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	str_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_ncmp(char *str1, char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && (i < n - 1) && (str1[i] == str2[i]))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

char	*str_dup(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * str_len(str) + 1);
	i = 0;
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	str_chrn(char *str, int c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*sub_str(char *str, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	if (str_len(str) < len)
		len = str_len(str);
	res = malloc(sizeof(char) * (len + 1));
	while (start <= str_len(str) && i < len)
	{
		res[i] = str[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
