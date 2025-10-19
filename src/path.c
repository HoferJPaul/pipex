/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:53:28 by phofer            #+#    #+#             */
/*   Updated: 2025/10/19 14:03:51 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*build_and_test(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*search_in_path(char *cmd, char **paths)
{
	int		i;
	char	*result;

	i = 0;
	while (paths[i])
	{
		result = build_and_test(paths[i], cmd);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_val;
	char	*result;

	if (!cmd || ft_strchr(cmd, '/'))
		return (cmd);
	path_val = ft_getenvp("PATH", env);
	if (!path_val)
		return (cmd);
	paths = ft_split(path_val, ':');
	if (!paths)
		return (cmd);
	result = search_in_path(cmd, paths);
	ft_free_tab(paths);
	if (result)
		return (result);
	return (cmd);
}
