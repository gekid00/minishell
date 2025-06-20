/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:29:06 by reeer-aa          #+#    #+#             */
/*   Updated: 2025/06/19 13:35:49 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/colors.h"

char	*format_prompt_part(char *content, char *color)
{
	char	*temp;
	char	*result;

	if (!content || !color)
		return (NULL);
	temp = ft_strjoin(color, content);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, RESET);
	free(temp);
	return (result);
}

int	get_last_exit_status(void)
{
	if (g_signal_status >= 256)
		return (g_signal_status - 256);
	return (g_signal_status);
}
