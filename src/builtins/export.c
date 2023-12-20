/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:38:04 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:09:48 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_func(t_env *env, t_main ptr)
{
	char	*str1;
	char	*str2;
	int		len;

	if (!ptr.args[0] || ptr.args[1])
		return (2);
	len = str_chrn(ptr.args[0], '=');
	if (!len)
		return (3);
	str1 = sub_str(ptr.args[0], 0, len);
	rem_env_var(env, str1);
	str2 = sub_str(ptr.args[0], len + 1,
			str_len(ptr.args[0]) - str_len(str1) - 1);
	add_env_var(env, str1, str2);
	free(str1);
	free(str2);
	return (0);
}
