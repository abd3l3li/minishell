#include "minishell.h"

t_list	*ft_lstnew(char *content, int len, int type)
{
	t_list	*new;
    char    *sub;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
    sub = ft_substr(content, 0, len);
    if (!sub)
        return (NULL);
	new->content = sub;
	new->next = NULL;
    new->type = type;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new || !new)
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