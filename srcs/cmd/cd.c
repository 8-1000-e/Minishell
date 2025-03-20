/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:57:26 by npalissi          #+#    #+#             */
/*   Updated: 2025/03/19 13:37:10 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ms_chdir(char *path, char **cmd)
{
	if (chdir(path) == -1)
	{
		printf("shellokitty: cd: %s: %s\n", cmd[1], strerror(errno));
		return (0);
	}
	return (1);
}

int	cd_env(t_data *data, char **cmd, char *key, int msg)
{
	t_env	*env;
	int		exit_chdir;

	env = ms_get_node_by_key(data, key);
	if (!env || !env->value)
	{
		printf("shellokitty: cd: %s not set\n", key);
		return (0);
	}
	exit_chdir = ms_chdir(env->value, cmd);
	if (exit_chdir && msg)
		printf("%s\n", env->value);
	return (exit_chdir);
}

int	cd_rel_abs(char **cmd)
{
	int		exit_chdir;

	exit_chdir = ms_chdir(cmd[1], cmd);
	return (exit_chdir);
}

int	cd(t_data *data, char **cmd)
{
	char	exit_code;

	if (ft_strcmp(cmd[1], "-"))
		exit_code = cd_env(data, cmd, "OLDPWD", 1);
	else if (!cmd[1])
		exit_code = cd_env(data, cmd, "HOME", 0);
	else
		exit_code = cd_rel_abs(cmd);
	if (exit_code == -1)
		return (-1);
	if (!exit_code)
		return (0);
	return (reload_pwd(data));
}
