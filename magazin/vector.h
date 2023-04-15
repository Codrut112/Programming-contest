#pragma once

#include <assert.h>

template<typename ElementT>
class IteratorVector;

template<typename ElementT>
class VectorDinamic {
private:
	//reprezentare
	ElementT* e;
	int cp;
	int n;

	//redim
	void redim();
public:
	//default constructor
	VectorDinamic();
	//copy constructor
	VectorDinamic(const VectorDinamic& ot);
	//assignment operator
	VectorDinamic& operator=(const VectorDinamic& ot);
	//destructor
	~VectorDinamic();

	//add element in vector
	void push_back(ElementT elem);
	//get element from position in vector
	ElementT& get(int poz);
	//set element on position in vector
	void set(ElementT elem, int poz);
	//get size - length of vector
	int size() const;
	//sterge ultimul element
	void pop_back();

	//iterator methods
	friend class IteratorVector<ElementT>;

	IteratorVector<ElementT> begin();
	IteratorVector<ElementT> end();

};

template<typename ElementT>
class IteratorVector {
private:
	const VectorDinamic<ElementT>& vec;
	int poz = 0;
public:
	IteratorVector(const VectorDinamic<ElementT>& v) noexcept;
	IteratorVector(const VectorDinamic<ElementT>& v, int poz) noexcept;
	bool valid() const;
	ElementT& element() const;
	void next();
	ElementT& operator*();
	IteratorVector& operator++();
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic() {
	this->e = new ElementT[1];
	this->n = 0;
	this->cp = 1;
}

template<typename ElementT>
VectorDinamic<ElementT>::VectorDinamic(const VectorDinamic& ot) {

	this->e = new ElementT[ot.cp];

	for (int i = 0; i < ot.n; i++) {
		this->e[i] = ot.e[i];
	}
	this->n = ot.n;
	this->cp = ot.cp;
}


template<typename ElementT>
VectorDinamic<ElementT>& VectorDinamic<ElementT>::operator=(const VectorDinamic& ot) {


	delete[] this->e;

	
	this->e = new ElementT[ot.cp];
	for (int i = 0; i < ot.n; i++) {
		e[i] = ot.e[i]; 
	}
	this->n = ot.n;
	this->cp = ot.cp;
	return *this;
}
template<typename ElementT>
void VectorDinamic<ElementT>::redim() {
	int newCapacity = this->cp * 2;
	ElementT* newElems = new ElementT[newCapacity];
	for (int i = 0; i < this->n; i++) {
		newElems[i] = this->e[i];
	}
	delete[] this->e;
	this->e = newElems;
	this->cp = newCapacity;

}
template<typename ElementT>
VectorDinamic<ElementT>::~VectorDinamic() {
	delete[] this->e;
}
template<typename ElementT>
void VectorDinamic<ElementT>::push_back(ElementT elem) {
	if (this->n == this->cp)
		redim();
	this->e[this->n] = elem;
	this->n++;
}

template<typename ElementT>
ElementT& VectorDinamic<ElementT>::get(int poz) {


	return this->e[poz];
}

template<typename ElementT>
void VectorDinamic<ElementT>::set(ElementT elem, int poz) {


	this->e[poz] = elem;
}

template<typename ElementT>
int VectorDinamic<ElementT>::size() const{
	

	return this->n;
}

template<typename ElementT>
 void VectorDinamic<ElementT>::pop_back()
 {
	 n--;
}

template<typename ElementT>
IteratorVector<ElementT> VectorDinamic<ElementT>::begin() {
	return IteratorVector<ElementT>(*this);
}
template<typename ElementT>
IteratorVector<ElementT> VectorDinamic<ElementT>::end() {
	return IteratorVector<ElementT>(*this, this->n);
}



template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectorDinamic<ElementT>& v) noexcept :vec{ v } { };
template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectorDinamic<ElementT>& v, int poz) noexcept :vec{ v }, poz{ poz } {};

template<typename ElementT>
bool IteratorVector<ElementT>::valid() const {
	return this->poz < this->vec.n;
}
template<typename ElementT>
ElementT& IteratorVector<ElementT>::element() const {
	return this->vec.e[this->poz];
}
template<typename ElementT>
void IteratorVector<ElementT>::next() {
	this->poz++;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::operator*() {
	return this->element();
}

template<typename ElementT>
IteratorVector<ElementT>& IteratorVector<ElementT>::operator++() {
	this->next();
	return *this;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator==(const IteratorVector& ot) noexcept {
	return this->poz == ot.poz;
}
template<typename ElementT>
bool IteratorVector<ElementT>::operator!=(const IteratorVector& ot) noexcept {
	return !(*this == ot);
}


 


