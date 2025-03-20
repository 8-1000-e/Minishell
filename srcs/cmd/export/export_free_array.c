/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_free_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:45:51 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/17 15:43:24 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ms_free_all_env(t_data *data)
{
	ms_free_lst_env(data);
	dh_free(data->env);
}

void	ms_free_env(t_env *env)
{
	dh_free(env->key);
	if (env->value)
	{
		dh_free(env->value);
		env->value = NULL;
	}
	dh_free(env->str);
	env->key = NULL;
	env->str = NULL;
	dh_free(env);
}

void	ms_free_lst_env(t_data *data)
{
	t_env	*tmp;
	t_env	*next;

	tmp = data->env_list;
	while (tmp)
	{
		next = tmp->next;
		ms_free_env(tmp);
		tmp = next;
	}
}

t_env	**ms_build_array_export(t_data data)
{
	t_env	**tab;
	t_env	*tmp;
	int		i;

	tab = dh_malloc(sizeof(t_env *) * (ms_size_lst_env(&data, 1) + 1));
	if (!tab)
		return (0);
	i = 0;
	tmp = data.env_list;
	while (tmp)
	{
		tab[i++] = tmp;
		tmp = tmp->next;
	}
	tab[i] = 0;
	return (tab);
}

int	ms_build_array_env(t_data *data)
{
	int		i;
	t_env	*tmp;

	if (data->env)
		dh_free(data->env);
	i = ms_size_lst_env(data, 0);
	data->env = dh_malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (0);
	i = 0;
	tmp = data->env_list;
	while (tmp)
	{
		if (tmp->value)
			data->env[i++] = tmp->str;
		tmp = tmp->next;
	}
	data->env[i] = 0;
	return (1);
}
