//
//  DList.cpp
//  hw1
//
//  Created by Nien-Tai Ho on 2017/2/1.
//  Copyright © 2017年 NientaiHo. All rights reserved.
//

#include <cmath>                        // abs()
#include "DList.hpp"


extern OPT_FLAG optFlag;
extern Debug *dbg;


bool DList::isEmpty()
{
    if(head==NULL)
        return true;
    else
        return false;
}

void DList::insertAtHead(int num)
{
    if (isEmpty()) {
        head = new Node();
        head->value = num;
        tail = head;
        NodeCount++;
    }
    else{
        Node* temp = new Node();
        temp->value = num;
        temp->next = head;
        head->prev = temp;
        head = temp;
        NodeCount++;
    }
}
void DList::insertAtTail(int num)
{
    if (isEmpty()) {
        head = new Node();
        head->value = num;
        tail = head;
        NodeCount++;
    }
    else{
        Node* temp = new Node();
        temp->value = num;
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        NodeCount++;
    }
}

void DList::deleteAtHead()
{
    if(!isEmpty())
    {
        Node* temp = head;
        head = head->next;
        head->prev = NULL;
        delete temp;
    }
}

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
        mod = 10*mod;
    }
}

void DList::printList()
{
    Node *temp = head;
    if(!isEmpty()){
    while (temp->next!=NULL) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << temp->value << endl;
    }
    else{
        cout << "Empty list" << endl;
    }
}

void DList::addTwoList(DList* listOne,DList* listTwo)
{
    
    //add diffSize ZeroNode
    if (listOne->getNodeCount() != listTwo->getNodeCount()) {
        //get difference in nodes
        int diff = abs(listOne->getNodeCount() - listTwo->getNodeCount());
        if (listOne->getNodeCount() > listTwo->getNodeCount()) {
            for (int i=0; i<diff; i++) {
                listTwo->insertAtHead(0);
            }
            
        }
        else if (listOne->getNodeCount() < listTwo->getNodeCount())
        {
            for (int i=0; i<diff; i++) {
                listOne->insertAtHead(0);
            }
        }
    }
    
    Node* tempL1 = listOne->tail;
    Node* tempL2 = listTwo->tail;
    
    //add sameSizeNode
    int carry = 0;
    int sum = 0;
    
        while(tempL1!=NULL||tempL2!=NULL||carry>0){
            
            int num1=0;
            int num2=0;
            
            if (tempL1!=NULL) {
                num1 = tempL1->value;
            }
            if (tempL2!=NULL) {
                num2 = tempL2->value;
            }
            
            //sum two list plus carryover
            sum = num1 + num2 + carry;
            
            //equal or over 10 carry = 1
            if(sum>=mod) {
                carry = sum/10;
                sum = sum%10;
            }
            //if not carry = 0
            else if(sum<mod){
                carry = 0;
            }
            
            this->insertAtHead(sum);
            if(tempL1!=NULL){
                tempL1 = tempL1->prev;
            }
            if(tempL2!=NULL){
                tempL2 = tempL2->prev;
            }
        }
        if (carry>0) {
            insertAtHead(carry);
        }

    
}

//ex L1:1-2-3-4-5-6
//   L2:2-5-9-3
//
void DList::multiplyTwoList(DList* listOne,DList* listTwo)
{
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
                
                sum = tempL2->value * tempL1->value + carry;
                if (sum>10) {
                    carry = sum/10;
                    sum = sum%10;
                }
                this->insertAtHead(sum);
        
            
                tempL1 = tempL1->prev;
            }
    }
    
}

DList::DList(string num,int dPerNode)
: NodeCount(0), digitsPerNode(dPerNode), mod(10)
{
    setMod();
    head = NULL;
    tail = head;
    int numberSplit;
    for (int i=0; i<num.length(); i+=digitsPerNode) {
        numberSplit = stoi(num.substr(i,digitsPerNode));
        insertAtTail(numberSplit);
    }
}
