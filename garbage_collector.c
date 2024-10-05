#include "minishell.h"

t_garbabe  **get_data(void)
{
    static t_garbabe *data = NULL;
    return (&data);
}
void    ft_free(void *ptr)
{
    t_garbabe **tracker;
    t_garbabe *tmp;
    
    tracker = get_data();
    tmp = *tracker;
    while(tmp)
    {
        if (tmp->content == ptr)
        {
            if (tmp->freed)
                return;
            free(tmp->content);
            tmp->freed = 1;
            return;
        }
        tmp = tmp->next;
    }

}
void    *ft_malloc(size_t len)
{
    void    *ptr;
    t_garbabe**tracker;
    t_garbabe *new;

    tracker = get_data();
    ptr = malloc(len);
    if (!ptr)
        return (NULL);
    new = ft_lstnew_plus(ptr);
    if (!new)
    {
        ft_free(ptr);
        return (NULL);
    }
    ft_listadd_back_plus(tracker, new);
    return (ptr);
}

void    erase_all(void)
{
    t_garbabe **tracker;
    t_garbabe *tmp;
    t_garbabe *temp;

    tracker = get_data();
    temp = *tracker;
    while (temp)
    {
        tmp = (temp)->next;
        if (!(temp->freed))
        {
            free((temp)->content);
            temp->freed = 1;
        }
        free(temp);
        temp = tmp;
    }
    *tracker = NULL;

}

void    ft_exitt(int n)
{
    erase_all();
    exit (n);
}

