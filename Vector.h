#ifndef VECTOR_H
#define VECTOR_H

#include<vector>

/**
 * @class Vector
 * @brief Creates a Vector template
 *
 *
 *
 *
 * @author Ricardo Jacobsen
 * @version 01
 * @date 04/07/2021 Ricardo Jacobsen, Started
 *
 *
 *
 */


template <typename T>
class Vector
{
public:
    /**
     * @brief Constructs the Vector
     *
     */
    Vector();
    /**
     * @brief deconstructs the Vector
     *
     */
    ~Vector();
     /**
     * @brief Copy constructor
     *
     */
    Vector(const Vector <T> &object2);
    /**
     * @brief Insert an object in the array
     * @param int i, const T& object
     * @return void
     */
    void pushIn(const T& object);
    /**
     * @brief Pops an object out of the array
     * @param int index
     * @return void
     */
    //void popOut(int index);
    /**
     * @brief Overloads the [] operator
     * @param const int& index
     * @return T&
     */
    T& operator[](unsigned index);

     /**
     * @brief Overloads the [] operator
     * @param index - index of the object in the vector to be returned
     * Nothing can be modified here since it is const
     * @return T&
     */
    const T& operator[](unsigned index) const;

    /**
     * @brief Doubles the size of the array
     * @param
     * @return void
     */

    int GetLength() const;

    /**
     * @brief clears the vector
     * @return void
     */
    void deleteVec();
private:
    vector<T> array; //array of type T
};

template <typename T>
Vector<T>::Vector()
{
vector<T> array;
}

template <typename T>
Vector<T>::~Vector()
{
   array.clear();
}

template <typename T>
void Vector<T>::pushIn( const T& object)
{
    array.push_back(object);
}
template <typename T>
T& Vector<T>::operator[](unsigned index)
{
    return array.at(index);
}

template <typename T>
const T& Vector<T>::operator[](unsigned index) const
{
    return array.at(index);
}

template <typename T>
int Vector<T>::GetLength() const
{

   return array.size();
}

template <typename T>
void Vector<T>::deleteVec(){
    array.clear();
}

#endif

