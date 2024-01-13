#pragma once
#include<iostream>
using namespace std;


template <class T>
class DoublyLinkList
{
	class Node
	{
		
		T data;
		Node* next;
		Node* prev;
	public:
		friend class DoublyLinkList<T>;
		Node()
		{
			data = 0;
			next = nullptr;
			prev = nullptr;
		}
		~Node()
		{
			next = nullptr;
			prev = nullptr;
		}
	};
private:
	Node* head = new Node;// dummy head
public:
	DoublyLinkList()
	{
		head->data = 0;
		head->next = nullptr;
		head->prev = nullptr;
	}
	DoublyLinkList(const DoublyLinkList& obj)
	{
		Node* curr = obj.head;
		while (curr != nullptr)
		{
			curr = curr->next;
		}
		while (curr->prev != obj.head)
		{
			this->Insert_at_Head(curr->data);
			curr = curr->prev;
		}
	}
	bool Insert_at_Head(T element)
	{
		if (head->next == nullptr)
		{
			Node* n = new Node;
			n->data = element;
			n->next = nullptr;
			n->prev = head;
			head->next = n;
			return true;
		}
		else
		{
			Node* n = new Node;
			n->data = element;
			head->next->prev = n;
			n->next = head->next;
			head->next = n;
			n->prev = head;
			return true;


		}
	}
	bool Delete_from_Head()
	{
		if (head->next == nullptr)
		{
			return false;//nothing to delete
		}
		else if (head->next->next == nullptr)  //if there is only one node
		{
			Node* n = head->next;
			head->next = nullptr;
			n->prev = nullptr;
			delete n;
			return true;
		}
		else
		{
			Node* n = head->next;
			head->next = n->next;
			n->next->prev = head;
			n->next = nullptr;
			n->prev = nullptr;
			delete n;
			return true;
		}
	}
	bool Delete_All(T element)
	{
		if (head == nullptr)
		{
			return false;
		}
		else
		{
			Node* n = head->next;
			while (n != nullptr)
			{
				if (n->data == element)
				{
					Node* n2 = n;
					n2->prev->next = n2->next;
					if(n2->next!=nullptr)
					n2->next->prev = n2->prev;
					n = n->next;
					n2->next = nullptr;
					n2->prev = nullptr;
					
					delete n2;
				}
				else 
				    n = n->next;
			}
			
			return true;
		}
	}
	bool Replace_All(T element1, T element2)
	{
		if (head->next == nullptr)
			return false;
		else
		{
			Node* n = head->next;
			while (n != nullptr)
			{
				if (n->data == element1)
					n->data = element2;
				n = n->next;

			}
			//if (n->data == element1) //for last node
			//	n->data = element2;

		}
	}
	bool Swap(T element1, T element2)
	{
		if (head->next == nullptr)
		{
			return false;
		}
		if (head->next->next == nullptr)
		{
			return false;
		}
		Node* n1=head->next;
		bool found1 = false;
		Node* n2=head->next;
		bool found2 = false;
		while (n1 != nullptr && !found1)
		{
			if (n1->data == element1)
			{
				found1 = true;
			}
			else
				n1 = n1->next;
		}
		while (n2 != nullptr && !found2)
		{
			if (n2->data == element2)
			{
				found2 = true;
			}
			else
				n2 = n2->next;
		}
		if (found1 && found2 != true)
			return false;
		else
		{
			

			
			n1->prev->next = n2;
			if (n1->next != n2)
			{
				n1->next->prev = n2;
				n2->prev->next = n1;
			}
			
			if(n2->next!=nullptr)
			   n2->next->prev = n1;

			if (n1->next != n2)
			{
				Node* temp = n1->next;
				n1->next = n2->next;
				n2->next = temp;

				temp = n1->prev;
				n1->prev = n2->prev;
				n2->prev = temp;
			}
			else
			{
				n1->next = n2->next;
				n2->next = n1;
				n2->prev = n1->prev;
				n1->prev = n2;
			}



			

			return true;
			


		}
		
	}
	void Print()//just for testing
	{
		Node* n = head->next;
		while (n != nullptr)
		{
			cout << n->data;
			n = n->next;
		}
		//cout << n->data;
		
	}  
	~DoublyLinkList()
	{
		Node* current = head;
		//current = head;
		while (current->next != nullptr)
		{
			current = current->next;
			delete head;
			head = current;
		}
		delete head;
	}
	class iterator
	{
		Node* current;
	public:
		friend class DoublyLinkList<T>;
		iterator(Node*start=nullptr)
		{
			current = start;
		}
		T& operator*() const
		{
			return current->data;
		}

		iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator l1(current);
			current = current->next;
			return l1;
		}
		iterator& operator--()
		{
			current = current->prev;
			return *this;
		}
		iterator operator--(int)
		{
			iterator lt(current);
			current = current->prev;
			return lt;
		}
		bool operator==(iterator& obj)
		{
			if (current == obj.current)
				return true;
			else
				return false;
		}
		bool operator!=(iterator& obj)
		{
			return !(*this == obj);
		}
	};
	 
	iterator Begin()
	{
		return head;
	}
	iterator End()
	{
		return nullptr;
	}
	
	
	bool Insert(iterator& obj, T element)
	{
		if (obj.current == nullptr)
			this->Insert_at_Head(element);
		else
		{
			Node* n = new Node;
			n->data = element;
			n->next = obj.current->next;
			n->prev = obj.current;
			if (obj.current->next != nullptr)
				obj.current->next->prev = n;
			obj.current->next = n;
		}
		
		return true;
	}
	bool Insert_Multiple(iterator& obj, T* arr, int size)  //if arr{1,2,3,4,5} then elements will also be inserted 
	{                                                     // in the same sequence in the list i.e (1,2,3,4,5)
		DoublyLinkList<T>* d = new DoublyLinkList<T>;
		for (int i = size-1; i >= 0; i--)
		{
			d->Insert_at_Head(arr[i]);
		}

		DoublyLinkList<T>::iterator x = d->Begin();
		x++;////
		for (int i = 0; i < size-1; i++)
			x++;

		d->head->next->prev = obj.current;
		if (obj.current->next != nullptr)
		x.current->next = obj.current->next;
		if(obj.current->next!=nullptr)
		  obj.current->next->prev = x.current;
		obj.current->next = d->head->next;  
		return true;

	}
	iterator& Delete(iterator obj) //after delteing returns the iterator to the next node
	{
		obj.current->prev->next = obj.current->next;
		if(obj.current->next !=nullptr)
		obj.current->next->prev = obj.current->prev;
		Node* n = obj.current;
		obj++;
		n->next = nullptr;
		n->prev = nullptr;
		delete n;
		return obj;
	}
	iterator& Delete_Multiple(iterator& obj, T* arr, int size)
	{                                      
		for (int i = 0; i < size; i++)
		{
			if(*obj== arr[i])
			   obj=this->Delete(obj);
			else
			{
				cout << arr[i] << "not found\n";
				break;
			}
			
		}
		return obj;
	} 
	bool Delete_Range(iterator& obj1, iterator& obj2)
	{
		
		obj1++;
		
		while (obj1 != obj2)
		{
			obj1 = this->Delete(obj1);
		}
		return true;
	}
	iterator& Search_First(T* element,int size)
	{
		DoublyLinkList<T>::iterator it = this->Begin();
		DoublyLinkList<T>::iterator end = this->End();
		it++;
		DoublyLinkList<T>::iterator x;
		int i = 0;
		bool found = false;
		
		while (it!=end  &&  !found )
		{
			if (*it == element[i])
			{
				x = it;
				int j = 0;
					while (j < size)
					{
						if (*it == element[j])
							it++;
						else
							break;
						j++;
				    }
					if (j == size )
						found = true;
					if (j != size - 1)
						j = 0;
				    
			}
			else
				it++;
		}
		
		return x;
	}
	bool Search_all(T *element,int size, DoublyLinkList<iterator> & obj)
	{

		
		DoublyLinkList<T>::iterator it = this->Begin();
		DoublyLinkList<T>::iterator end = this->End();
		it++;
		DoublyLinkList<T>::iterator x=this->Begin();
		x++;
		int i = 0;
		bool found = false;
		while (it != end)
		{
			i = 0;
			found = false;
			//it = this->Begin();
			while (it != end && !found)
			{
				if (*it == element[i])
				{
					x = it;
					int j = 0;
					while (j < size)
					{
						if (*it == element[j])
							it++;
						else
							break;
						j++;
						if (it == end)
							break;
					}
					if (j == size)
						found = true;
					if (j != size - 1)
						j = 0;

				}
				else
					it++;
				if (found)
				{
					obj.Insert_at_Head(x);
				}
			}

			//x++;
		}
		return true;
		/*Node* n = head->next;
		size = 0;
		while (n != nullptr)
		{
			if (n->data == element)
				size++;
			n = n->next;
		}
		if (size == 0)
			return false;
		else
		{
			arr = new iterator[size];
			int count = 0;
			n = head->next;
			while (n != nullptr)
			{
				if (n->data == element)
				{
					arr[count].current = n;
					count++;
				}
				n = n->next;
			}
			return true;
		}*/

	}

};