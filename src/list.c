#include "list.h"

#include <stdlib.h>

/*
 * Creates a new linked list node with the
 * data passed as a parameter. The next
 * pointer is set to NULL.
 */
t_list *ft_lstnew(void *data) {
  t_list *lst;

  if (!(lst = malloc(sizeof(t_list))))
    return (0);
  lst->data = data;
  lst->next = NULL;
  return (lst);
}

/*
 * Returns linked list's size in number of elements.
 */
int ft_lstsize(t_list *lst) {
  if (!lst)
    return (0);
  return (ft_lstsize(lst->next) + 1);
}

/*
**	Returns the last element
**	of the linked list lst.
*/
t_list *ft_lstlast(t_list *lst) {
  if (!lst)
    return (NULL);
  else if (!(lst->next))
    return (lst);
  return (ft_lstlast(lst->next));
};

/*
** Push new element to the linked list
** end, without changing its head.
*/
void ft_lstadd_back(t_list **lst, t_list *new) {
  if (!*lst)
    *lst = new;
  else
    ft_lstlast(*lst)->next = new;
}

/*
 * Adds the element 'new' at the beginning of the list.
 */
void ft_lstadd_front(t_list **lst, t_list *new) {
  new->next = *lst;
  *lst = new;
}

/*
** Deletes the content of a linked
** list node. The node may be passed
** by reference for test purposes.
*/
void ft_lstdelone(t_list *lst, void (*del)(void *)) {
  if (!del)
    return;
  del(lst->data);
  free(lst);
}

/*
** This function completely erases a linked
** list t_list with a delete function (*del),
** which deletes the content of the node. The
** head then returns as a NULL pointer.
*/
void ft_lstclear(t_list **lst, void (*del)(void *)) {
  if ((*lst)->next)
    ft_lstclear(&(*lst)->next, del);
  ft_lstdelone(*lst, del);
  *lst = NULL;
}

/*
** Iterates over all list elements,
** applying the f function to each
** element data.
*/
void ft_lstiter(t_list *lst, void (*f)(void *)) {
  if (lst) {
    f(lst->data);
    ft_lstiter(lst->next, f);
  }
}

/*
 * Iterates over the list 'lst' and applies
 * the function 'f' to each element.
 * Returns a new list with the results of the function 'f'.
 */
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)) {
  t_list *map;

  if (!lst)
    return (NULL);
  else {
    if (!(map = ft_lstnew(f(lst->data)))) {
      ft_lstclear(&map, del);
      return (NULL);
    }
    map->next = ft_lstmap(lst->next, f, del);
    return (map);
  }
}
