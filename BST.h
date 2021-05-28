#ifndef BST_H
#define BST_H

#include<iostream>


using namespace std;

    /**
     * @class BST
     * @brief Create a binary search tree and do several operations(Based on the book)
     *
     * Consists of a struct nodeType which holds the information, left link and right link of the node
     *
     *
     * @author Ricardo Jacobsen
     * @version 01
     * @date 01/05/2021 Ricardo Jacobsen, Started
     *
     *
     *
     */

template <class T>
struct nodeType
{
    T info;
    nodeType<T> *lLink;
    nodeType<T> *rLink;
};




template <class T>
class BST{

typedef void (*fcnPtr)(const T&);

public:

     /**
     * @brief Default constructor which sets the root to a nullptr
     *
     */
     BST();

     /**
     * @brief Deconstructor which destrois the the tree when program finishes
     *
     */
    ~BST();

     /**
     * @brief Copy Constructor which copies the tree
     * @param otherTree - the tree to be copied
     */
     BST(const BST<T>& otherTree);

     /**
     * @brief Insert an item of type T into the tree
     * @param insertItem - an item of type T
     * @return void
     */
     void insertNode(const T& insertItem);

     /**
     * @brief Search a specific item in the tree and returns the address of the node if it is found
     * @param item - an item of type T
     * @return T*
     */
     bool searchNode (const T& searchItem) const;

     /**
     * @brief calls the private method: inorderTraversal
     * It can not modify anything since it is const
     * @return void
     */
     void inorderTraversal(fcnPtr fcn1) const;

     /**
     * @brief calls the private method: preorderTraversal
     * It can not modify anything since it is const
     * @return void
     */
     void preorderTraversal(fcnPtr fcn1) const;

     /**
     * @brief calls the private method: postorderTraversal
     * It can not modify anything since it is const
     * @return void
     */
     void postorderTraversal(fcnPtr fcn1 ) const;

     /**
     * @brief Destroy the tree from root pointed as parameter
     * @return void
     */
     void destroyTree();

     /**
     * @brief delete an item of type T from the tree
     * @param deleteItem - an item of type T
     * @return void
     */
    void deleteNode(const T& deleteItem);

     /**
     * @brief assignment operator overloading
     * @param otherTree - the tree that copies the other
     */
    const BST<T>& operator=(const BST<T>& otherTree);

private:
    nodeType<T>* root; //pointer which points to the root of the tree

    /**
     * @brief Make a copy of the tree
     * @param copiedTreeRoot - root of the tree that is copied, otherTreeRoot - root of the copy tree
     * @return void
     */
    void copyTree(nodeType<T>* &copiedTreeRoot, nodeType<T>* otherTreeRoot);


    /**
     * @brief Destrois the tree from root pointed as parameter
     * @return void
     */
    void destroy(nodeType<T>* &p);


    /**
     * @brief order the tree with inorder traversal
     * @param p - pointer of type T
     * @return void
     */
    void inorder(nodeType<T>* p, fcnPtr fcn1) const;

    /**
     * @brief order the tree with preorder traversal
     * @param p - pointer of type T
     * @return void
     */
    void preorder(nodeType<T>* p, fcnPtr fcn1) const;

    /**
     * @brief order the tree with postorder traversal
     * @param p - pointer of type T
     * @return void
     */
    void postorder(nodeType<T>* p, fcnPtr fcn1) const;


    /**
     * @brief delete an item of type T from the tree
     * @param deleteItem - an item of type T
     * @return void
     */
    void deleteFromTree(nodeType<T>* &p);



};

template <class T>
BST<T>::BST()
{
    root = nullptr; //sets the root to nullptr
}//end of default constructor

template <class T>
const BST<T>& BST<T>::operator=(const BST<T>& otherTree)
{
    if(this != &otherTree) //avoiding self copy
    {
        if(root != nullptr) //if the current tree is non empty
        {
            destroy(root);
        }

        if(otherTree.root == nullptr) //if tree to be assigned is empty
        {
            root = nullptr;
        }
        else //copy the tree using copyTree function
        {
            copyTree(root, otherTree.root);
        }
    }

    return *this;
}

//inorder
template <class T>
void BST<T>::inorderTraversal(fcnPtr fcn1) const
{
    inorder(root,fcn1); //Call the private

}//end of inorder


//preorder
template <class T>
void BST<T>::preorderTraversal(fcnPtr fcn1) const
{
    preorder(root,fcn1); //Call the private

}//end of inorder


//postorder
template <class T>
void BST<T>::postorderTraversal(fcnPtr fcn1) const
{
    postorder(root,fcn1); //Call the private

}//end of inorder


//destroy tree
template <class T>
void BST<T>::destroyTree()
{
    destroy(root);
}//end of destroy tree



//Copy the constructor
template <class T>
BST<T>::BST(const BST<T>& otherTree)
{
    if(otherTree.root==nullptr)//otherTree is empty
    {
        root = nullptr;
    }
    else{
        copyTree(root, otherTree.root);
    }
} //end of copy constructor



template <class T>
BST<T>::~BST()
{
}//end of desconstructor



//Search
template <class T>
bool BST<T>::searchNode(const T& searchItem) const
{
    nodeType<T>* curr; //pointer which will hold the current node
    bool found = false;

    if(root==nullptr){ //display a message when tree is empty
        cout<<"Tree is empty..."<<'\n';

    }
    else{
        curr = root;

        while(curr!=nullptr && !found){
            if(curr->info==searchItem){ //return true when searching item is found
                found=true;
                }
            else if(curr->info > searchItem){
                curr = curr->lLink; //traverse through the left link of the current node if the searching item is smaller than the current node's item
            }
            else{
                curr = curr->rLink; //traverse through the right link of the current node if the searching item is greater than the current node's item
            }
        }
    }

    return found;
}//end of search





//inserNode
template <class T>
void BST<T>::insertNode(const T& insertItem)
{
    nodeType<T> *curr; //current pointer to hold the pointer that is being dealt with
    nodeType<T> *trailcurr; //pointer to track current pointer
    nodeType<T> *newNode; //new node pointer whhich will be the inserted object

    newNode = new nodeType<T>;
    newNode->info = insertItem;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;

    if(root==nullptr){ //if the root is a nullptr, the new object will be the root of the tree
        root = newNode;
       // cout<<endl<<newNode->info<<"data INSERTED as root node"<<endl;

    }
    else{
        curr = root;

        while(curr!=nullptr){ //while loop till it hits a nullptr
            trailcurr = curr;


            if(curr->info==insertItem){ //display a message when the item already exists in the tree
              //cout<<"The data already exists...."<<endl;

                return;
            }
            else if(curr->info > insertItem){
                curr = curr->lLink; //traverse through the left link when inserting item is smaller than the current node's item
            }
            else{
                curr = curr->rLink; //traverse through the right link when inserting item is smaller than the current node's item

            }
        }//end of while

        if(trailcurr->info > insertItem){
            trailcurr->lLink = newNode; //assign the new node to the left link of the leaf node if the item is smaller than leaf node's item
           //cout<<"The data "<<insertItem<<" INSERTED on the left link"<<endl;

        }
        else {
            trailcurr->rLink = newNode; //assign the new node to the right link of the leaf node if the item is greater than leaf node's item
           //cout<<"The data "<<insertItem<<" INSERTED on the Right link"<<endl;

        }
    }
}//end of insert node







//delete node
template <class T>
void BST<T>::deleteNode(const T& deleteItem)
{
nodeType<T> *curr;
nodeType<T> *traillCurr;
bool found= false;

    if(root == nullptr){
        cout<<"Cannot delete, it's empty"<<endl;
    }else{
    curr=root;
    traillCurr =root;
    while(curr != nullptr && !found){
        if(curr->info==deleteItem){
            found=true;
            }

        else{
            traillCurr = curr;
            if(curr->info >deleteItem){
                curr = curr->lLink;
            }

        else{
            curr=curr->rLink;}
        }
    }//end of while

    if(curr==nullptr){
        cout<<"The item to be deleted is not int the tree."<<endl;
    }
    else if(found){
        if(curr == root){
            deleteFromTree(root);
        }
    else if (traillCurr->info >deleteItem){
        deleteFromTree(traillCurr->lLink);
        }
    else{
        deleteFromTree(traillCurr->rLink);
    }
    }
    else{
        cout<<"The item to be deleted is not in the tree"<<endl;
    }
    }
} //end of delete node








//copytree
template <class T>
void BST<T>::copyTree(nodeType<T>* &copiedTreeRoot, nodeType<T>* otherTreeRoot)
{
    if(otherTreeRoot==nullptr){
        copiedTreeRoot=nullptr; //If the tree root is nullptr, the copying tree's root is also a nullptr
    }
    else{//If the root is not a nullptr, copy the value in the node and copy the left and right node recursively
        copiedTreeRoot=new nodeType<T>;
        copiedTreeRoot->info=otherTreeRoot->info;
        copyTree(copiedTreeRoot->lLink,otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink,otherTreeRoot->rLink);
    }
}//end of copy tree




//destroy
template <class T>
void BST<T>::destroy(nodeType<T>* &p)
{
    if(p!=nullptr){ //when pointer is not nullptr
        destroy(p->lLink); //call destroy() on the left link
        destroy(p->rLink); //call destroy() on the right link
        delete p; //delete node once it is a leaf
        p = nullptr; //set the deleted pointer to a nullptr
    }
}//end of destroy


//inorder
template<class T>
void BST<T>::inorder(nodeType<T>* p, fcnPtr fcn1)const
{
    if(p!=nullptr){
        inorder(p->lLink,fcn1);
        (fcn1)(p->info);
        inorder(p->rLink,fcn1);
    }
}//end of inorder




//preorder
template<class T>
void BST<T>::preorder(nodeType<T>* p, fcnPtr fcn1)const
{
    if(p!=nullptr){
        (fcn1)(p->info);
        preorder(p->lLink, fcn1);
        preorder(p->rLink, fcn1);
    }
}//end of preorder


//postorder
template<class T>
void BST<T>::postorder(nodeType<T>* p, fcnPtr fcn1)const
{
    if(p!=nullptr){
        preorder(p->lLink, fcn1);
        preorder(p->rLink, fcn1);
        (fcn1)(p->info);
    }
}//end of preorder

//delete from tree
template<class T>
void BST<T>::deleteFromTree(nodeType<T>* &p)
{
    nodeType<T> *curr; //current pointer to hold the pointer that is being dealt with
    nodeType<T> *trailcurr; //pointer to track current pointer
    nodeType<T> *temp; //new node pointer whhich will be the inserted object

    if(p==nullptr){
        cout<<"Error: the node does not exist"<<endl;
    }
    else if(p->lLink==nullptr && p->rLink==nullptr){
        temp = p;
        p= nullptr;
        delete temp;
    }
    else if(p->lLink==nullptr){
        temp=p;
        p=temp->rLink;
        delete temp;
    }
    else if(p->rLink==nullptr){
        temp = p;
        p = temp->lLink;
        delete temp;
    }
    else{
        curr = p->lLink;
        trailcurr = nullptr;

        while(curr->rLink != nullptr){
            trailcurr = curr;
            curr = curr->rLink;
        }//end of while

        p->info = curr->info;

        if(trailcurr==nullptr){
            p->lLink = curr->lLink;
        }else{
        trailcurr->rLink = curr->lLink;
        delete curr;
        }
    }//end of else
}//end of delete from tree




#endif // BST_H


