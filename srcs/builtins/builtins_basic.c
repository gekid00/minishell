/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:30:00 by gekido            #+#    #+#             */
/*   Updated: 2025/06/04 22:49:57 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_builtin(char **args, t_env *env)
{
	char	cwd[1024];
	char	*path;
	int		should_free;

	if (ft_tablen(args) > 2)
		return (ft_putendl_fd("minishell: too many arguments", 2), 1);
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_env_value("HOME", env);
		if (!path)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
		should_free = 0;
	}
	else
	{
		path = ft_strdup(args[1]);
		should_free = 1;
	}
	if (chdir(path))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		if (should_free)
			free(path);
		return (1);
	}
	if (getcwd(cwd, 1024))
		update_env_var(env, "PWD", cwd);
	if (should_free)
		free(path);
	return (0);
}

int	echo_builtin(char **args)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args, t_env *env)
{
	(void)env;
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		g_signal_status = 256;
		return (0);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_signal_status = 256 + 2;
		return (2);
	}
	if (args[2])
		return (ft_putendl_fd("minishell: exit: too many arguments", 2), 1);
	g_signal_status = ft_atoi(args[1]);
	g_signal_status = ((g_signal_status % 256) + 256) % 256;
	g_signal_status = 256 + g_signal_status;
	return (g_signal_status % 256);
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
