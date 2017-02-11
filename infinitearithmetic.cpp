//
//  infinitearithmetic.cpp
//  hw0
//
//  Created by Nien-Tai Ho on 2017/1/19.
//  Copyright © 2017年 NienTaiHo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
#include "DList.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: infinitearithmetic input=<filename>;digitsPerNode=<number>\n";
    }
    ArgumentManager am(argc, argv);
    string filename = am.get("input");
    int digitsPerNode = stoi(am.get("digitsPerNode"));
    ifstream ifs(filename.c_str());
    string line;
    
    //get line input from file
    while (getline(ifs, line)){
        
        string operation=" ";
        string num1=" ";
        string num2=" ";
        int operationIndex=0;
        //get string from stringstream
        //delimiter here + - * / to split string to two part
        for (int i=0; i<line.length(); i++) {
            if (ispunct(line[i])) {
                operationIndex = i;
            }
        }
        num1 = line.substr(0,operationIndex);
        num2 = line.substr(operationIndex+1);
        num2.erase(remove(num2.begin(),num2.end(),'\r'));
        operation = line[operationIndex];

        DList* listOne = new DList(num1,digitsPerNode);
        DList* listTwo = new DList(num2,digitsPerNode);
        DList* result = new DList(digitsPerNode);
        
        
        //addition operation here
        if(operation=="+")
        {
            cout << num1 << operation << num2 << "=";
            result->addTwoList(listOne, listTwo, result);
            result->printList();
            listOne->printList();
            listTwo->printList();
        }
        //multiplication operation here
        else if(operation=="*")
        {
            cout << num1 << operation << num2 << "=";
            result->multiplyTwoList(listOne, listTwo, result);
            result->printList();
        }
        
    }
    cout << endl;
    
    return 0;
}
