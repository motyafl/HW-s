#include <iostream>
#include <stdexcept>
#include <string>

class empty_list : public std::exception {
private:
	std::string message;
public:
	empty_list(const char* msg) : message{msg} {}
    	
	const char* what() const noexcept {
        	return message.c_str();
    	}
};

struct Node {
	int data;

	Node* prev;
	Node* next;

	Node(int value):data(value), prev(nullptr),next(nullptr){}
};

class DoubleLinkedList {

private:
	Node* head;
	Node* tail;

public:
	DoubleLinkedList() : head(nullptr), tail(nullptr){}

	void append(int value) {
		Node* newNode = new Node(value);

		if (!head) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	void remove(int pos) {
		Node* curr = head;
	
		if (head == tail and curr == nullptr) {
			throw empty_list("The list is empty");
		}

		for (int i = 0; i < pos; i++) {
			if (curr == nullptr)
				throw std::out_of_range("Index out of range");
			else
				curr = curr->next;
		}

		if (head == tail) {
			//curr = nullptr
			head = nullptr;
			tail = nullptr;
		}
	
		if (curr->next != nullptr) {
			curr->next->prev = curr->prev;
		}	

		if (curr->prev != nullptr) {
			curr->prev->next = curr->next;
		}

		if (curr == head and head != nullptr) {
			//head->next->prev = nullptr;
			head = head->next;
		}

		if (curr == tail and tail != nullptr) {
			//tail->prev->next = nullptr;
			tail = tail->prev;
		}
	
		delete curr;
	}

	const void display(){
		Node* current = head;
		if (current == nullptr)
			std::cout << "The list is empty";

		while (current) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}

};

	


int main() {
try {
	DoubleLinkedList list;

	list.append(1);
	list.append(2);
	list.append(3);

	list.remove(1);
	
	std::cout << "List content: ";
	list.display();
	return 0;
}

catch (const std::out_of_range& e) {
	std::cerr << "ERROR:" << e.what() << std::endl;
}

catch (const empty_list& e) {
	std::cerr << "ERROR:" << e.what() << std::endl;
}
}
