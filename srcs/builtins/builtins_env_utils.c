/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:00:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/25 00:16:11 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_env_tab(char **old, char *new_var, int size)
{
	char	**tab;
	int		j;

	tab = malloc(sizeof(char *) * (size + 2));
	if (!tab)
		return (NULL);
	j = 0;
	while (j < size)
	{
		tab[j] = old[j];
		j++;
	}
	tab[size] = new_var;
	tab[size + 1] = NULL;
	return (tab);
}

int	key_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	update_env_var(t_env *env, char *key, char *value)
{
	char	*var;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	var = ft_strjoin(tmp, value);
	free(tmp);
	add_env_var(env, var);
	free(var);
}

int	find_and_replace_env_var(t_env *env, char *var, char *new, int klen)
{
	int	i;

	i = 0;
	while (env->vars[i])
	{
		if (ft_strncmp(env->vars[i], var, klen) == 0
			&& (env->vars[i][klen] == '\0' || env->vars[i][klen] == '='))
		{
			free(env->vars[i]);
			env->vars[i] = new;
			return (1);
		}
		i++;
	}
	return (0);
}

void	allocate_new_env(t_env *env, char *var)
{
	int		i;
	char	**new_vars;

	i = 0;
	while (env->vars[i])
		i++;
	new_vars = malloc(sizeof(char *) * (i + 2));
	if (!new_vars)
		return ;
	i = -1;
	while (env->vars[++i])
		new_vars[i] = env->vars[i];
	new_vars[i] = ft_strdup(var);
	new_vars[i + 1] = NULL;
	free(env->vars);
	env->vars = new_vars;
}
