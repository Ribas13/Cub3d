/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:37:39 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 19:57:00 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* @brief Clears a given list
	@param lst The address of a pointer to the first link of a list
	@param del The address of a function to delete the content of the element
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*plzwork;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		plzwork = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = plzwork;
	}
	lst = NULL;
}
