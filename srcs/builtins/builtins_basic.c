/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/23 10:31:26 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cd_path(char **args, t_env *env, int *should_free)
{
	char	*path;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_env_value("HOME", env);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		*should_free = 1;
	}
	else
	{
		path = ft_strdup(args[1]);
		*should_free = 1;
	}
	return (path);
}

int	handle_cd_error(char *path, int should_free)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	if (should_free)
		free(path);
	return (1);
}

int	cd_builtin(char **args, t_env *env)
{
	char	cwd[1024];
	char	*path;
	int		should_free;

	if (ft_tablen(args) > 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[1], 2);
		return (ft_putendl_fd(": too many arguments", 2), 1);
	}
	path = get_cd_path(args, env, &should_free);
	if (!path)
		return (1);
	if (chdir(path))
		return (handle_cd_error(path, should_free));
	if (getcwd(cwd, 1024))
		update_env_var(env, "PWD", cwd);
	if (should_free)
		free(path);
	return (0);
}

int	echo_builtin(char **args)
{
	int	result;
	int	n;
	int	i;

	result = process_n_option(args);
	i = result / 1000;
	n = result % 1000;
	print_echo_args(args, i);
	if (!n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
}
