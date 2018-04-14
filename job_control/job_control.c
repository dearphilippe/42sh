/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 23:50:39 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/14 10:39:54 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** //TODO:
** jobs: Display the current program that is executed from the list
** job control functions that returns true or/and false when program is successful
** Create a signal with the PID once it is suspended after command is running (bg, fg)
** Ctrl Z for suspend and Ctrl C kills the process with SIGINT
/*
