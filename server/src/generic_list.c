/*
** simple_list.c for Ex00 in /home/fillon_g/tek2/piscine/piscine_cpp_d02a/ex00
**
** Made by guillaume fillon
** Login   <fillon_g@epitech.net>
**
** Started on  Thu Jan  9 14:22:00 2014 guillaume fillon
** Last update Tue Jul  1 18:29:59 2014 guillaume fillon
*/

#include <stdlib.h>
#include <stdio.h>

#include "generic_list.h"

unsigned int list_get_size(t_list list)
{
  unsigned int count = 0;
  t_node *tmp;

  tmp = list;
  if (tmp == NULL)
    return 0;
  while (tmp != NULL)
    {
      ++count;
      tmp = tmp->next;
    }
  return count;
}

t_bool list_is_empty(t_list list)
{
  if (list_get_size(list) == 0)
    return true;
  return false;
}

void list_dump(t_list list, t_value_displayer val_disp)
{
  t_node *tmp;

  tmp = list;
  while (tmp != NULL)
    {
      val_disp(tmp->value);
      tmp = tmp->next;
    }
}

t_bool list_add_elem_at_front(t_list *front_ptr, void *elem)
{
  t_node *new_node;

  if ((new_node = malloc(sizeof(t_node))) == NULL)
    return false;
  new_node->value = elem;
  new_node->next = *front_ptr;
  *front_ptr = new_node;
  return true;
}

t_bool  list_add_elem_at_back(t_list *front_ptr, void *elem)
{
  t_node *new_node = NULL;
  t_node *tmp = NULL;

  if ((new_node = malloc(sizeof(t_node))) == NULL)
    return false;
  new_node->value = elem;
  new_node->next = NULL;

  if (*front_ptr != NULL)
    {
      for (tmp = *front_ptr; tmp->next != NULL; tmp = tmp->next);
      tmp->next = new_node;
    }
  else
    *front_ptr = new_node;

  return true;
}

t_bool list_add_elem_at_position(t_list *front_ptr, void *elem,
				 unsigned int position)
{
  unsigned int i = 0;
  unsigned int lsize;
  t_node *new_node = NULL;
  t_node *tmp = NULL;

  lsize = list_get_size(*front_ptr);
  if (position > lsize)
    return false;
  if (position == 0)
    return (list_add_elem_at_front(front_ptr, elem));
  if (position == lsize)
    return (list_add_elem_at_back(front_ptr, elem));
  if ((new_node = malloc(sizeof(t_node))) == NULL)
    return false;

  tmp = *front_ptr;
  if (tmp != NULL)
    {
      while (i < position)
	{
	  tmp = tmp->next;
	  ++i;
	}
      new_node->value = elem;
      new_node->next = tmp->next;
      tmp->next = new_node;
    }
  return true;
}

t_bool list_del_elem_at_front(t_list *front_ptr)
{
  t_node *node_tofree;

  if (list_is_empty(*front_ptr) == true)
    return false;
  if (*front_ptr != NULL)
    {
      node_tofree = *front_ptr;
      *front_ptr = node_tofree->next;
      free(node_tofree);
    }
  return true;
}

t_bool list_del_elem_at_back(t_list *front_ptr)
{
  t_node *tmp;
  t_node *node_tofree;

  if (list_is_empty(*front_ptr) == true)
    return false;
  tmp = *front_ptr;
  if (tmp == NULL)
    return true;
  if (tmp->next == NULL)
    {
      free(tmp);
      *front_ptr = NULL;
      return true;
    }
  while (tmp->next->next != NULL)
    tmp = tmp->next;
  node_tofree = tmp->next;
  tmp->next = NULL;
  free(node_tofree);
  return true;
}

t_bool list_del_elem_at_position(t_list *front_ptr, unsigned int position)
{
  unsigned int i = 0;
  unsigned int lsize;
  t_node *tmp;
  t_node *node_tofree;

  lsize = list_get_size(*front_ptr);
  if (position > lsize)
    return false;
  if (position == 0)
    return (list_del_elem_at_front(front_ptr));
  if (position == lsize)
    return (list_del_elem_at_back(front_ptr));
  tmp = *front_ptr;
  if (tmp != NULL)
    {
      while (i < position - 1)
	{
	  tmp = tmp->next;
	  node_tofree = tmp->next;
	  ++i;
	}
      node_tofree = tmp->next;
      tmp->next = tmp->next->next;
      free(node_tofree);
    }
  return true;
}

t_bool		list_del_node(t_list *front_ptr, void *data)
{
  unsigned int	i;
  t_node	*tmp;

  i = 0;
  for (tmp = *front_ptr; tmp != NULL; tmp = tmp->next)
    {
      if (data == tmp->value)
	return (list_del_elem_at_position(front_ptr, i));
      ++i;
    }
  return (false);
}

void *list_get_elem_at_front(t_list list)
{
  if (list_is_empty(list) == true && list == NULL)
    return NULL;
  return list->value;
}

void *list_get_elem_at_back(t_list list)
{
  t_node *tmp;

  if (list_is_empty(list) == true && list == NULL)
    return NULL;
  for (tmp = list; tmp->next != NULL; tmp = tmp->next);
  return tmp->value;
}

void *list_get_elem_at_position(t_list list, unsigned int position)
{
  t_node *node;
  unsigned int i = 0;

  if (list_is_empty(list) == true)
    return NULL;
  if (position == 0)
    return list_get_elem_at_front(list);
  if (position == list_get_size(list))
    return list_get_elem_at_back(list);
  node = list;
  while (i < position)
    {
      node = node->next;
      ++i;
    }
  return node->value;
}

t_node *list_get_first_node_with_value(t_list list, void *value, t_value_comparator val_comp)
{
  t_node *tmp = NULL;

  tmp = list;
  while (tmp != NULL)
    {
      if (val_comp(tmp->value, value) == 0)
	return (tmp);
      tmp = tmp->next;
    }
  return tmp;
}

void list_clear(t_list *front_ptr)
{
  t_node *tmp;

  tmp = *front_ptr;
  if (tmp->next != NULL)
    list_clear(&(tmp->next));
  free(*front_ptr);
  *front_ptr = NULL;
}
