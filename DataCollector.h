#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <iostream>
#include "Vector.h"
#include "BST.h"

    /**
     * @class DataCollector
     * @brief Collector class used to collect data from a BST
     *
     *
     * @author Ricardo Jacobsen
     * @version 01
     * @date 22/05/2021 Ricardo Jacobsen, Started
     *
     */

template <class T>
using Bst = BST<T>;

using namespace std;

template <class T>
class DataCollector
{

public:

    /**
     * @brief collects items and loads in a vector
     * @param data - object to be inserted in the end of the vector
     * @return void (static)
     */
    static void vectorCollect(const T& data)
    {
       weatherVector.pushIn(data);
    }

    /**
     * @brief returns the size of the vector
     * @return int
     */
    int size()
    {
        return weatherVector.GetLength();
    }

    /**
     * @brief [] operator which returns the vector data in a specific index
     * @param k - index of a vector
     * @return T&
     */
    T& operator[](int k)
    {
        return weatherVector[k];   // used to return the data that has been collected.
    }

    /**
     * @brief clears the vector
     * @return void (static)
     */
    static void deleteData()
    {
        weatherVector.deleteVec();
    }


private:
    static Vector<T> weatherVector;  // static vector which will hold the retrieved data from a BST
};

template <class T>
Vector<T> DataCollector<T>::weatherVector;

#endif
