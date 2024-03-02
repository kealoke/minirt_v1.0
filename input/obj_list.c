/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushimom <yushimom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:32:25 by yushimom          #+#    #+#             */
/*   Updated: 2024/03/02 18:32:27 by yushimom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

// t_objects のノードを新しく作成する
// 1: void *content -> ノードのコンテント　
t_objects	*objnew(void *content)
{
	t_objects	*new_node;

	new_node = my_malloc(sizeof(t_objects));
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

//オブジェクトリストのサイズを取得する
int	get_obj_size(t_objects *list)
{
	int	count;

	count = 1;
	if (list == NULL)
		return (0);
	while (list->next != NULL)
	{
		count++;
		list = list->next;
	}
	return (count);
}

//オブジェクトリストの最後のノードを取得する
t_objects	*ob_lstlast(t_objects *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

//オブジェクトリストの末尾に新しくノードを追加する
void	ob_lstadd_back(t_objects **lst, t_objects *new)
{
	t_objects	*lst_last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		lst_last = ob_lstlast(*lst);
		lst_last->next = new;
	}
}
