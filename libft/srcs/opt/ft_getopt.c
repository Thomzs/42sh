/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:35:28 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/11 21:52:13 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		ft_check_opt(char *name, size_t size_name, char *optstr)
{
	char *tmp;
	char *oldtmp;	

	tmp = optstr;
	if (ft_strnequ(optstr, name, size_name))
		return ((*(tmp + size_name + 1) == ':') + 1);
	while ((tmp = ft_strchr(tmp + 1, '|')))
	{
		oldtmp = tmp;
		if (ft_strnequ(tmp + 1, name, size_name))
			return ((*(tmp + size_name + 1) == ':') + 1);
	}
	if (!(tmp = ft_strchr(optstr, '|')))
		tmp = optstr + ft_strlen(optstr) - 1;
	if (ft_strnequ(optstr, name, size_name))
		return ((*(tmp - 1) == ':') + 1);
	if (ft_strnequ(tmp + 1, name, size_name))
		return ((*(tmp - 1) == ':') + 1);
	return (0);
}

t_opt	*ft_create_sopt(char name, char *content)
{
	t_opt *tmp;

	tmp = NULL;
	if (!(tmp = (t_opt*)malloc(sizeof(t_opt))))
		return (NULL);
	tmp->name = ft_strndup(&name, 1);
	tmp->arg = NULL;
	if (content)
		tmp->arg = ft_strdup(content);
	tmp->next = NULL;
	return (tmp);
}

t_opt	*ft_create_dopt(char *name, char *content)
{
	t_opt *tmp;

	tmp = NULL;
	if (!(tmp = (t_opt*)malloc(sizeof(t_opt))))
		return (NULL);
	tmp->name = ft_strdup(name);
	tmp->arg = NULL;
	if (content)
		tmp->arg = ft_strdup(content);
	tmp->next = NULL;
	return (tmp);
}

t_opt	*ft_get_sopt_arg(int *ac, char ***av, int i)
{
	char	*arg;
	char	name;
	t_opt	*optmp;

	arg = NULL;
	name = (**av)[i];
	if ((**av)[i + 1] == '=')
		arg = ft_strdup(**av + i + 2);
	else if ((**av)[i + 1])
		arg = ft_strdup(**av + i + 1);
	else
	{
		(*ac)--;
		(*av)++;
		arg = ft_strdup(**av);
	}
	if (!arg)
		return (NULL);
	optmp = ft_create_sopt(name, arg);
	free(arg);
	return (optmp);
}

t_opt	*ft_get_dopt(int *ac, char ***av, char *optstr)
{
	int check;
	t_opt *optmp;
	char *tmp;

	optmp = NULL;
	check = ft_check_opt((**av), ft_strlen(**av), optstr);
	if (check == 1)
		optmp = ft_create_dopt((**av), NULL);
	else if (check == 2 && (tmp = ft_strchr(**av, '=')))
		optmp = ft_get_sopt_arg(ac, av, tmp - **av);
	else if (check == 2)
		optmp = ft_get_sopt_arg(ac, av, ft_strlen(**av) - 1);
	else
		;//ft_perror
	return (optmp);
}

t_opt	*ft_get_sopt(int *ac, char ***av, char *optstr)
{
	int i;
	int check;
	t_opt *optlst;
	t_opt *optmp;

	i = 1;
	optlst = NULL;
	optmp = NULL;
	while ((**av)[i] && (check = ft_check_opt((**av) + i, 1, optstr)) == 1 )
	{
		if (!optmp)
			optmp = ft_create_sopt((**av)[i], NULL);
		else
		{
			optmp->next = ft_create_sopt((**av)[i], NULL);
			optmp = optmp->next;
		}
		i++;
		if (!optlst)
			optlst = optmp;
	}
	if (check == 2)
		if (!optlst)
			optlst = ft_get_sopt_arg(ac, av, i);
		else
			optmp->next = ft_get_sopt_arg(ac, av, i);
	else if (!check)
		;//ft_perror
	return (optlst);
}

t_opt	*ft_getopt(int *ac, char ***av, char *optstr)
{
	static int avi = 0;
	t_opt		*tmp;

	tmp = NULL;
	if (!(*ac - 1))
		return (NULL);
	if (!avi)
	{
		(*ac)--;
		(*av)++;	
	}
	if ((**av)[0] == '-' && (**av)[1] == '-' && (**av)[2])
		tmp = ft_get_dopt(ac, av, optstr);
	else if ((**av)[0] == '-' && (**av)[1] == '-' && !(**av)[2])
		tmp = NULL;
	else if ((**av)[0] == '-' && (**av)[1])
		tmp = ft_get_sopt(ac, av, optstr);
	else
		return (NULL);
	(*ac)--;
	(*av)++;
	if (tmp)
		tmp->next = ft_getopt(ac, av, optstr);
	return (tmp);
}