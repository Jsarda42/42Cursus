/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:42:56 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/10 10:59:56 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_game(t_game *game)
{
	free_all(game);
	exit(EXIT_SUCCESS);
}

int	victory(t_game *game)
{
	free_all(game);
	ft_printf("\n\
BBBBB    RRRRR       A    V       V   OOOOO\n\
B    B   R    R    A  A    V     V   O     O\n\
BBBBB    RRRRR    AAAAAA    V   V    O     O\n\
B    B   R   R    A    A     V V     O     O\n\
BBBBB    R    R   A    A      V       OOOOO\n\
");
	exit (EXIT_SUCCESS);
}
