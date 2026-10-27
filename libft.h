#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
    void	*content;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(void *content);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void(*del)(void *));
t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
        void (*del)(void *));



#endif