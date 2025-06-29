/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:39:02 by gekido            #+#    #+#             */
/*   Updated: 2025/06/25 00:04:19 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

char	*get_env_value(char *var, t_env *env)
{
	int	i;
	int	len;

	if (ft_strcmp((char *)var, "?") == 0)
		return (ft_itoa(env->exit_code));
	len = ft_strlen(var);
	i = 0;
	while (env->vars[i])
	{
		if (ft_strncmp(env->vars[i], var, len) == 0 && env->vars[i][len] == '=')
			return (ft_strdup(env->vars[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	expand_token_variables(t_token *tokens, t_env *env)
{
	t_token	*cur;
	char	*expanded;
	char	*final;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_WORD)
		{
			expanded = expand_variables(cur->value, env);
			if (expanded)
			{
				final = remove_quotes(expanded);
				if (final)
				{
					free(cur->value);
					cur->value = final;
				}
				free(expanded);
			}
		}
		cur = cur->next;
	}
}

void	copy_regular_char(char *str, char *result, int *i, int *j)
{
	result[*j] = str[*i];
	(*j)++;
	(*i)++;
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (str[i])
	{
		if ((str[i] == '\'' && !in_double_quotes)
			|| (str[i] == '"' && !in_single_quotes))
			handle_quote_char(str, &i, &in_single_quotes, &in_double_quotes);
		else
			copy_regular_char(str, result, &i, &j);
	}
	result[j] = '\0';
	return (result);
}
