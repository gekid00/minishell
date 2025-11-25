/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:05:54 by gekido            #+#    #+#             */
/*   Updated: 2025/06/17 13:59:54 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_quotes(char *input)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	if (!input)
		return (0);
	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (input[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	if (in_single_quotes || in_double_quotes)
	{
		ft_putendl_fd("minishell: syntax error: unmatched quotes", 2);
		return (1);
	}
	return (0);
}

int	should_stop_word(char *input, int i)
{
	return (ft_is_space(input[i]) || input[i] == '|' || input[i] == '<'
		|| input[i] == '>' || input[i] == '\0');
}

void	handle_normal_text(char *input, int *i, char **word)
{
	char	*tmp;
	char	c[2];

	c[0] = input[*i];
	c[1] = '\0';
	tmp = ft_strjoin(*word, c);
	if (tmp)
	{
		free(*word);
		*word = tmp;
	}
	(*i)++;
}

void	extract_quoted_text(char *input, int *i, char **word, char quote)
{
	append_quote_to_word(word, quote);
	(*i)++;
	append_quoted_content(input, i, word, quote);
	if (input[*i] == quote)
	{
		append_quote_to_word(word, quote);
		(*i)++;
	}
}

char	*get_word(char *input, int *i)
{
	char	*word;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*i] && !should_stop_word(input, *i))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quotes(input, i, &word);
		else
			handle_normal_text(input, i, &word);
		if (!word)
			return (NULL);
	}
	return (word);
}
