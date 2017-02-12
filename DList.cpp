//
//  DList.cpp
//  hw1
//
//  Created by Nien-Tai Ho on 2017/2/1.
//  Copyright © 2017年 NientaiHo. All rights reserved.
//

#include <cmath>                        // abs()
#include <algorithm>
#include "DList.hpp"


extern OPT_FLAG optFlag;
extern Debug *dbg;


bool DList::isEmpty()
{
    return ((pHead == NULL) ? true : false);
}

/* Circular double linked-list */
void DList::insertAtHead(string num)
{
    insertAtTail( num );
    pHead = pHead->prev;
}

void DList::insertAtTail(string num)
{
    Node *pNode = new Node();
    pNode->value = num;

    if (isEmpty()) {
        pHead = pNode;
        pNode->prev = pNode;
        pNode->next = pNode;
    } else {
        Node* pTail = pHead->prev;

        pNode->prev = pTail;
        pNode->next = pHead;

        pTail->next = pNode;
        pHead->prev = pNode;
    }

    NodeCount++;
}

void DList::deleteAtHead()
{
    if (isEmpty())
        return;

    Node* pNode = pHead;

    pHead->prev->next = pHead->next;
    pHead->next->prev = pHead->prev;

    pHead = pHead->next;

    // Last one ?
    if (--NodeCount == 0) {
        pHead = NULL;
    }

    delete pNode;
}

/*
void DList::setNodeCount()
{
    
    if(head!=NULL){
    Node* temp = head;
    while(temp->next!=NULL)
    {
        NodeCount++;
        temp = temp->next;
    }
    NodeCount++;
    }
}
*/

int DList::getNodeCount()
{
    return NodeCount;
}

void DList::setDigitsPerNode(int digit)
{
    digitsPerNode = digit;
}

int DList::getDigitsPerNode()
{
    return digitsPerNode;
}

void DList::setMod()
{
    mod = 10;
    for (int i=1; i<digitsPerNode; i++) {
        mod = 10 * mod;
    }
}

void DList::printList()
{
    if (isEmpty()) {
        cout << "(Empty)" << endl;
        return;
    }

    Node* pNode = pHead;
    while (true) {
        cout << pNode->value;
        pNode = pNode->next;

        if (pNode == pHead)
            break;
    }
    cout << endl;
}

void DList::printList( Debug *dbg, string prompt )
{
    *dbg << prompt << ":";

    if (isEmpty()) {
        *dbg << "(Empty)" << endl;
        return;
    }

    *dbg << "node=" << NodeCount << "(" << digitsPerNode << "):";

    Node* pNode = pHead;
    while (true) {
        *dbg << pNode->value;
        pNode = pNode->next;

        if (pNode == pHead)
            break;
        else
            *dbg << ",";
    }
    *dbg << endl;
}

void DList::addTwoList(DList* listOne, DList* listTwo)
{
    // Point to LSB (list should not be NULL)
    Node *pNode1 = listOne->pHead->prev;
    Node *pNode2 = listTwo->pHead->prev;

    int value1, value2;         // Integer of pNode*->value
    int sum = 0;                // sum = value1 + value2 for each iteration
    int carry = 0;              // carry of each iteration


    do {
        // fetch value into integer
        // assume integer could hold it (32-bit)
        value1 = (pNode1 ? stoi(pNode1->value) : 0);
        value2 = (pNode2 ? stoi(pNode2->value) : 0);

        sum = value1 + value2 + carry;

        // calculate carry value
        if (sum >= mod) {
            // equal or over: carry = 1
            // '-' operation is faster than "/" and "%"
            carry = 1;
            sum = sum - mod;
        } else {
            // if not carry = 0
            carry = 0;
        }

        *dbg << "add: " << value1 << " + " << value2 << " : sum=" << sum << ", carry=" << carry << endl;

        this->insertAtHead( to_string(sum) );

        // Moving to next node, or NULL if already at pHead
        pNode1 = (pNode1 == listOne->pHead) ? NULL : pNode1->prev;
        pNode2 = (pNode2 == listTwo->pHead) ? NULL : pNode2->prev;
    } while (pNode1 || pNode2);

    if (carry) {
        insertAtHead( to_string(carry) );
    }

    // Remove leading "0"

}

//ex L1:1-2-3-4-5-6
//   L2:2-5-9-3
//
void DList::multiplyTwoList(DList* listOne,DList* listTwo)
{
#if 0
    Node* tempL1 = listOne->tail;
    Node* tempL2 = listTwo->tail;
    DList* hold = new DList(digitsPerNode);
    int sum=0;
    int carry=0;
    
        //List 1 > list 2
        if (listOne->getNodeCount() > listTwo->getNodeCount()) {
            //get node difference
            while (tempL1!=NULL) {

                int diff = abs(listOne->getNodeCount() - listTwo->getNodeCount());
                // L1 * L2 + carry
                
                sum = stoi(tempL2->value) * stoi(tempL1->value) + carry;
                if (sum>10) {
                    carry = sum/10;
                    sum = sum%10;
                }
                this->insertAtHead( to_string(sum) );
        
            
                tempL1 = tempL1->prev;
            }
    }
#endif
}

DList::DList(string num, int dPerNode)
: NodeCount(0), digitsPerNode(dPerNode), mod(10)
{
    setMod();
    pHead = NULL;

    // "result" list uses this
    if (num.empty())
        return;

    // Reverse the number, so it would be be aligned from LSN
    std::reverse(num.begin(), num.end());
    string node_value;

    for (int i=0; i<num.length(); i += digitsPerNode) {
        string node_value = num.substr(i, digitsPerNode);
        std::reverse(node_value.begin(), node_value.end());

        insertAtTail( node_value );
    }
}
