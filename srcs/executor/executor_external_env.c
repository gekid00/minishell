/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 01:49:32 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_partial_env(char **dup_env, int count)
{
	while (count > 0)
		free(dup_env[--count]);
	free(dup_env);
}

char	**allocate_env_array(int count)
{
	char	**dup_env;

	dup_env = malloc(sizeof(char *) * (count + 1));
	return (dup_env);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**convert_env_to_array(t_env *env)
{
	return (env->vars);
}
