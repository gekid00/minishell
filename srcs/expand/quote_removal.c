/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:52 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/16 21:03:51 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_quote_char(char *str, int *i, bool *in_single, bool *in_double)
{
	if (str[*i] == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		(*i)++;
	}
	else if (str[*i] == '"' && !*in_single)
	{
		*in_double = !*in_double;
		(*i)++;
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
