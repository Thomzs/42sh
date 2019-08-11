/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libshutil.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:43:18 by thdelmas          #+#    #+#             */
/*   Updated: 2019/08/06 23:33:31 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H
# include "sh_env.h"

int	sh_basename(int ac, char **av, t_env **ev);
int	sh_false(int ac, char **av, t_env **ev);
int	sh_pwd(int ac, char **av, t_env **ev);
int	sh_rm(int ac, char **av, t_env **env);
int	sh_set(int ac, char **av, t_env **ev);
int	sh_cd(int ac, char **av, t_env **ev);
int	sh_true(int ac, char **av, t_env **ev);
int	sh_check_path(char *all_path, int *error);
int	sh_find_opt(char **av, int *i);
int	sh_error_rm_opt(char c);
int sh_are_you_sure(char *question);

#endif