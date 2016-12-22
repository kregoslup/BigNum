// projekt_cpp1.cpp : Defines the entry point for the console application.
//
#define _DEBUG 
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "BigNum.h"
#include <iostream>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	BigNum l1;
	BigNum l2(9999);
	BigNum l3("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
	BigNum l4(l3);
	BigNum l5 = l4;
	BigNum l6(-987654);

	BigNum *l7 = new BigNum("-999999999999999999999999999999");
	BigNum *l8 = new BigNum(999999999999);

	std::cout << l1 << l2 << l3 << l4 << l5 << l6 << *l7;

	delete l7;

	l1 = l2;
	std::cout << l1;

	l1 += 23;
	
	l1 += l4;
	
	l2 -= l3;
	std::cout << l2;
	l3 *= l4;
	std::cout << l3;
	std::cout << l4;
	if (l4 == "23424") {
		l4 /= l5;
	}
	system("PAUSE");

	return 0;
}

