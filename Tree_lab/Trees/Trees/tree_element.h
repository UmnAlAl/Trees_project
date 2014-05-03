#pragma once
#include <list>

//!  An element of a tree. 
struct tree_element
{
	int value; /*!< Some inf. */
	std::list<tree_element*> sons; /*!< List of pointers on sons. */
};

