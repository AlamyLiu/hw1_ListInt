//
//  DList.cpp
//  hw1
//
//  Created by Nien-Tai Ho on 2017/2/1.
//  Copyright © 2017年 NientaiHo. All rights reserved.
//

#include <cmath>                        // abs()
#include <algorithm>
#include <sstream>
#include <iomanip>
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

void DList::insertAtHead(int value)
{
    insertAtTail( value );
    pHead = pHead->prev;
}

void DList::insertAtTail(int value)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(digitsPerNode) << value;
    insertAtTail( ss.str() );
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

int DList::add(int value, int idx)
{
    Node *pNode;
    int nIdx;           // Index of Node
    int value1;         // value from the Node
    int value2;         // value from the added value
    int sum, carry;     // variables for '+' operation
    std::stringstream ss;

    *dbg << "Adding " << value << " to index " << idx;
    printList(dbg, "");

    // prevent empty list
    if (isEmpty())
        insertAtTail( 0 );

    // point to LSN (idx = 0), initiate variables
    pNode = pHead->prev;
    nIdx = 0;
    while (value) {

        if (nIdx == idx) {
            value1 = stoi(pNode->value);
            value2 = value % mod;

            sum = value1 + value2;

            // refine sum & carry values
            if (sum >= mod) {
                // equal or over: carry = 1
                // '-' operation is faster than "/" and "%"
                carry = 1;
                sum = sum - mod;
            } else {
                // if not carry = 0
                carry = 0;
            }

            // Restore the new value
            ss << std::setfill('0') << std::setw(digitsPerNode) << sum;
            pNode->value = ss.str();
            ss.str(std::string());      // MUST clear, or it carry on.

            // Re-calculate 'value' and 'idx' for next node
            value /= mod;
            value += carry;
            idx++;
        } // End of if (pIdx)

        // Need to extend the list ?
        if (value && (pNode == pHead))
            insertAtHead( 0 );

        // Advance to next node
        pNode = pNode->prev;
        nIdx++;
    } // End of while (value)

    *dbg << "Added";
    printList(dbg, "");

    return 0;
}

void DList::addTwoList(DList* listOne, DList* listTwo)
{
    // Point to LSN (Least significant Node): list should not be NULL
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

        this->insertAtHead( sum );

        // Moving to next node, or NULL if already at pHead
        pNode1 = pNode1 ? ((pNode1 == listOne->pHead) ? NULL : pNode1->prev) : NULL;
        pNode2 = pNode2 ? ((pNode2 == listTwo->pHead) ? NULL : pNode2->prev) : NULL;
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
    // list should not be NULL
    Node *pNode1, *pNode2;      // Iterator over listOne & listTwo

    // Node Index (0 based LSN)
    int nIdx1, nIdx2, nIdx;

    int value1, value2;         // Integer of pNode*->value
    int sum = 0;                // sum = value1 * value2 for each iteration

    // Loop over listOne (LSN to MSN)
    pNode1 = listOne->pHead;
    nIdx1 = -1;
    do {
        pNode1 = pNode1->prev;  // 1st iteration will be LSN
        nIdx1++;                // 1st nIdx1 == 0
        value1 = stoi(pNode1->value);

        // Loop over listTwo (LSN to MSN)
        pNode2 = listTwo->pHead;
        nIdx2 = -1;
        do {
            pNode2 = pNode2->prev;
            nIdx2++;

//	    *dbg << "node2: index=" << nIdx2 << ", value=" << pNode2->value << endl;

            value2 = stoi(pNode2->value);

            // Now the calculation
            sum = value1 * value2;
            nIdx = nIdx1 + nIdx2;

	    *dbg << "Mul: " << value1 << " * " << value2 << endl;

            // Add sum to nIdx node (LSN)
            this->add(sum, nIdx);

        } while (pNode2 != listTwo->pHead);
    } while (pNode1 != listOne->pHead);
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

        insertAtHead( node_value );
    }
}
