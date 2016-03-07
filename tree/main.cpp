#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <list>


struct Node;
typedef std::shared_ptr<Node> NodePtr;

struct Node {
    Node(int n, NodePtr p = nullptr, NodePtr l = nullptr, NodePtr r = nullptr)
            : num(n), parent(p), left(l), right(r) {}
    NodePtr left, right, parent;
    int num;
    void print() { std::cout << num << "\t";}
};

NodePtr create_node(int n, NodePtr p = nullptr, NodePtr l = nullptr, NodePtr r = nullptr)
{
    return std::make_shared<Node>(Node(n,p,l,r));
}

NodePtr createBST(std::vector<int> &v, int start, int end, NodePtr parent) {
    if(start > end)
        return nullptr;
    int mid = (start + end) / 2;
    NodePtr n = std::shared_ptr<Node>(new Node(v[mid]));
    n->parent = parent;
    n->left = createBST(v,start,mid-1,n);
    n->right = createBST(v,mid+1,end,n);
    return n;
}

void inorder(NodePtr node) {
    if(node) {
        if(node->left)
            inorder(node->left);
        node->print();
        if(node->right)
            inorder(node->right);
    }
}

void preorder(NodePtr node) {
    if(node) {
        node->print();
        if(node->left)
            preorder(node->left);
        if(node->right)
            preorder(node->right);
    }
}
void postorder(NodePtr node) {
    if(node) {
        if(node->left)
            postorder(node->left);
        if(node->right)
            postorder(node->right);
        node->print();
    }
}

bool check(NodePtr node) {

    bool l = true;
    bool r = true;

    if(node->left)
        if(node->num > node->left->num)
            l = check(node->left);
        else l = false;
    if(node->right)
        if(node->num <= node->right->num)
            r = check(node->right);
        else r = false;
    return l && r;
}

NodePtr next_successor(NodePtr node) {
    // 1.case - have right subtree;
    if(node->right) {
        node = node->right;
        while (node->left)
            node = node->left;
        return node;
    }
    // 2.case - is root;
    if(!node->parent) return nullptr;

    // 3.case - is left child
    if(node->parent->left == node)
        return node->parent;

    // 4.case - is right child
    NodePtr parent = node->parent;
    NodePtr right = node;
    while(parent && parent->right == right) {
        right = parent;
        parent = parent->parent;
    }

    // 5. is biggest
    if(!parent) return nullptr;

    return parent;
}

int getHeight(NodePtr node) {
    int h = 0;
    while(node->parent) {
        h++;
        node = node->parent;
    }
    return h;
}

NodePtr find_common_ancesstor(NodePtr node1, NodePtr node2) {
    int h1 = getHeight(node1);
    int h2 = getHeight(node2);
    if(h1 == 0 || h2 == 0)
        return nullptr;

    while(h1 > h2) {
        h1--;
        node1 = node1->parent;
    }
    while(h2 > h1) {
        h2--;
        node2 = node2->parent;
    }
    while(node2->parent != node1->parent) {
        node1 = node1->parent;
        node2 = node2->parent;
    }
    return node1->parent;

}

typedef std::queue<NodePtr> Path;
typedef std::list<Path> Paths;

void createPath(NodePtr node, int value, int sum, Path path, Paths &paths) {
    if(!node) return;

    path.push(node);
    sum += node->num;

    if(sum == value)
        paths.push_back(path);
    else if (sum > value) {
        while (sum > value) {
            sum -= path.front()->num;
            path.pop();
        }
        if (sum == value)
            paths.push_back(path);
    }
    createPath(node->left, value, sum, path, paths);
    createPath(node->right, value, sum, path, paths);
}

NodePtr find_equal(NodePtr node, int i) {
    if(i == node->num)
        return node;

    if(i < node->num)
        if(node->left)
            return find_equal(node->left, i);
        else return nullptr;

    if(node->right)
        return find_equal(node->right, i);
    return nullptr;
}

void test1(NodePtr root)
{
    std::cout << "SEARCH TREE: " << (check(root) ? "YES" : "NO") << std::endl;

    std::vector<NodePtr> cases(6);
    cases[0] = find_equal(root,3);
    cases[1] = root;
    cases[2] = find_equal(root,0);
    cases[3] = find_equal(root,11);
    cases[4] = find_equal(root,30);
    cases[5] = find_equal(root,9);

    std::cout << "CASES\n";
    for(auto case_ : cases)
        case_->print();

    std::cout << "\n";

    for(auto case_ :cases) {
        NodePtr s = next_successor(case_);
        if(s)
            std::cout << "Succesor of " << case_->num << " is " << s->num << "\n";
        else
            std::cout << "Succesor of " << case_->num << " not exist \n";

    }
    std::cout << "COMMON\n" ;
    find_common_ancesstor(cases[0],cases[2])->print();
    find_common_ancesstor(cases[0],cases[3])->print();
    find_common_ancesstor(cases[0],cases[5])->print();
    find_common_ancesstor(cases[2],cases[3])->print();
    find_common_ancesstor(cases[3],cases[5])->print();
    find_common_ancesstor(cases[5],cases[4])->print();
    if(find_common_ancesstor(cases[1],cases[0]) == nullptr)
        std::cout << "no common with root\n";


    for(int i = 10; i < 20; i++) {
        std::cout << "PATHS for value " << i << std::endl;
        Paths paths;
        Path path;
        createPath(root, i, 0, path, paths);
        for (Path &path_ : paths) {
            std::cout << "PATH: ";
            while (!path_.empty()) {
                NodePtr node = path_.front();
                path_.pop();
                std::cout << node->num << "\t";
            }
            std::cout << std::endl;
        }
    }
}

void preorder_array(NodePtr node, std::vector<int> &v)
{
    if(!node) {
        return;
    }

    v.push_back(node->num);
    preorder_array(node->left, v);
    preorder_array(node->right, v);
}

NodePtr find_right_leaf_position(int value, NodePtr current)
{
    if(!current) {
        throw std::logic_error("Empty tree");
    }

    NodePtr successor = current->parent;
    NodePtr temp = current;
    while(successor && successor->right && successor->right->num == temp->num) {
        temp = successor;
        successor = temp->parent;
    }
    if(!successor) {
        return current;
    }
    if(value < successor->num) {
        return current;
    }
    // value > successor->num
    return find_right_leaf_position(value, successor);
}

NodePtr tree_from_preorder(std::vector<int> array)
{
    if(array.empty()) {
        return nullptr;
    }

    int i = 0;
    NodePtr root = create_node(array[i++]);
    NodePtr node = root;
    while(i < array.size()) {
        if(array[i] == node->num) {
            i++;
            continue;
        }
        if(array[i] < node->num) {
            node->left = create_node(array[i++], node);
            node = node->left;
            continue;
        }
        // array[i] > node->num
        node = find_right_leaf_position(array[i], node);
        node->right = create_node(array[i++], node);
        node = node->right;
    }

    return root;
}

int main()
{

    std::vector<int> tree;
    for(int i = 0; i < 31; i++)
        tree.push_back(i);

    NodePtr root = createBST(tree,0,tree.size()-1,nullptr);
    std::cout << "PREORDER\n";
    std::vector<int> array;
    preorder_array(root, array);
    for(int e : array)
        std::cout << e << "\t";
    std::cout << std::endl;

    int i = 0;
    NodePtr node = tree_from_preorder(array);
    preorder(node);
    std::cout << std::endl;
    inorder(node);
    std::cout << std::endl;
    inorder(root);
    return 0;
}