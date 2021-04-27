#include "Node.h"
#include "ListIterator.h"
#include <iostream>
#include <string>
#include <fstream>

class List
{
protected:
	Node* pFirst;
	Node* pLast;
	ListIterator it;
	int ListLen;
public:
	List();
	~List();

	int GetListLenght();		// Размер списка
	bool IsEmpty();				// Проверка на пустоту

	void InsFirst(int Val);		// Вставить в начало
	void InsLast(int Val);		// Вставить в конец

	void DelFirst();			// Удалить элемент в начале
	void DelLast();				// Удалить элемент в конце
	void DelList();				// Удалить список

	void InsValue(int Val, int pos);	// Вставить значение по позиции
	void DelValue(int pos);				// Удалить значение по позиции

	void print();						// Вывести список в консоль

	bool search(int data);				// Проверка есть ли элемент в списке
	int	 get(int pos);					// Получить значение по позиции
	bool IsSort();						// Проверка отсортирован ли список по возрастанию

	List* findSpecialElements(int K);	// Возвращает список в котором каждый элемент делится на цело на K

	void WriteFile(std::string path);	// Вывести список в файл
	void ReadFile (std::string path);	// Считать список с файла 
};


List::List()
{
	pFirst = nullptr;
	pLast = nullptr;
	ListLen = 0;
}


List::~List() { DelList(); }


int List::GetListLenght() { return ListLen; }


bool List::IsEmpty()
{
	if (ListLen == 0) { return true; }
	else { return false; }
}


void List::InsFirst(int Val)
{
	it.init(pFirst);
	if (!it.check_current())
	{
		pFirst = it.insert(Val);
		pLast = pFirst;
	}
	else
	{
		pFirst = it.insert(Val);
	}
	ListLen++;
}


void List::InsLast(int Val)
{
	it.init(pFirst);
	if (!it.check_current())
	{
		pFirst = it.insert(Val);
		pLast = pFirst;
	}
	else
	{
		Node* tmp = new Node(Val);
		pLast->Next = tmp;
		pLast = tmp;
	}
	ListLen++;
}


void List::DelFirst()
{
	it.init(pFirst);
	if (!it.check_current())
	{
		return;
	}
	if (pFirst == pLast)
	{
		delete pFirst;
		pFirst = nullptr;
		pLast = nullptr;
		ListLen--;
		return;
	}
	pFirst = it.del_cur(pFirst);
	ListLen--;
}


void List::DelLast()
{
	it.init(pFirst);
	if (!it.check_current())
	{
		return;
	}
	if (pFirst == pLast)
	{
		delete pFirst;
		pFirst = nullptr;
		pLast = nullptr;
		ListLen--;
		return;
	}
	
	Node* tmp = pFirst;
	while (tmp->Next->Next != nullptr)
	{
		tmp = tmp->Next;
	}
	delete tmp->Next;
	tmp->Next = nullptr;
	pLast = tmp;
}


void List::DelList()
{
	pFirst = nullptr;
	pLast = nullptr;
	ListLen = 0;
}


void List::InsValue(int Val, int pos)
{
	if (pos < 0)
	{
		return;
	}
	if (pos == 0)
	{
		InsFirst(Val);
		return;
	}
	if (pos >= ListLen)
	{
		InsLast(Val);
		return;
	}
	int count = 0;
	Node* tmp = pFirst;
	it.init(tmp);
	while (count != pos - 1)
	{
		it.go_next();
		count++;
	}
	Node* newNode = new Node(Val, tmp->Next);
	it.insert(Val);
	tmp->Next = newNode;
	ListLen++;
}


void List::DelValue(int pos)
{
	if (pos < 0 || pos >= ListLen)
	{
		return;
	}
	if (pos == 0)
	{
		DelFirst();
		return;
	}
	if (pos == ListLen - 1)
	{
		DelLast();
		return;
	}
	Node* tmp = pFirst;
	int count = 0;
	while (count != pos - 1)
	{
		tmp = tmp->Next;
		count++;
	}
	Node* tmp2 = tmp->Next->Next;
	delete tmp->Next;
	tmp->Next = tmp2;
	ListLen--;
}

void List::print()
{
	if (pFirst != nullptr)
	{
		Node* tmp = pFirst;
		while (tmp->Next != nullptr)
		{

			std::cout << tmp->data << "->";
			tmp = tmp->Next;
		}
		std::cout << tmp->data << "->";
	}
	std::cout << "List length - " << GetListLenght() << "\n";
}


bool List::search(int data)
{
	if (ListLen == 0)
	{
		return false;
	}
	if (ListLen == 1)
	{
		if (pFirst->data == data)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Node* tmp = pFirst;
	while (tmp->Next != nullptr)
	{
		if (tmp->data == data)
		{
			return true;
		}
		tmp = tmp->Next;
	}
	if (tmp->data == data)
	{
		return true;
	}
	return false;
}


int List::get(int pos)
{
	if (pos < 0 || pos >= ListLen)
	{
		throw std::out_of_range("Input error: invalide input value");
	}
	Node* tmp = pFirst;
	int count = 0;
	while (count != pos)
	{
		tmp = tmp->Next;
		count++;
	} 
	return tmp->data;

}

bool List::IsSort()
{
	for (int i = 0; i < ListLen - 1; i++)
	{
		if (get(i) > get(i + 1))
		{
			return false;
		}
	}
	return true;
}

/*
inline bool List::check_current()
{
	if (pFirst != nullptr)
	{
		return true;
	}
	else { return false; }
}

inline bool List::check_next()
{
	if (pFirst->Next != nullptr)
	{
		return true;
	}
	else { return false; }
}

inline Node* List::ins_next(int val)
{
	if (!check_current())
	{
		return new Node(val);
	}
	else
	{
		return new Node(val, pFirst);
	}
}
*/

inline List* List::findSpecialElements(int K)
{
	List* res = new List();
	if (pFirst != nullptr)
	{
		Node* tmp = pFirst;
		while (tmp->Next != nullptr)
		{
			if (tmp->data % K == 0)
			{
				res->InsFirst(tmp->data);
			}
			tmp = tmp->Next;
		}
		if (tmp->data % K == 0)
		{
			res->InsFirst(tmp->data);
		}
	}
	return res;
}

inline void List::WriteFile(std::string path)
{
	std::ofstream file(path, std::ios::trunc);
	if (file.is_open())
	{
		if (pFirst != nullptr)
		{
			Node* tmp = pFirst;
			while (tmp->Next != nullptr)
			{

				file << tmp->data << "->";
				tmp = tmp->Next;
			}
			file << tmp->data;
		}
	}
	else
	{
		std::cout << "Files is not open!\n";
	}
	file.close();
}

inline void List::ReadFile(std::string path)
{
	std::ifstream file(path, std::ios::in);
	if (file.is_open())
	{
		std::string buf;

		int val[250];
		int i_val = 0;
		std::string str;
		while (std::getline(file, buf))
		{
			for (int i = 0; i < buf.size(); i++)
			{
				if (buf[i] == '-' && buf[i + 1] == '>')
				{
					val[i_val] = std::atoi(str.c_str());
					InsLast(val[i_val]);
					i_val++;
					str.clear();
					i++;
					continue;
				}
				str += buf[i];
			}
			val[i_val] = std::atoi(str.c_str());
			InsLast(val[i_val]);
		}
	}
	else
	{
		std::cout << "Files is not open!\n";
	}
	file.close();
}

