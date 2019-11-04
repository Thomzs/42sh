/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:55:02 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/04 21:20:25 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh_env.h"
#include <limits.h>

int		sh_pwd(int ac, char **av, t_env **ev)
{
	char *tmp;

	(void)ac;
	(void)av;
	(void)ev;
	if (!(tmp = ft_strnew(PATH_MAX + 1)))
		return (1);
	tmp = getcwd(tmp, PATH_MAX);
	ft_putendl(tmp);
	ft_strdel(&tmp);
	return (0);
}
