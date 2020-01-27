/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 23:29:29 by ede-ram          #+#    #+#             */
/*   Updated: 2020/01/16 01:01:21 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_builtins.h"

int		sh_find_error(char *path, char c, int *error)
{
	struct stat	s;
	int			mode;

	mode = F_OK | X_OK;
	if (stat(path, &s) == -1)
	{
		*error = NOT_FOUND;
		return (0);
	}
	if (c != '\0' && (s.st_mode & S_IFDIR) != S_IFDIR)
	{
		*error = NOT_DIR;
		return (0);
	}
	if (c != '\0' && access(path, mode) == -1)
	{
		*error = NOT_ACCESS;
		return (0);
	}
	return (1);
}

int		sh_check_path(char *all_path, int *error)
{
	char	*path;
	int		i;

	i = 0;
	if (!(path = malloc(sizeof(char) * strlen(all_path) + 1)))
		destructor(-1);
	while (all_path[i])
	{
		while (all_path[i] && all_path[i] != '/')
		{
			path[i] = all_path[i];
			i++;
		}
		path[i] = '\0';
		if (!(sh_find_error(path, all_path[i], error)))
		{
			path[i] = '1';
			ft_memdel((void**)&path);
			return (0);
		}
		path[i] = all_path[i];
		i++;
	}
	ft_memdel((void**)&path);
	return (1);
}
