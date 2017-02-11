//
//  DList.hpp
//  hw1
//
//  Created by Nien-Tai Ho on 2017/2/1.
//  Copyright © 2017年 NientaiHo. All rights reserved.
//

#ifndef DList_hpp
#define DList_hpp

#include <iostream>
#include <string>
#include <math.h>
#include "DebugW.hpp"                   // Debug
using namespace std;

class DList
{
private:
    struct Node
    {
        int value;
        Node* prev;
        Node* next;
    };
    Node* head;
    Node* tail;
    int digitsPerNode;
    int NodeCount;
    int mod;
public:
    
    bool isEmpty();
    void insertAtHead(int num);
    void insertAtTail(int num);
    
    void deleteAtHead();
    
    void setDigitsPerNode(int digit);
    int getDigitsPerNode();
    
    void setNodeCount();
    int getNodeCount();
    
    void setMod();
    
    void printList();
    void addTwoList(DList* listOne,DList* listTwo);
    void multiplyTwoList(DList* listOne,DList* listTwo);
    
    DList() : DList(1) {};                              // 1 digit per node
    DList(int dPerNode) : DList("0", dPerNode) {};      // default value = "0"
    DList(string num,int dPerNode);                     // default constructur
    ~DList();
};

#endif /* DList_hpp */
