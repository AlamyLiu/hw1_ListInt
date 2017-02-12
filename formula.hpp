/*
 * License
 */

#ifndef _FORMULA_HPP_
#define _FORMULA_HPP_

#include <iostream>
#include <string>
#include <regex>

enum MATH_OPERATOR {MATH_ADD, MATH_SUB, MATH_MUL, MATH_DIV, MATH_SQRT};

class Formula
{
private:
//	const string OPStr[5] = {"+", "-", "*", "/", "sqrt"};
	const string OPChar = "+-*/s";

	string	lValue;		// left operand
	string	rValue;		// right operand
	int	op;		// MATH_OPERATOR

	int f_regex(const std::string& f) {
	try {
//		std::regex fmt( "([[:digit:]])([+-*/])([[::digit]])" );
//		std::regex fmt( "(0)(\\*)(0)" );
//		std::regex fmt( "0\D0" );
//		regex fmt( "(\d+)(\D+)(\d+)" );
//		regex fmt( "\s*" );	// good
//		regex fmt( "(\d+)" );
//		regex fmt( "[a-z|*]+" );
		regex fmt( "(.*)" );	// good
//		regex fmt( "(\d+)" );

		smatch match;

		if (! regex_match(f, match, fmt)) {
			cerr << "Wrong math format!" << endl;
			cerr << "match size = " << match.size() << endl;
			return -1;
		}
		if (match.size() < 3) {
			cerr << "Wrong math number! (" << match.size() << ")" << endl;
			for (int i = 0; i < match.size(); i++)
				cout << match[i].str() << endl;
			return -1;
		}
		lValue = match[0].str();
		rValue = match[2].str();

	} catch (std::regex_error &e) {
			if (e.code() == std::regex_constants::error_badrepeat)
				cerr << "Repeat was not preceded by a valid regex" << endl;
			else
				cerr << "Some other regex exception" << endl;
			cerr << "Err code = " << e.code() << endl;
			return -1;
	}
#if 0
		string c = match[1].str();

		switch (c[0]) {
		case '+': op = MATH_ADD;	break;
		case '-': op = MATH_SUB;	break;
		case '*': op = MATH_MUL;	break;
		case '/': op = MATH_DIV;	break;
		default: cout << "Unknown OP: " << c << endl;	break;
		}
#endif
		return 0;
	};

	int f_simple(const std::string& f) {
		string str_digits ("0123456789");
		string str_ops ("+-*/");

		size_t pLValue = f.find_first_of( str_digits );
		if (pLValue == std::string::npos) {
			cerr << "Wrong format: No L-Value" << endl;
			return -1;
		}

		size_t pOP     = f.find_first_of( str_ops, pLValue+1 );
		if (pOP == std::string::npos) {
			cerr << "Wrong format: No OP" << endl;
			return -1;
		}

		size_t pRValue = f.find_first_of( str_digits, pOP+1 );
		if (pRValue == std::string::npos) {
			cerr << "Wrong format: No R-Value" << endl;
			return -1;
		}

		size_t pEOS = f.find_first_not_of( str_digits, pRValue+1 );

		lValue = f.substr(pLValue, pOP-pLValue);
		
		rValue = (pEOS == std::string::npos)
			? f.substr(pRValue)
			: f.substr(pRValue, pEOS-pRValue);

		char c = f.at(pOP);
		switch (c) {
		case '+': op = MATH_ADD;	break;
		case '-': op = MATH_SUB;	break;
		case '*': op = MATH_MUL;	break;
		case '/': op = MATH_DIV;	break;
		default: cout << "Unknown OP: " << c << endl;	break;
		}

	};

public:
#if 0
	Formula() {
		operand0 = 0;
		operand1 = 0;
		op = MATH_ADD;
	};
#endif
	Formula(const std::string& f) {
		// f_regex(f);
		f_simple(f);
	};
	~Formula() {};

	int getLValueInt() {
		return stoi(lValue);
	};
	int getRValueInt() {
		return stoi(rValue);
	};
	int getOP() {
		return op;
	};
	string getLValue() {
		return lValue;
	}
	string getRValue() {
		return rValue;
	}

	char getOPChar() {
		return OPChar.at(op);
	}
};


#endif // _FORMULA_HPP_
