#include "tree.h"
#include <list>
#include <iostream>

void main ()
{
	tree MyTree;
	int N, index, value;
	std::cout << "Type the number of elements: ";
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> index >> value;
		MyTree.fnCreateRightSon(index, value);
	}
	/*!< Printing tree in different ways. */
	std::cout << std::endl << "Tree in direct bypass: ";
	MyTree.fnPrint(direct);
	std::cout << std::endl << "Tree in reverse bypass: ";
	MyTree.fnPrint(reverse);
	std::cout << std::endl << "Tree in symmetrical bypass: ";
	MyTree.fnPrint(symmetrical);
	std::cout << std::endl;
	system("pause");
}