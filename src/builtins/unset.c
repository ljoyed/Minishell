/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:38:51 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:10:18 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_func(t_env *env, t_main ptr)
{
	char	*str;
	int		len;

	if (!ptr.args[0] || ptr.args[1])
		return (2);
	len = str_chrn(ptr.args[0], '=');
	if (!len)
		return (3);
	str = sub_str(ptr.args[0], 0, len);
	rem_env_var(env, str);
	free(str);
	return (0);
}
