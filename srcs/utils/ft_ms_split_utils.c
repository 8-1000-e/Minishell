/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42angouleme>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:00:01 by edubois-          #+#    #+#             */
/*   Updated: 2025/02/26 22:43:57 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_quote(char *str)
{
	int	iq[2];
	int	i;

	i = 0;
	iq[0] = 0;
	iq[1] = 0;
	while (str && str[i])
	{
		if (str[i] == '"' && iq[0] == 0 && ((i == 0)
				|| (i > 0 && str[i - 1] != '\\')) && iq[1] == 0)
			iq[1] = 1;
		else if (str[i] == '"' && iq[0] == 0 && ((i == 0)
				|| (i > 0 && str[i - 1] != '\\')) && iq[1] == 1)
			iq[1] = 0;
		else if (str[i] == '\'' && iq[1] == 0 && ((i == 0)
				|| (i > 0 && str[i - 1] != '\\')) && iq[0] == 0)
			iq[0] = 1;
		else if (str[i] == '\'' && iq[1] == 0 && ((i == 0)
				|| (i > 0 && str[i - 1] != '\\')) && iq[0] == 1)
			iq[0] = 0;
		i++;
	}
	if (iq[1] || iq[0])
		return (1);
	return (0);
}

void	add_quoted_word(char **word, char **str, int *idq, int *iq)
{
	int		i;
	char	*s[2];
	char	*save_w;

	s[0] = *str;
	s[1] = *word;
	save_w = s[1];
	i = 0;
	if (*iq)
		*s[1]++ = '\'';
	else
		*s[1]++ = '"';
	while (s[0][i] && (*idq || *iq || (s[0][i] != ' ' && s[0][i + 1] != '|')))
	{
		*s[1]++ = s[0][i];
		if (s[0][i] == '"' && *iq == 0 && ((i == 0)
			|| (i > 0 && s[0][i - 1] != '\\')) && *idq == 1)
			*idq = 0;
		else if (s[0][i] == '\'' && *idq == 0 && ((i == 0)
			|| (i > 0 && s[0][i - 1] != '\\')) && *iq == 1)
			*iq = 0;
		i++;
	}
	*word = save_w;
	*str = s[0] + i;
}

void	finish_to_add_word(char *s, char **w, int *i, int iq[2])
{
	while (s[*i] && (iq[0] || iq[1]))
	{
		**w = s[*i];
		(*w)++;
		if (s[*i] == '"' && iq[0] == 0 && ((*i == 0)
				|| (*i > 0 && s[*i - 1] != '\\')) && iq[1] == 1)
			iq[1] = 0;
		else if (s[*i] == '\'' && iq[1] == 0 && ((*i == 0)
				|| (*i > 0 && s[*i - 1] != '\\')) && iq[0] == 1)
			iq[0] = 0;
		(*i)++;
	}
	while (s[*i] && s[*i] != ' ' && s[*i] != '|')
	{
		**w = s[*i];
		(*w)++;
		(*i)++;
	}
}

void	add_word(char *s, char **w, int *i, int iq[2])
{
	while (s[*i] && !iq[0] && !iq[1] && s[*i] != ' ' && s[*i] != '|')
	{
		**w = s[*i];
		(*w)++;
		if (s[*i] == '"' && iq[0] == 0 && ((*i == 0)
				|| (*i > 0 && s[*i - 1] != '\\')) && iq[1] == 0)
			iq[1] = 1;
		else if (s[*i] == '\'' && iq[1] == 0 && ((*i == 0)
				|| (*i > 0 && s[*i - 1] != '\\')) && iq[0] == 0)
			iq[0] = 1;
		(*i)++;
	}
	finish_to_add_word(s, w, i, iq);
}

void	add_simple_word(char **word, char **str)
{
	char	*s;
	char	*w;
	char	*s_w;
	int		i;
	int		iq[2];

	s = *str;
	w = *word;
	s_w = w;
	i = 0;
	iq[0] = 0;
	iq[1] = 0;
	add_word(s, &w, &i, iq);
	*word = s_w;
	*str = s + i;
}
