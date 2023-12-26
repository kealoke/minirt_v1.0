#include "minirt.h"

// t_objects のノードを新しく作成する
// 1: void *content -> ノードのコンテント　
t_objects *objnew(void *content){
  t_objects *new_node;

  new_node = my_malloc(sizeof(t_objects));
  new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

int get_obj_size(t_objects *list){

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