#include <iostream>

// Простая структура связного стека
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

	// Возвращает верхнее значение в стеке
	T Get()
	{
		return head->value;
	}
	// Возвращает значение _Idx-того элемента в стеке
	T Get(UINT _Idx)
	{
		return GetNode(_Idx)->value;
	}
	// Возвращает _Idx-й элемент в стеке
	Node* GetNode(UINT _Idx)
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
	T operator [] (UINT _Idx)
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
	void CmdOut(bool doEndl = 1, std::ostream& os = std::cout)
	{
		if (size() == 0)
		{
			os << "[ NIL ]" << (doEndl? "\n" : "");
			return;
		}
		Node* node = head;
		os << "[ ";
		while (node)
		{
			os << node->value << (node->next ? ", " : " ");
			node = node->next;
		}
		os << "]" << (doEndl ? "\n" : "");
	}
	friend ostream& operator << (ostream& os, LinkedStack& ls)
	{
		ls.CmdOut(1, os);
		return os;
	}
	friend ostream& operator << (ostream& os, LinkedStack* ls)
	{
		ls->CmdOut(1, os);
		return os;
	}
	// Меняет местами два элемента в стеке и индексами _a и _b
	void swap(UINT _a, UINT _b)
	{
		if (_a == _b) return;
		if (_a > _b)
		{
			UINT tmp = _a;
			_a = _b;
			_b = tmp;
		}
		if (_b - _a > 1)
		{
			if (_a == 0)
			{
				Node* np2 = GetNode(_b - 1);
				Node* n2 = np2->next;
				Node* nn2 = n2->next;

				n2->next = head->next;
				head->next = nn2;
				np2->next = head;
				head = n2;
			}
			else
			{
				Node* np1 = GetNode(_a - 1);
				Node* n1 = np1->next;
				Node* nn1 = n1->next;
				Node* np2 = GetNode(_b - 1);
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
				Node* np1 = GetNode(_a - 1);
				Node* n1 = np1->next;
				Node* n2 = GetNode(_b);
				Node* nn2 = n2->next;
				np1->next = n2;
				n2->next = n1;
				n1->next = nn2;
			}
		}
		else throw;
	}
	// Меняет направление элементов в стеке
	LinkedStack* reverse(void)
	{
		size_t sz = size();
		for (size_t i = 0; i < sz / 2; i++)
			swap(i, sz - i - 1);
		return this;
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
