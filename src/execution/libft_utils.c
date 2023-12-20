/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:55:37 by ekuchel           #+#    #+#             */
/*   Updated: 2023/10/05 09:38:36 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_str2lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	posneg;

	posneg = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			posneg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res *= 10;
		res = res + (str[i] - '0');
		i++;
	}
	return (res * posneg);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	ptr = malloc(sizeof(char) * (str_len(s1) + str_len(s2) + 1));
	if (ptr == NULL)
		return (ptr);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

int	digsize(int num)
{
	int	i;
	int	pos;

	pos = num;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		i++;
		pos *= -1;
	}
	while (pos != 0)
	{
		i++;
		pos /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	num;

	num = n;
	size = digsize(n);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[size--] = '\0';
	if (num == 0)
		ptr[0] = '0';
	else if (num < 0)
	{
		ptr[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		ptr[size--] = (num % 10) + '0';
		num /= 10;
	}
	return (ptr);
}
