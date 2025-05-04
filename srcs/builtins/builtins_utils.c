/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 02:50:34 by gekido            #+#    #+#             */
/*   Updated: 2025/05/04 04:56:56 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	source_builtin(char **args, t_env *env)
{
	if (!args[1])
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		env->exit_code = 2;
		return (2);
	}
	if (args[1][0] == '.' && ft_strspn(args[1], ".") == ft_strlen(args[1]))
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(args[1], 2);
		env->exit_code = 127;
		return (127);
	}
	ft_putstr_fd("minishell: .: ", 2);
	ft_putendl_fd(args[1], 2);
	env->exit_code = 1;
	return (1);
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

int	find_env_var_index(char **vars, char *var, int len)
{
	int	i;

	i = 0;
	while (vars[i])
	{
		if (ft_strncmp(vars[i], var, len) == 0 && vars[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**realloc_env(char **env, char *new, int count)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (count + 2));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < count)
		tab[i] = env[i];
	tab[i++] = new;
	tab[i] = NULL;
	free(env);
	return (tab);
}
