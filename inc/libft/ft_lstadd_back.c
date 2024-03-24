/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:56:19 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 19:55:54 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* @brief Appends an elemnent to the end of a list
	@param lst The address of a pointer to the first link of a list
	@param new The address of a pointer to the element to be added to the list
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*plzwork;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	plzwork = ft_lstlast(*lst);
	plzwork->next = new;
}
