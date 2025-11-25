/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:35:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/23 10:49:53 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(t_env *env)
{
	int	i;

	i = 0;
	while (env->vars[i])
	{
		ft_putendl_fd(env->vars[i], 1);
		i++;
	}
	return (0);
}

int	unset_builtin(char **args, t_env *env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (args[++i])
	{
		len = ft_strlen(args[i]);
		j = -1;
		while (env->vars[++j])
		{
			if (ft_strncmp(env->vars[j], args[i], len) == 0)
			{
				free(env->vars[j]);
				while (env->vars[j])
				{
					env->vars[j] = env->vars[j + 1];
					j++;
				}
				break ;
			}
		}
	}
	return (0);
}

bool	is_valid_env_var_name(char *var)
{
	int	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (false);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	add_env_var(t_env *env, char *var)
{
	int		i;
	int		klen;
	char	*new;
	char	**tab;

	klen = key_len(var);
	new = ft_strdup(var);
	if (!is_valid_env_var_name(var))
	{
		print_invalid(var);
		free(new);
		return ;
	}
	if (find_and_replace_env_var(env, var, new, klen))
		return ;
	i = 0;
	while (env->vars[i])
		i++;
	tab = expand_env_tab(env->vars, new, i);
	free(env->vars);
	env->vars = tab;
}
