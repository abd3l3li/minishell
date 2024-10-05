#include "minishell.h"

t_list	*ft_listnew(char *content, int len, int type)
{
	t_list	*new;
    char    *sub;

	new = (t_list *)ft_malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_substr(content, 0, len);;
	if (!new->content)
        return (NULL);
	new->next = NULL;
    new->type = type;
	return (new);
}

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_garbabe 	*ft_lstnew_plus(void *content)
{
	t_garbabe 	*new;

	new = (t_garbabe  *)malloc(sizeof(t_garbabe));
	if (!new)
		return (NULL);
	new->content = content;
	new->freed = 0;
	new->next = NULL;
	return (new);
}

void	ft_listadd_back_plus(t_garbabe	**lst, t_garbabe	*new)
{
	t_garbabe	*temp;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}