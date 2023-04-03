//-----------------------------------------------------------------------------
/***
    Author: Nicholas Barsi-Rhyne
    CruzID: nbarsirh
    Assignment: pa6

    List.cpp: This file contains the implementation of my List ADT IN C++.
***/
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List(){
   frontDummy = new Node(-1);
   backDummy = new Node(-2);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
   frontDummy = new Node(-1);
   backDummy = new Node(-2);
   num_elements = 0;
   pos_cursor = 0;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   Node *beforeTemp = backDummy;
   Node *afterTemp = backDummy->prev;
   Node *n = L.frontDummy->next;
   while (n != L.backDummy) {

      insertAfter(n->data);
      if (L.afterCursor == nullptr) {
         throw std::range_error("List: copy constructor: afterCursor undefined");
      }
      if (L.afterCursor == n) {
         afterTemp = afterCursor;
         beforeTemp = beforeCursor;
      }
      moveNext();
      n = n->next;
   }

   if (length() != 0) {
      beforeCursor = beforeTemp;
      afterCursor = afterTemp;
      pos_cursor = L.pos_cursor;
   }
   else {
      afterCursor = backDummy;
      beforeCursor = frontDummy;
   }
   
}

// Destructor
List::~List() {
   clear();
   delete frontDummy;
   delete backDummy;
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
   return num_elements;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
   return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
   if (pos_cursor == num_elements) {
      throw std::range_error("List: peekNext(): cursor at back");
   }
   return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
   if (pos_cursor <= 0) {
      throw std::range_error("List: peekPrev(): cursor at front");
   }
   return beforeCursor->data;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
   if (num_elements == 0) {
      throw std::length_error("List: front(): empty list");
   }
   return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
   if (num_elements == 0) {
      throw std::length_error("List: back(): empty list");
   }
   return backDummy->prev->data;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
   while (num_elements != 0) {
      moveFront();
      eraseAfter();
   }
   beforeCursor = frontDummy;
   afterCursor = backDummy;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
   pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
   beforeCursor = backDummy->prev;
   afterCursor = backDummy;
   pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
   if (pos_cursor == num_elements) {
      throw std::range_error("List: moveNext(): cursor at back");
   }
   beforeCursor = afterCursor;
   afterCursor = afterCursor->next;
   pos_cursor++;
   return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
   if (pos_cursor <= 0) {
      throw std::range_error("List: movePrev(): cursor at front");
   }
   afterCursor = beforeCursor;
   beforeCursor = beforeCursor->prev;
   pos_cursor--;
   return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
   Node* n = new Node(x);
   n->prev = beforeCursor;
   n->next = afterCursor;
   beforeCursor->next = n;
   afterCursor->prev = n;
   afterCursor = n;
   num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
   Node* n = new Node(x);
   n->prev = beforeCursor;
   n->next = afterCursor;
   beforeCursor->next = n;
   afterCursor->prev = n;
   beforeCursor = n;
   num_elements++;
   pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
   if (pos_cursor >= num_elements) {
      throw std::range_error("List: setAfter(): cursor at back");
   }
   afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
   if (pos_cursor <= 0) {
      throw std::range_error("List: setBefore(): cursor at front");
   }
   beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
   if (pos_cursor == num_elements) {
      throw std::range_error("List: eraseAfter(): cursor at back");
   }
   Node *N = afterCursor;
   afterCursor = afterCursor->next;
   afterCursor->prev = beforeCursor;
   beforeCursor->next = afterCursor;
   num_elements--;
   delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
   if (pos_cursor <= 0) {
      throw std::range_error("List: eraseBefore(): cursor at front");
   }
   Node *N = beforeCursor;
   beforeCursor = beforeCursor->prev;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;
   num_elements--;
   pos_cursor--;
   delete N;
}

// Other Functions -------------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
   while (pos_cursor != num_elements) {
      if (moveNext() == x) {
         return pos_cursor;
      }
   }
   return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
   while (pos_cursor != 0) {
      if (movePrev() == x) {
         return pos_cursor;
      }
   }
   return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
   Node *temp = frontDummy->next;
   Node *compare = temp->next;
   int tempPos = 0;
   int comparePos = 1;
   while (temp != backDummy) {
      while (compare != backDummy) {
         if (temp->data == compare->data) {
            Node *n = compare;
            compare->prev->next = compare->next;
            compare->next->prev = compare->prev;
            compare = n->next;
            num_elements--;
            if (beforeCursor == n) {
               beforeCursor = n->prev;
            }
            if (afterCursor == n) {
               afterCursor = n->next;
            }
            delete n;
            if (comparePos <= pos_cursor) {
               pos_cursor--;
            }
            comparePos++;
            continue;
         }
         compare = compare->next;
         comparePos++;
      }
      tempPos++;
      comparePos = tempPos + 1;
      temp = temp->next;
      compare = temp->next;
   }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
   List N;
   Node *temp = this->frontDummy->next;
   while(temp != this->backDummy) {
      N.insertAfter(temp->data);
      N.moveNext();
      temp = temp->next;
   }
   temp = L.frontDummy->next;
   while(temp != L.backDummy) {
      N.insertAfter(temp->data);
      N.moveNext();
      temp = temp->next;
   }
   N.moveFront();
   return N;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
   Node* N = nullptr;
   if (length() == 0) {
      return "";
   }
   std::string s = "(";
   if (num_elements == 0) {
      return s;
   }
   for(N = frontDummy->next; N != backDummy->prev; N = N->next){
      s += std::to_string(N->data)+", ";
   }
   s += std::to_string(N->data) + ")";
   return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
   Node *l;
   Node *r;
   if (this->num_elements != R.num_elements) {
      return false;
   }
   l = this->frontDummy->next;
   r = R.frontDummy->next;
   while (l != this->backDummy) {
      if (l->data != r->data) {
         return false;
      }
      l = l->next;
      r = r->next;
   }
   return true;
}

// Overloaded Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
   return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L, then returns a reference
// to this List.
List& List::operator=( const List& L ) {
   if (this != & L) { // not self assignment
      // make a copy of L
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }
   // return this with the new data installed
   return *this;
   // the copy, if there is one, is deleted upon return
}
