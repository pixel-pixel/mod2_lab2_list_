#include <iostream>

using namespace std;

struct Rational{
    Rational(int u, int d) {
        up = u;
        down = d;
    }
    int up = 0;
    int down = 1;

    void add(Rational *n){
        up = up*n->down + n->up*down;
        down *= n->down;
    }
    void sub(Rational *n){
        up = up*n->down - n->up*down;
        down *= n->down;
    }
    void print(){
        cout << up << '/' << down << endl;
    }
};

struct Node{
    Node(Rational *n, Node* nxt){
        number = n;
        next = nxt;
    }
    Rational *number;
    Node* next;
};

struct List{

private:
    Node *head = nullptr;
    int size = 0;
    Rational *sum = new Rational(0, 1);

    Node* getNode(int index){
        Node *node = head;
        for(int i = 0; i < index; i++){
            node = node->next;
        }
        return node;
    }
public:
    void add(Rational n, int index){
        Node *node = head;
        if(size == 0 || index == 0){
            addFirst(n);
        }else if(index >= size){
            addLast(n);
        }else{
            for(int i = 1; i < index; i++){
                node = node->next;
            }
            node->next = new Node(new Rational(n.up, n.down), node->next);
            sum->add(&n);
            size++;
        }
    }
    void add(Rational n){
        addLast(n);
    }
    void addFirst(Rational n){
        head = new Node(new Rational(n.up, n.down), head);
        sum->add(&n);
        size++;
    }
    void addLast(Rational n){
        Node *node = head;

        if(size == 0){
            addFirst(n);
        }else{
            for(int i = 1; i < size; i++){
                node = node->next;
            }
            node->next = new Node(new Rational(n.up, n.down), head);
            sum->add(&n);
            size++;
        }
    }

    void remove(int index){
        Node *node = head;
        if(index < 0 || index >= size){
            cout << "EROR!" << endl;
        }else if(index == 0){
            removeFirst();
        }else if(index == size-1){
            removeLast();
        }else{
            for(int i = 1; i < index; i++){
                node = node->next;
            }
            sum->sub(node->next->number);
            node->next = node->next->next;
            size--;
        }
    }
    void remove(Rational *n){
        int index = getIndex(n);
        if(index >= 0) remove(index);
    }
    void removeFirst(){
        sum->sub(head->number);
        head = head->next;
        size--;
    }
    void removeLast(){
        sum->sub(getNode(size-1)->number);
        getNode(size-2)->next = head;
        size--;
    }
    void clear(){
        size = 0;
    }

    Rational get(int index){
        if(index >= size){
            cout << "EROR!" << endl;
        }

        Node *node = head;
        for(int i = 0; i < index; i++){
            node = node->next;
        }
        return *node->number;
    }
    Rational getFirst(){
        return get(0);
    }
    Rational getLast(){
        return get(size - 1);
    }

    bool equals(Rational *n1, Rational *n2){
        return (n1->up == n2->up && n1->down == n2->down);
    }
    int getIndex(Rational *n){
        Node *node = head;

        for(int i = 0; i < size; i++){
            if(equals(node->number, n)) return i;
            node = node->next;
        }
        return -1;
    }
    Rational getSum(){
        return *sum;
    }
    int getSize(){
        return size;
    }
};

Rational getNextByKantor(Rational n){
    Rational m(n.up, n.down);
    if(m.down == 1){
        m.down += m.up;
        m.up = 1;
    }else{
        m.up++;
        m.down--;
    }
    return m;
}

void fillInByKantor(List *l, int size){
    if(size <= 0) return;
    Rational n(1, 1);
    l->add(n);

    for(int i = 1; i < size; i++){
        l->add(getNextByKantor(l->getLast()));
    }
}

int main() {

    List list;

    fillInByKantor(&list, 20);
    for(int i = 0; i < list.getSize(); i++){
        list.get(i).print();
    }

    list.add(getNextByKantor(list.getLast()));
    for(int i = 0; i < list.getSize(); i++){
        list.get(i).print();
    }
    cout << list.getIndex(new Rational(3, 2)) << endl;
    list.remove(new Rational(3, 2));
    for(int i = 0; i < list.getSize(); i++){
        list.get(i).print();
    }
    list.getSum().print();
    return 0;
}
