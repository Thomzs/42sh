/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 23:04:22 by ede-ram          #+#    #+#             */
/*   Updated: 2019/09/08 22:47:16 by ede-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_env.h"
#include "libft.h"

int			sh_unset(int ac, char **av, t_env **env)
{
	int i;

	i = 0;
	while (++i < ac)
		sh_unsetev(av[i], env);
	return (0);
}
