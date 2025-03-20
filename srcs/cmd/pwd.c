/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:08:43 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/20 13:33:24 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pwd(void)
{
	char	path[1024];

	getcwd(path, sizeof(path));
	printf("%s\n", path);
	return (0);
}

int	reload_pwd(t_data *data)
{
	char	path[1024];
	t_env	*node_old_pwd;
	t_env	*node_pwd;

	getcwd(path, sizeof(path));
	node_old_pwd = ms_create_node_ifno(data, "OLDPWD");
	node_pwd = ms_create_node_ifno(data, "PWD");
	if (!node_old_pwd || !node_pwd)
		return (-1);
	ms_swap_node(&node_old_pwd->key, &node_pwd->key);
	if (!ms_edit_env_lst(data, "PWD", path, ft_buildstr("%s=%s", "PWD", path)))
		return (-1);
	ms_build_array_env(data);
	return (0);
}
