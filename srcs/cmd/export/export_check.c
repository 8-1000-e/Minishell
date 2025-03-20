/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:43:21 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:51 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	is_valid_char(char c)
{
	return (ft_isalnum(c) || c == '_' );
}

int	is_valid_key(char *str)
{
	if (ft_isdigit(*str))
		return (0);
	while (*str)
		if (!is_valid_char(*str++))
			return (0);
	return (1);
}

int	get_bigger(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] <= str2[i]);
}

void	ms_swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ms_print_export(t_data data)
{
	t_env	**tab;
	int		big;
	int		i;
	int		j;

	tab = ms_build_array_export(data);
	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
	{
		j = i + 1;
		big = i;
		while (tab[j])
			if (get_bigger(tab[j++]->key, tab[big]->key))
				big = j - 1;
		ms_swap_env(&tab[i], &tab[big]);
		if (tab[i]->value)
			printf("export %s=\"%s\"\n", tab[i]->key, tab[i]->value);
		else
			printf("export %s\n", tab[i]->key);
		i++;
	}
	dh_free(tab);
	return (0);
}
