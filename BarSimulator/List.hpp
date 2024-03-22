#pragma once

template <typename T>
class List {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& data) : data(data), next(nullptr) {
			// Nothing to do here
		}
	};
public:
	class iterator {
		friend class List;
	private:
		Node* curr;
		iterator(Node* curr) : curr(curr) {
			// Nothing to do here
		}
	public:
		iterator(const iterator& other) : curr(other.curr) {
			// Nothing to do here
		}
		iterator& operator++() {
			curr = curr->next;
			return *this;
		}
		T& operator*() {
			return curr->data;
		}
		bool operator==(const iterator& other) const {
			return curr == other.curr;
		}
		bool operator!=(const iterator& other) const {
			return !(this->operator==(other));
		}
	};
private:
	Node* head;
	Node* tail;

	void free();
	void copyFrom(iterator it);
public:
	List() : head(nullptr), tail(nullptr) {
		// Nothing to do here
	}
	List(const List& other) : head(nullptr), tail(nullptr) {
		copyFrom(iterator(other.head));
	}
	List& operator=(const List& other) {
		if (this != &other) {
			free();
			copyFrom(iterator(other.head));
		}
		return *this;
	}
	~List() {
		free();
	}

	bool empty() const { return head == nullptr; }
	T& front() { return head->data; }
	T& back() { return tail->data; }
	bool isValid(iterator it) const { return it.curr == nullptr ? false : true; }

	iterator insert(iterator pos, const T& data);
	iterator eraseNext(iterator pos);
	iterator pop_front();
	iterator push_front(const T& data);
	iterator push_back(const T& data);
	iterator begin() { return iterator(head); }
};

template<typename T>
inline void List<T>::free() {
	while (!empty()) {
		pop_front();
	}
}

template<typename T>
inline void List<T>::copyFrom(iterator it) {
	for (; it.curr != nullptr; ++it) {
		push_back(*it);
	}
}

template<typename T>
inline typename List<T>::iterator List<T>::insert(iterator pos, const T& data) {
	if (head == nullptr) {
		return push_front(data);
	}

	Node* node = new Node(data);

	if (pos.curr == tail) {
		tail = node;
	}

	node->next = pos.curr->next;
	pos.curr->next = node;

	return iterator(node);
}

template<typename T>
inline typename List<T>::iterator List<T>::eraseNext(iterator pos) {
	if (pos.curr->next == nullptr) {
		return iterator(nullptr);
	}

	Node* nextNode = pos.curr->next;
	pos.curr->next = pos.curr->next->next;
	delete nextNode;

	return iterator(pos.curr->next);
}


template<typename T>
inline typename List<T>::iterator List<T>::pop_front() {
	Node* nextNode = head->next;
	delete head;
	head = nextNode;
	if (head == nullptr) {
		tail = nullptr;
	}

	return iterator(nextNode);
}

template<typename T>
inline typename List<T>::iterator List<T>::push_front(const T& data) {
	Node* node = new Node(data);

	if (head == nullptr) {
		tail = node;
	}

	node->next = head;
	head = node;

	return iterator(node);
}

template<typename T>
inline typename List<T>::iterator List<T>::push_back(const T& data) {
	if (tail == nullptr) {
		return push_front(data);
	}

	return insert(iterator(tail), data);
}
