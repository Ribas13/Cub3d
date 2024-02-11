/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:00:35 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/11 13:25:10 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

# define ALLOWED_CHARS "10NSWE"
# define PLAYER_CHARS "NSWE"

typedef struct s_map
{
	char		**map;
	bool		has_player;
	size_t		rows;
	size_t		cols;
}				t_map;

typedef struct s_data
{
	t_map		*map;
}				t_data;

//Prototypes

t_data	*ft_data(void);

//validate_input.c

void	valid_map(int ac, char **av);
void	errors(char *error_msg);
void	clean_all(t_data *data);

#endif