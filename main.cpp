#include <iostream>

using namespace std;

struct Node{
    Node(int n, Node* nxt){
        number = n;
        next = nxt;
    }
    int number;
    Node* next;
};

struct List{

private:
    Node *head;
    int size = 0;

    Node* getNode(int index){
        Node *node = head;
        for(int i = 0; i < index; i++){
            node = node->next;
        }
        return node;
    }
public:
    void add(int n, int index){
        Node *node = head;
        if(size == 0 || index == 0){
            addFirst(n);
        }else if(index >= size){
            addLast(n);
        }else{
            for(int i = 1; i < index; i++){
                node = node->next;
            }
            node->next = new Node(n, node->next);
            size++;
        }
    }
    void add(int n){
        addLast(n);
    }
    void addFirst(int n){
        head = new Node(n, head);
        size++;
    }
    void addLast(int n){
        Node *node = head;

        if(size == 0){
            addFirst(n);
        }else{
            for(int i = 1; i < size; i++){
                node = node->next;
            }
            node->next = new Node(n, head);
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
            node->next = node->next->next;
            size--;
        }
    }
    void removeFirst(){
        head = head->next;
        size--;
    }
    void removeLast(){
        getNode(size-2)->next = head;
        size--;
    }
    void clear(){
        size = 0;
    }

    int get(int index){
        if(index >= size){
            cout << "EROR!" << endl;
            return 0;
        }
        Node *node = head;
        for(int i = 0; i < index; i++){
            node = node->next;
        }
        return node->number;
    }
    int getFirst(){
        return get(0);
    }
    int getLast(){
        return get(size - 1);
    }
    int getSize(){
        return size;
    }
};

int main() {
    return 0;
}
