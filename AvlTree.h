#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <vector>
#include <iostream>    // For NULL
#include <algorithm>
#include <iomanip>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }
    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x, vector<int> & lineno, int & compar ) const
    {
        return contains( x, lineno, root, compar );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == NULL;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        out << "Binary Search Tree Index:" << endl
            << "-------------------------" << endl;
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    void printTree(string fName) const {
      ofstream outFile(fName);
      ostream & out = outFile;
      out << "Binary Search Tree Index:" << endl
          << "-------------------------" << endl;
      if (isEmpty())
          out << "Empty tree" << endl;
      else
          printTree( root, out );
      out << endl;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x, const int & lineno, int & compar, int & rotates )
    {
        insert( x, lineno, root, compar, rotates );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        cout << "Sorry, remove unimplemented; " << x <<
                " still present" << endl;
    }

    /**
     * Deep copy.
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }

    int countTreeNodes() const{
      if(isEmpty()){
        return -1;
      }
      else
        return(countTreeNodes(root));
    }

    int TreeHeight() const{
      if(isEmpty()){
        return -1;
      }
      else
        return(height(root));
    }

  private:
    struct AvlNode
    {
        Comparable element;
        vector<int> lineNumberList;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    AvlNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, int lineno, AvlNode * & t, int & compar, int & rotates )
    {
        if( t == NULL ){
            t = new AvlNode( x, NULL, NULL );
            t->lineNumberList.push_back(lineno);
        }
        else if( x < t->element )
        {
            compar++;
            insert( x, lineno, t->left, compar, rotates );
            if( height( t->left ) - height( t->right ) == 2 )
                if( x < t->left->element ){
                    compar++;
                    rotates++;
                    rotateWithLeftChild( t );
                  }
                else{
                    compar++;
                    rotates = rotates + 2;
                    doubleWithLeftChild( t );
                }
        }
        else if( t->element < x )
        {
            compar = compar + 2;
            insert( x, lineno, t->right, compar, rotates );
            if( height( t->right ) - height( t->left ) == 2 )
                if( t->right->element < x ){
                    compar++;
                    rotates++;
                    rotateWithRightChild( t );
                }
                else{
                    compar++;
                    rotates = rotates + 2;
                    doubleWithRightChild( t );
                }
        }
        else{
            compar = compar + 2;
            t->lineNumberList.push_back(lineno);  // Duplicate; do nothing
        }
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, vector<int> & lineno, AvlNode *t, int & compar) const
    {
        if( t == NULL ){
            return false;
          }
        else if( x < t->element ){
            compar++;
            return contains( x, lineno, t->left, compar );
          }
        else if( t->element < x ){
            compar = compar + 2;
            return contains( x, lineno, t->right, compar );
          }
        else{
            compar = compar + 2;
            lineno = t->lineNumberList;
            return true;    // Match
        }
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != NULL )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t, ostream & out ) const
    {
        if( t != NULL )
        {
            int numbersPrinted = 0;
            printTree( t->left, out );
            out << left << setw(16) << t->element << " ";
            for (const auto line: t->lineNumberList) {
              if (numbersPrinted++ %9 == 0)
                out << line;
              else if (numbersPrinted % 9)
                out << ", " << line;
              else {
                out << ", " << line << "," << endl << left << setw(17) << " ";
              }
            }
            out << endl;
            //cout << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     */
    int height( AvlNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    int countTreeNodes(AvlNode * t) const{
      if(t == nullptr)
        return 0;
      else{
        return(1 + countTreeNodes(t->left) + countTreeNodes(t->right));
      }
    }
};

#endif
