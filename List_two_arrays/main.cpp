#include "List.h"
#include <stdio.h>
#include <locale>

#define PATH "C:\\out.txt"

int main()
{
	setlocale(LC_ALL, "RUS");

	std::cout << "\nТестирование функционала: \n";
	List list1;
	List list2;

	List s;

	s.InsFirst(15);
	s.InsFirst(3);
	s.InsFirst(-2);
	s.InsFirst(0);
	s.InsFirst(0);
	s.InsFirst(0);
	s.InsFirst(11);
	s.InsFirst(6);
	s.InsFirst(9);
	s.InsLast(10101);

	std::cout << "Исходный список: \n";
	s.print();
	s.DelFirst();
	s.print();
	s.DelList();
	s.InsFirst(3);
	s.InsFirst(4);
	s.InsLast(5);
	s.InsLast(7);
	s.print();
	s.DelLast();
	s.print();
	s.InsValue(366, 2);
	s.print();


	list1.InsFirst(15);
	list1.InsFirst(9);
	list1.InsFirst(33);
	list1.InsFirst(66);

	list1.WriteFile(PATH);

	list2.ReadFile(PATH);
	list2.print();

	list2.InsFirst(1);
	list2.InsFirst(6);
	list2.InsFirst(7);
	list2.InsFirst(9);
	list2.InsFirst(2);
	list2.InsFirst(333);

	list1.print();

	list2.print();

	List find;
	find = *list2.findSpecialElements(3);
	find.print();

	return 0;
}