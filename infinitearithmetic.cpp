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
#include <unistd.h>                     // getopt()
#include "DebugW.hpp"                   // Debug
#include "formula.hpp"
#include "DList.hpp"


OPT_FLAG optFlag;
Debug *dbg;             // Warning: should be created before DList

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

    // Retrieve other options (argv[2] and afterwards)
    int opt;
    while ( (opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
        case 'd': optFlag.debug = true;         break;
        case '?': /* Unknown option (ignore) */
        default : /* Do nothing */              break;
        } // End of switch(opt)
    } // End of while(opt)

    // using Debug class (DEFAULT_DEBUG_LEVEL), borrow 'opt'
    opt = (optFlag.debug ? DEBUG_LEVEL_INFO : DEBUG_LEVEL_DEBUG);
    dbg = new (std::nothrow) Debug(opt);
    if (!dbg) {
        cerr << "Unable to create Debug system!" << endl;
        return -ENOMEM;
    }

    *dbg << "Digits Per Node : " << digitsPerNode << endl;

    //get line input from file
    while (getline(ifs, line)){
        *dbg << "--- Parsing " << line << endl;

        Formula f(line);
	*dbg << "L-Value = " << f.getLValue() << endl;
	*dbg << "R-Value = " << f.getRValue() << endl;
	*dbg << "Operator= " << f.getOP() << endl;

	string num1 = f.getLValue();
	string num2 = f.getRValue();
	int fOP     = f.getOP();

        *dbg << "num1 = " << num1 << endl;
        *dbg << "num2 = " << num2 << endl;
	*dbg << "operation = " << fOP << endl;

        DList* listOne = new DList(num1,digitsPerNode);
        DList* listTwo = new DList(num2,digitsPerNode);
        DList* result = new DList(digitsPerNode);

        listOne->printList( dbg, "value 1" );
        listTwo->printList( dbg, "value 2" );
        result->printList( dbg, "result" );

        //addition operation here
	if (fOP == MATH_ADD)
        {
            result->addTwoList(listOne, listTwo);
        }
        //multiplication operation here
	else if (fOP == MATH_MUL)
        {
            result->multiplyTwoList(listOne, listTwo);
        }
        result->printList( dbg, "result" );	// Debug

        cout << num1 << f.getOPChar() << num2 << "=";
        result->printList();
    }
    cout << endl;

    delete dbg;

    return 0;
}
