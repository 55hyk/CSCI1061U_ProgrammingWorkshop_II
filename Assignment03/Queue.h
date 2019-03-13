#ifndef __queue_h__
#define __queue_h__
#include <iostream>
#include <cstdlib>

using namespace std;

namespace Huang {
  template <typename T>
  struct Node {
    T data;
    Node *next;
  };

  template <typename U>
  class TQueue {
  public:
    TQueue(); //constructor
    ~TQueue(); //destructor
    void push(U d); //enqueues node onto top of TQueue
    U pop(); //dequeues bottom node off of TQueue
    bool isEmpty(); //checks if TQueue is empty
    void print(); //print contents of TQueue
    //from top to bottom
  private:
    Node<U> *top; //points to top node in TQueue
    Node<U> *bottom;
  };

  template <typename V>
  TQueue<V>::TQueue() {
    top = NULL;
    bottom = top;
  }

  template <typename V>
  TQueue<V>::~TQueue() {
    while (!isEmpty()){
      TQueue<V>::pop();
    }
  }

  template <typename V>
  void TQueue<V>::push(V d) {
    Node<V> *temp = new Node<V>;
    temp->data = d;
    temp->next = top;
    top = temp;
    Node<V> *current = top;
    while ((current->next) != NULL) {
      current = current->next;
    }
    bottom = current;
  }

  template <typename V>
  V TQueue<V>::pop() {
    if (isEmpty()) {
      cout << "ERROR: Can't pop from empty TQueue" << endl;
      exit(1);
    } else {
      V topValue = top->data;
      Node<V> *oldBottom = bottom;
      Node<V> *current = top;
      if ((current->next) == NULL) {
        top = NULL;
        bottom = top;
      }
      while ((current->next) != NULL) {
        bottom = current;
        current = current->next;
      }
      // current->next = NULL;
      delete oldBottom;
      if (!isEmpty()) {
        bottom->next = NULL;
      }
      return topValue;
    }
    // return 0;  //comment out this line once you implement your function
  }

  template <typename V>
  bool TQueue<V>::isEmpty() {
    return (top==NULL);
  }

  //Print TQueue from top to bottom
  template <typename V>
  void TQueue<V>::print() {
    if (isEmpty()) {
      cout << "NULL" << endl;
    } else {
      if (top->next == NULL) {
        cout << "[" << (top->data) << "]" << endl;
      } else {
        Node<V> *current = top;
        while (current != NULL) {
          cout << "[" << current->data << "] ";
          // if (current->next != NULL) {
          // }
          current = current->next;
        }
        cout << endl;
      }
    }
  }
}

#endif
