/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdelmas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 22:16:31 by thdelmas          #+#    #+#             */
/*   Updated: 2019/09/21 23:44:46 by thdelmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ENV_H
# define SH_ENV_H

# include "sh_types.h"

int			sh_isset(const char *key);
void		sh_set_pwd(void);
void		sh_print_env(void);
void		sh_fill_env(const char **env);
void		sh_set_env(const char *key, const char *value);
void		sh_set_value(const char *key, const char *value);
char		*sh_getev_value(const char *key);
t_env		*sh_getev(const char *key);
t_env		*sh_init_var(const char *key, const char *value);
t_env		*sh_setev(const char *key, const char *value);
const char	*sh_get_value(const char *key);
void		sh_unsetev(const char *key, t_env **env);
t_env		*sh_create_param(const char *key);
t_env		*sh_env_params(char **env);
void		sh_putparams(t_env *params);
int			sh_isset(const char *key);
void		sh_del_env(t_env *env);
void		sh_del_all_env(t_env *env);

#endif
