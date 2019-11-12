/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:39:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/11/11 22:45:29 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sh.h"

#include <stdlib.h>

void	sh_env_del(t_env **env)
{
	t_env	*ev;

	if (!env || !(ev = *env))
		return ;
	ft_strdel(&(ev->key));
	ft_strdel(&(ev->value));
	sh_env_del(&(ev->next));
	free(*env);
	*env = NULL;
}