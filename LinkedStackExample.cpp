#include <iostream>

template <class T>
struct LinkedStack
{
	typedef unsigned int UINT;

// Элемент стека
	struct Node
	{
		T value = T{};
		Node* next = nullptr;

		Node(T value, Node* next = nullptr) : value(value), next(next) { };
	};
// Указатель на вершину стека
	Node* head = nullptr;

// Возвращает _Idx-й элемент в стеке
	Node* Get(UINT _Idx)
	{
		UINT depth = 0;
		Node* node = head;
		while (true)
		{
			if (!node) throw std::out_of_range("fix ur life idiot");
			if (depth != _Idx) { node = node->next; depth++; }
			else return node;
		}
		return node;
	}
// Индексация, чтоб вместо Get
	Node* operator [] (UINT _Idx)
	{
		return Get(_Idx);
	}
// Добавляет в начало новый элемент, возвращает указатель на него
	Node* push(T _Val)
	{
		if (!head)
		{
			head = new Node(_Val);
			return head;
		}
		head = new Node(_Val, head);
		return head;
	}
// Удаляет первый элемент в стеке (0-й), возвращает его копию
	const Node pop()
	{
		if (head)
		{
			Node* tmp = head;
			Node result = *head;
			head = head->next;
			delete tmp;
			return result;
		}
		else throw std::out_of_range("fix ur life idiot");
	}
// Возвращает индекс первого найденного элемента в стеке
// со значением _Val
	const int find(T _Val)
	{
		UINT depth = 0;
		Node* node = head;
		while (true)
		{
			if (!node) return -1;
			else if (node->value == _Val) return depth;
			else { node = node->next; depth++; }
		}
	}
// Возвращает размер (кол-во эдементов) стека
	const UINT size()
	{
		UINT depth = 0;
		Node* node = head;
		while (node) { node = node->next; depth++; }
		return depth;
	}
// Выводит в консоль через ostream весь стек, як список в питоне
	void CmdOut(void)
	{
		Node* node = head;
		std::cout << "[ ";
		while (node)
		{
			std::cout << node->value << (node->next? ", " : " ");
			node = node->next;
		}
		std::cout << "]" << std::endl;
	}
// Меняет местами два элемента в стеке и индексами _a и _b
	void swap(UINT _a, UINT _b)
	{	
		if (_b - _a > 1)
		{
			if (_a == 0)
			{
				Node* np2 = Get(_b - 1);
				Node* n2 = np2->next;
				Node* nn2 = n2->next;

				n2->next = head->next;
				head->next = nn2;
				np2->next = head;
				head = n2;
			}
			else
			{
				Node* np1 = Get(_a - 1);
				Node* n1 = np1->next;
				Node* nn1 = n1->next;
				Node* np2 = Get(_b - 1);
				Node* n2 = np2->next;
				Node* nn2 = n2->next;
				np1->next = n2;
				n1->next = nn2;
				np2->next = n1;
				n2->next = nn1;
			}
		}
		else if (_b - _a == 1)
		{
			if (_a == 0)
			{
				Node* n2 = head->next;
				head->next = n2->next;
				n2->next = head;
				head = n2;
			}
			else
			{
				Node* np1 = Get(_a - 1);
				Node* n1 = np1->next;
				Node* n2 = Get(_b);
				Node* nn2 = n2->next;
				np1->next = n2;
				n2->next = n1;
				n1->next = nn2;
			}
		}
		else throw;
	}
// Меняет направление элементов
	void reverse(void)
	{
		size_t sz = size();
		for (size_t i = 0; i < sz / 2; i++)
			swap(i, sz - i - 1);
	}
// Простое "a = b" вызовет полное копирование, т.е. по факту a и b будут указывать на одни и те же значения,
// copy(куда?) вызовет заполнение "куда?" элементами с теми же значениями, что и в исходном стеке. 
// Главное чтобы типы совпадали. После заполнения необходимо развернуть стек, если вам не нужно - copy(куда?, 0);
	void copy(LinkedStack<T>& _Dest, bool doReverse = 1)
	{
		Node* node = head;
		while (node)
		{
			_Dest.push(node->value);
			node = node->next;
		}
		if (doReverse) _Dest.reverse();
	}
};

int main()
{
	LinkedStack<int> ls1, ls2;
	LinkedStack<double> ls3;

	std::cout << "Первый элемент стека ls1: " << ls1.push(69) << std::endl;

	//ls1.copy(ls3); Ошибка - разные типы элементов - int и double
	ls1.copy(ls2);  // стек ls2 заполнен теми же значениями, что и ls1
	
	return 0;
}
