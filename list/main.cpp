#include <iostream>
#include <memory>
#include <stringprep.h>

class Node;
typedef std::shared_ptr<Node> node_ptr;
class Node {
public:
    std::shared_ptr<Node> next;
    int value;

    Node(int v) : value(v) { }

    void push_back(int v) {
        std::shared_ptr<Node> n = std::shared_ptr<Node>(new Node(v));

        if(!next) {
            next = n;
            return;
        }
        std::shared_ptr<Node> end = next;
        while (end->next)
           end = end->next;
        end->next = n;
    }

    friend bool operator< (Node &a, Node &b) {
        return a.value < b.value;
    }

    friend bool operator> (Node &a, Node &b) {
        return a.value > b.value;
    }

    friend bool operator== (Node &a, Node &b) {
        return a.value == b.value;
    }

    friend bool operator<= (Node &a, Node &b) {
        return a.value <= b.value;
    }

    friend bool operator>= (Node &a, Node &b) {
        return a.value >= b.value;
    }
};


void print(std::shared_ptr<Node> current) {
    std::cout << "PRINT" << std::endl;
    while(current) {
        std::cout << current->value << "\t";
        current = current->next;
    }
    std::cout << "\nEND" << std::endl;

}

void delete_node(std::shared_ptr<Node> node) {
    if(node->next) {
        node->value = node->next->value;
        node->next =  node->next->next;
        return;
    }
    std::cerr << "Cannot delete end of the list";
}

/*
 * not stable solution
 */
void partition(int value, node_ptr head) {
    node_ptr greater = head;
    node_ptr smaller = head;
    node_ptr node = node_ptr(new Node(value));

    while(greater && smaller) {
        while(greater && *greater < *node)
            greater = greater->next;
        if(!greater) break;
        smaller = greater;
        while(smaller && *node <= *smaller)
            smaller = smaller->next;
        if(!smaller) break;
        int temp = greater->value;
        greater->value = smaller->value;
        smaller->value = temp;
    }
}

node_ptr partition2(int val, node_ptr node) {

    if(!node->next)
        return node;

    node_ptr head = node;
    node_ptr tail = node;
    node_ptr x = node_ptr(new Node(val));

    node = node->next;

    while(node) {
        node_ptr next = node->next;
        if (node && *node < *x) {
            node->next = head;
            tail->next = next;
            head = node;
        } else {
            tail->next = node;
            tail = node;
        }
        node = next;
    }
    return head;
}

node_ptr suma(node_ptr& node1, node_ptr& node2, node_ptr& sum, int offset) {

    if(!node1 && !node2) {
        sum = node_ptr(new Node(offset));
        return sum;
    }

    int val = offset;
    if(!node1) {
        val += node2->value;
        sum = node_ptr(new Node(val % 10));
        suma(node1, node2->next, sum->next, (val - (val % 10))/10);
        return sum;
    }

    if(!node2) {
        val += node1->value;
        sum = node_ptr(new Node(val % 10));
        suma(node1->next, node2, sum->next, (val - (val % 10))/10);
        return sum;
    }

    val += node1->value + node2->value;
    sum = node_ptr(new Node(val % 10));
    suma(node1->next, node2->next, sum->next, (val - (val % 10))/10);
    return sum;
}

int reverse(node_ptr& node1, node_ptr& node2, node_ptr& sum) {

    if(!node1)
        return 0;

    sum = node_ptr(new Node(0));

    int offset = reverse(node1->next, node2->next, sum->next);

    int suma = node1->value + node2->value + offset;
    sum->value = suma % 10;
    return (suma - suma % 10)/10;
}

node_ptr sum_reverse(node_ptr node1, node_ptr node2, node_ptr& sum) {
    if(!node1 && !node2)
        return sum;
    if(!node1)
        return node2;
    if(!node2)
        return node1;

    node_ptr end1 = node1;
    node_ptr end2 = node2;
    int l1 = 1;
    int l2 = 1;

    while(end1->next) {
        end1 = end1->next;
        l1++;
    }

    while(end2->next) {
        end2 = end2->next;
        l2++;
    }

    while(l1 < l2) {
        node_ptr temp = node_ptr(new Node(0));
        temp->next = node1;
        node1 = temp;
        l1++;
    }

    while(l2 < l1) {
        node_ptr temp = node_ptr(new Node(0));
        temp->next = node2;
        node2 = temp;
        l2++;
    }

    int offset = reverse(node1, node2, sum);

    if(offset){
        node_ptr temp = node_ptr(new Node(offset));
        temp->next = sum;
        sum = temp;
    }
}

void test_delete_node(node_ptr head, node_ptr end){
    print(head);
    delete_node(head->next);
    print(head);
    delete_node(end);
}

void test_partition(node_ptr head){
    print(head);
    head = partition2(5, head);
    print(head);
}

void test_sum(node_ptr head1, node_ptr head2) {
    print(head1);
    print(head2);
    node_ptr head3, sum;
    head3 = suma(head1,head2,sum,0);
    print(head3);
}

void test_sum_reverse(node_ptr head1, node_ptr head2) {
    print(head1);
    print(head2);
    node_ptr sum;
    sum_reverse(head1,head2,sum);
    print(sum);
}

void init_list(node_ptr& head, node_ptr& end, int N) {
    head = node_ptr(new Node(5));
    node_ptr node = head;
    for(int i = 1 ; i < N; i++) {
        node->push_back(i+5);
        node = node->next;
    }
    end = node;
}

int main() {

    std::shared_ptr<Node> head1, end1, head2, end2;

    init_list(head1, end1, 2);
    init_list(head2, end2, 3);

    test_sum_reverse(head1, head2);
    //test_sum(head1,head2);
    //test_partition(head1);

    return 0;
}