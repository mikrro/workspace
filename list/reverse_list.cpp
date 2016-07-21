#include <iostream>

struct list {
    list *next;
    int data;

    list(int d) : data(d), next(NULL) {}
};

list *fill_list(int n)
{
    list *temp = new list(1);
    list *l = temp;
    for(int i = 2; i < n+1; i++) {
        temp->next = new list(i);
        temp = temp->next;
    }
    return l;
} 

void print_list(list *l) 
{
    list *temp = l;
    while(temp) {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}

void destroy_list(list *l)
{
    list *temp;

    while(l) {
        temp = l;
        l = l->next;
        delete(temp);
    }
}

list *find_prev(list *l, list *elem)
{
    list *temp = l;
    while(temp && temp->next && temp->next != elem)
        temp = temp->next;

    return temp;
}

bool exchange_with_next(list *l, list *elem)
{
    if (!l || !elem || !elem->next) return false;

    list *prev, *current, *next;
    current = elem; next = elem->next;
    prev = find_prev(l, elem);

    if (prev) {
        prev->next = next;
    } 

    current->next = next->next;
    current->next = next;

    return true;
}

list *reverse(list *l)
{
    list *next, *prev;

    prev = NULL;
    while(l) {
        next = l->next;
        l->next = prev;
        prev = l;
        l = next;
    }

    return prev;
}

int main() {

    list *l, *elem;
    l = fill_list(10);
    print_list(l);
    l = reverse(l);
    print_list(l);

    destroy_list(l);
    return 0;
}