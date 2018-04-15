/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 17:24:17 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 15:02:24 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_title(void)
{
	ft_printf(STDOUT_FILENO, "******************");
	ft_printf(STDOUT_FILENO, "*                *");
	ft_printf(STDOUT_FILENO, "*    Help menu   *");
	ft_printf(STDOUT_FILENO, "*                *");
	ft_printf(STDOUT_FILENO, "******************");
}

void header_sh(void)
{
	ft_printf(STDOUT_FILENO, "	   @@@@@@@@     @@\n");
	ft_printf(STDOUT_FILENO, "	@@@                @@\n");
	ft_printf(STDOUT_FILENO, "	@@                   @\n");
	ft_printf(STDOUT_FILENO, "	@@                    @\n");
	ft_printf(STDOUT_FILENO, "	@                    @\n");
	ft_printf(STDOUT_FILENO, "  @			          @\n");
	ft_printf(STDOUT_FILENO, "   #@@	 @@@@        .@\n");
	ft_printf(STDOUT_FILENO, "		 @@@	 @       @@@@@\n");
	ft_printf(STDOUT_FILENO, "			      @      @@    @\'\n");
	ft_printf(STDOUT_FILENO, "			      @     @@      @\n");
	ft_printf(STDOUT_FILENO, "			      @     @@       @\n");
	ft_printf(STDOUT_FILENO, "                @    @@        @\n");
	ft_printf(STDOUT_FILENO, "@             @     @@        @\n");
	ft_printf(STDOUT_FILENO, " @@          @    @          @    /\n");
	ft_printf(STDOUT_FILENO, "  @@@   @@@@@    /'         /'  @@\n");
	ft_printf(STDOUT_FILENO, "	   @@@         @         @@@@\n");
}

void header_42(void)
{
	ft_printf(1, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	ft_printf(1, "@@@@@@@@@@@@@@@/        @@@@&       @         @\n");
	ft_printf(1, "@@@@@@@@@@@@@/        @@@@@@&     @@@         @\n");
	ft_printf(1, "@@@@@@@@@@@/        @@@@@@@@&   @@@@@         @\n");
	ft_printf(1, "@@@@@@@@@/        @@@@@@@@@@& @@@@@@@         @\n");
	ft_printf(1, "@@@@@@@/        @@@@@@@@@@@@@@@@@@@@(        @@\n");
	ft_printf(1, "@@@@@/        @@@@@@@@@@@@@@@@@@@@(        @@@@\n");
	ft_printf(1, "@@@/        @@@@@@@@@@@@@@@@@@@@(        @@@@@@\n");
	ft_printf(1, "@/        @@@@@@@@@@@@@@@@@@@@(        @@@@@@@@\n");
	ft_printf(1, "@       ,,,,,,,,,,,,,,,,,@@@&        @@@@@@@@@@\n");
	ft_printf(1, "@                        @@@&        @@@@@@/ @@\n");
	ft_printf(1, "@                        @@@&        @@@@*   @@\n");
	ft_printf(1, "@                        @@@&        @@.     @@\n");
	ft_printf(1, "@@@@@@@@@@@@@@@@,        @@@&        /       @@\n");
	ft_printf(1, "@@@@@@@@@@@@@@@@.        @@@@@@@@@@@@@@@@@@@@@@\n");
	ft_printf(1, "@@@@@@@@@@@@@@@@.        @@@@@@@@@@@@@@@@@@@@@@\n");
	ft_printf(1, "@@@@@@@@@@@@@@@@.        @@@@@@@@@@@@@@@@@@@@@@\n");
	ft_printf(1, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
