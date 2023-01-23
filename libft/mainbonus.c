#include "libft.h"
#include <stdio.h>
/*void    tft_lstnew()
{
	printf("LSTNEW\n");
	t_list *lst;
	int i = 5;
	lst = ft_lstnew((void *)i);
	// printf("%i\n", lst->content);
	
}

void tft_lstadd_front()
{
	printf("LSTADDFRONT\n");
	t_list **lst;
	t_list *new;
	int i = 5;
	*lst = ft_lstnew(i);
	new = ft_lstnew(i);
	ft_lstadd_front(lst,new);
	printf("%i\n", (*lst)->content);
	printf("%i\n", new->content);
}
*/
void tft_lstsize()
{
	printf("LSTSIZE\n");
	//char s[] = "hi";
	t_list *lst1;
	t_list *lst2;
	t_list **lst;
	t_list *lstlast;

	lst = malloc(3 * sizeof(t_list *));
	lst1 = ft_lstnew("hallo");
	lst2 = ft_lstnew("du");
	lstlast = ft_lstnew("kuh");
	*lst = lst1;
	lst1->next = lst2;

	printf("node 1 %s\nnode 2 %s\n", (*lst)->content, lst2->content);

	printf("%d\n", ft_lstsize(lst1));
 
	printf("%s\n", ft_lstlast(lst1)->content);

}

void tft_lstaddback()
{
	printf("LSTADDBACK\n");
	t_list *node1;
	t_list *node2;
	t_list *new;
	t_list **begin;

	node1 = ft_lstnew("hallo");
	node2 = ft_lstnew(" du");
	new = ft_lstnew("kuh");
	*begin = malloc ((3) * sizeof(t_list *));
	*begin = node1;
	ft_lstadd_back(begin, node1);
	//ft_lstadd_back(begin, node1);
	//ft_lstadd_back(begin, node2);
	printf("last of the list: %s\n", ft_lstlast(*begin)->content);
}

int main ()
{
	//tft_lstnew();
	//tft_lstadd_front();
	tft_lstsize();
	tft_lstaddback();
	return (0);
}
