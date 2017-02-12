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
        Node* prev;
        Node* next;
        string value;
    };
    Node* pHead;
//    Node* pTail;

    int digitsPerNode;  // How many digits in one node
    int NodeCount;      // How many nodes in the list
    int mod;            // Multiply base (2 digits per node -> 100)

public:
    
    bool isEmpty();
    void insertAtHead(string num);
    void insertAtTail(string num);
    
    void deleteAtHead();
    
    void setDigitsPerNode(int digit);
    int getDigitsPerNode();
    
//    void setNodeCount();
    int getNodeCount();
    
    void setMod();
    
    void printList();
    void printList( Debug *dbg, string prompt );

    void addTwoList(DList* listOne,DList* listTwo);
    void multiplyTwoList(DList* listOne,DList* listTwo);
    
    DList() : DList(1) {};                              // 1 digit per node
    DList(int dPerNode) : DList("", dPerNode) {}        // Specific for result (no list created)
    DList(string num, int dPerNode);                    // default constructur
    ~DList();
};

#endif /* DList_hpp */
