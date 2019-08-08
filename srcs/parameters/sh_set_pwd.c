/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_set_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 00:13:54 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/06 23:31:46 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"
#include <limits.h>

void	sh_set_pwd(void)
{
	char	*tmp2;

	if ((tmp2 = ft_strnew(PATH_MAX + 1)))
	{
		tmp2 = getcwd(tmp2, PATH_MAX);
		sh_setenv("PWD", tmp2);
		ft_strdel(&tmp2);
	}
}
