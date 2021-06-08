#include <bits/stdc++.h>

template<typename T>
struct PersistentStack {
	struct node {
		T value;
		node* prv;
		node(T value, node* prv) {
			this->value = value;
			this->prv = prv;
		}
	};
private:
	node* p;
public:
	PersistentStack(void) : p(nullptr) {}
	PersistentStack(node* ptr) : p(ptr) {}
	T top(void) {
		assert(("top() called on an empty stack.", p != nullptr));
		return (p->value);
	}
	PersistentStack push(T value) {
		node* new_node = new node(value, p);
		return PersistentStack(new_node);
	}
	PersistentStack pop(void) {
		assert(("pop() called on an empty stack.", p != nullptr));
		return PersistentStack(p->prv);
	}
};