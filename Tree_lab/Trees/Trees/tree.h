#pragma once
#include "tree_element.h"
#include <list>
#include <iostream>

enum bypass_type {direct, reverse, symmetrical};

class tree
{
	/*!< The node of the tree. */
	tree_element* node;

	/*!< Creates list of tree elements using direct bypass. */
	std::list<tree_element*>* fnDirect (tree_element* _node)
	{
		static std::list<tree_element*> DirectList; /*!< List of pointers according direct bypass. */
		DirectList.push_back(_node); /*!< Add node. */
		for (std::list<tree_element*>::iterator i = _node->sons.begin(); i != _node->sons.end(); ++i)	 /*!< Recursion for every child. */	
			fnDirect(*i);
		return &DirectList; /*!< Return list. */
	}

	/*!< Creates list of tree elements using reverse bypass. */
	std::list<tree_element*>* fnReverse (tree_element* _node)
	{
		static std::list<tree_element*> ReverseList; /*!< List of pointers according reverse bypass. */		
		for (std::list<tree_element*>::iterator i = _node->sons.begin(); i != _node->sons.end(); ++i)	 /*!< Recursion for every child. */	
			fnReverse(*i);
		ReverseList.push_back(_node); /*!< Add node. */
		return &ReverseList; /*!< Return list. */
	}

	/*!< Creates list of tree elements using symmetrical bypass. */
	std::list<tree_element*>* fnSymmetrical (tree_element* _node)
	{
		static std::list<tree_element*> SymmetricalList;
		if (_node->sons.empty())	 /*!< If there's no sons -> just add node. */
		{
			SymmetricalList.push_back(_node);
			return &SymmetricalList;
		}
		fnSymmetrical(_node->sons.front()); /*!< Add first son. */
		SymmetricalList.push_back(_node); /*!< Add node. */
		std::list<tree_element*>::iterator i = _node->sons.begin();
		++i; /*!< Set iterator on the second element. */
		for (; i != _node->sons.end(); ++i)	/*!< Recursion for every child starts from the second one. */
			fnSymmetrical(*i);
		return &SymmetricalList;
	}
public:
	/*!< Construstor without parameters. */
	tree(void): node(0){};

	/*!< Construstor which creates node. */
	tree(int val)
	{
		node = new tree_element;
		node->value = val;
	}

	/*!< Getting element using index. */
	/*!
      \param index -  the number of searched element.
	  \return The pointer on the searched element
    */
	tree_element* fnGetElem (int index)
	{
		std::list<tree_element*>* dirList = fnDirect(node); /*!< Getting list of the basic tree direct bypass. */
		std::list<tree_element*>::iterator i = dirList->begin();
		tree_element* tmp;
		std::advance(i, index-1); /*!< Getting element according the index. */
		tmp = *i; /*!< Save it. */
		dirList->clear(); /*!< Clear list for the next usage. */
		return tmp;
	}

	/*!< Getting element using index. */
	/*!
      \param index -  the number of searched element.
	  \return The data of the searched element
    */
	int fnGetVal (int index)
	{
		tree_element* elem = fnGetElem(index);
		return elem->value;
	}

	/*!< Creating the most right son of the element using index. */
	/*!
      \param index -  the number of the element.
	  \param _value -  The value of the son.
    */
	void fnCreateRightSon (int index, int _value)
	{
		if (node) /*!< If tree isn't empty. */
		{
			tree_element* parent = fnGetElem(index); /*!< We search parent. */
			tree_element* son = new tree_element; /*!< and create and append the new son. */
			son->value = _value;
			parent->sons.push_back(son);
		}
		else /*!< If tree's empty -> just create node with _value parameter. */
		{
			node = new tree_element;
			node->value = _value;
		}
	}

	/*!< Printing the tree according bypass. */
	void fnPrint (bypass_type bypass)
	{
		std::list<tree_element*>* List;

		/*!< Bypass selection. */
		if(bypass == direct)
		{
			List = fnDirect(node);
		}
		else if (bypass == reverse)
		{
			List = fnReverse(node);
		}
		else if (bypass == symmetrical)
		{
			List = fnSymmetrical(node);
		}

		/*!< Printing out of the List. */
		for (std::list<tree_element*>::iterator i = List->begin(); i != List->end(); ++i)
		{
			std::cout << " " << (*i)->value << " ";
		}
		List->clear();
	}
	~tree(void){};
};

