/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:09:17 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/19 15:20:00 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	is_valis_quote(char c, int q, int dq)
{
	return ((c != '\'' && c != '\"')
		|| (c == '\'' && dq != -1 && (dq < q || q == -1))
		|| (c == '\"' && q != -1 && (q < dq || dq == -1)));
}

static int	get_size_epur(char *str)
{
	int	i;
	int	size;
	int	dquote;
	int	quote;

	dquote = -1;
	quote = -1;
	size = 0;
	i = 0;
	while (str && str[i])
	{
		check_quotes(str, i, &dquote, &quote);
		if (is_valis_quote(str[i], quote, dquote))
			size++;
		i++;
	}
	return (size);
}

char	*epurstr(char *str)
{
	int		dquote;
	int		quote;
	int		i;
	char	*new_str;
	int		j;

	j = 0;
	dquote = -1;
	quote = -1;
	i = 0;
	new_str = dh_malloc(get_size_epur(str) + 1);
	if (!new_str)
		return (0);
	while (str && str[i])
	{
		check_quotes(str, i, &dquote, &quote);
		if (is_valis_quote(str[i], quote, dquote))
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = 0;
	return (new_str);
}
