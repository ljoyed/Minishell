/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekuchel <ekuchel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:45:34 by loandrad          #+#    #+#             */
/*   Updated: 2023/10/05 10:32:16 by ekuchel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_comm_tbl(t_main *ptr)
{
	int	i;

	i = 0;
	while (ptr[i].cmd)
	{
		if (ptr[i].cmd)
			free(ptr[i].cmd);
		if (ptr[i].options)
			free(ptr[i].options);
		if (ptr[i].args)
			clear_arr(ptr[i].args);
		i++;
	}
	free(ptr);
}

void	minishell(t_env *env)
{
	char	*input;
	t_main	*ptr;

	while (1)
	{
		signal_func();
		input = readline("$$$: ");
		if (input == NULL)
			break ;
		if (!input[0])
			continue ;
		add_history(input);
		ptr = parse(env, &input);
		if (!ptr || ptr[0].cmd == 0)
			continue ;
		env->status = ft_execute(ptr, env);
		free_comm_tbl(ptr);
		free(input);
	}
}

int	main(int argc, char *argv[], char **env_var)
{
	t_env	env;

	if (argc != 1)
		return (0);
	(void)argv;
	cp_env_var(&env, env_var);
	signal_func();
	minishell(&env);
	clear_env(&env);
	return (0);
}
