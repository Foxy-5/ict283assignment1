#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <iostream>
/**
	 * @class  MyVector
	 * @brief  vector template class
	 *
	 *
	 *
	 *
	 * @author Seow Wei Cheng
	 * @version 01
	 * @date 1/3/2021
	 *
	 *
	 *
	 * @todo
	 *
	 * @bug
	 */
using namespace std;

template <class T>
class MyVector
{
public:
                /**
                * @brief create a vector object
                *
                * Construct a vector object
                *
                * @return
                */
    MyVector();
                /**
                * @brief set all variables to 0 or NULL
                *
                * set all variables to 0 or NULL
                *
                * @return void
                */
    void clear();
                /**
                * @brief create a vector data structure
                *
                * create a vector data structure using the given int size
                *
                * @return void
                */
    void create(int size);
                /**
                * @brief resize the vector
                *
                * Resize the vector if it's not large enough (x2 in size)
                *
                * @return void
                */
    void resize(int newSize);
                /**
                * @brief add a value to the end of the vector
                *
                * add a value to the end of the vector
                *
                * @return void
                */
    void push_back(const T& element);
        //remove a value from the end of the vector
    //void pop_back();
                /**
                * @brief print the whole vector
                *
                * print out the whole vector to the screen
                *
                * @return void
                */
    void print() const;
                /**
                * @brief returns value at index
                *
                * returns the value at index using the given int i
                *
                * @return T&
                */
    T& at(int i);
                /**
                * @brief returns current number of index stored
                *
                * returns the current number of index stored
                *
                * @return int
                */
    int getCount();
                /**
                * @brief returns max capacity of the vector
                *
                * returns the max capacity of the vector
                *
                * @return int
                */
    int getCapacity();
                /**
                * @brief check if the vector is full
                *
                * returns whether the vector is full
                *
                * @return bool
                */
    bool isFull();
                /**
                * @brief check if the vector is empty
                *
                * return whether the vector is empty
                *
                * @return bool
                */
    bool isEmpty();

private:
    T* arr;///vector to contain elements.
    T* start;///start of the vector
    T* end;///end of the vector.
    int count;///number of elements in the vector
    int capacity;///maximum capacity of the vector
};

template <class T>
MyVector<T>::MyVector()
{
    clear();
    create(2);
}

template <class T>
void MyVector<T>::clear()
{
    arr = NULL;
    start = NULL;
    end = NULL;
    count = 0;
    capacity = 0;

}

template <class T>
void MyVector<T>::create(int size)
{
    arr = new T[size];
    start = arr;
    end = arr;
    capacity = size;
}

 template <class T>
 void MyVector<T>::resize(int newSize)
 {
     T* newArr = new T[newSize]; //create new vector with new size
     T* newarrpointer = newArr; //create pointer to new vector
     T* oldarrpointer = arr;    //create pointer to old vector

     while (oldarrpointer != (arr + count)) //while there is still elements in the old vector
     {
         *(newarrpointer) = *(oldarrpointer); //copy elements from old vector to new vector
         newarrpointer++; //move pointer
         oldarrpointer++; // move pointer
     }
     start = newArr;
     end = newArr + count;
     capacity = newSize;

     delete[] arr; //delete the old vector
     arr = newArr; //set vector to new vector
 }

 template <class T>
 void MyVector<T>::push_back(const T& element)
 {
    if(count == (capacity - 1))
    {
        MyVector::resize(capacity * 2); //double the size of vector
    }
    *end = element; //add the element to the back of the vector
    end++;  //move the vector end pointer by 1
    count++; //+1 to the current size of the vector
 }

 /*template <class T>
 void MyVector<T>::pop_back()
 {
    count--;
    end--;
 }*/

 template <class T>
 void MyVector<T>::print() const
 {
     for(int i = 0; i < count; i++)
     {
         cout << arr[i] << endl;
     }
 }

 template <class T>
 T& MyVector<T>::at(int i)
 {
     if(i >= 0 && i <= count)
     {
         return arr[i];
     }
 }

 template <class T>
 int MyVector<T>::getCount()
 {
     return count;
 }

 template <class T>
 int MyVector<T>::getCapacity()
 {
     return capacity;
 }

 template <class T>
 bool MyVector<T>::isFull()
 {
    return(count == capacity);
 }

 template <class T>
 bool MyVector<T>::isEmpty()
 {
     return(count == 0);
 }
#endif // MYVECTOR_H_INCLUDED
