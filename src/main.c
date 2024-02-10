/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:01:29 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/10 20:58:41 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* To do:

1. Finish map validation(gnl, etc)
2. Open window and draw map */

t_data	*ft_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->map = malloc(sizeof(t_map));
	data->map->has_player = false;
	data->map->cols = 0;
	data->map->rows = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data);
	valid_map(ac, av);
	if (ft_strchr("10NSWE", 'N') == NULL)
		printf("NULL\n");
	else
		printf("found letter\n");
	printf("Hreeee\n");
}
