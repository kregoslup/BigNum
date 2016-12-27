#pragma once
#include "ListBigNumElement.h"

class BigNumList {
	BigNumListElement *first;
	BigNumListElement *last;
public:
	static bool compare_values(const BigNumListElement&, const BigNumListElement&);
};