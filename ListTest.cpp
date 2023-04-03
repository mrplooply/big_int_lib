//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/***
    Author: Nicholas Barsi-Rhyne
    CruzID: nbarsirh
    Assignment: pa6

    ListTest.cpp: This file contains my tests for my List ADT.
***/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void runTest(List *a, List *b) {
   List A = *a;
   List B = *b;

   A.insertBefore(1);
   A.insertBefore(2);
   A.insertBefore(2);
   A.insertBefore(1);
   A.insertBefore(2);
   A.insertBefore(3);
   A.insertBefore(1);
   A.findPrev(3);
   cout << "Pos after findPrev " + to_string(A.position()) << endl;
   A.cleanup();
   if (A.position() != 2) {
      cout << "Failed " + to_string(A.position()) << endl;
      cout << A << endl;
   }
   else
      cout << "Passed" << endl;
}

int main(){
   /*******************************************************
      Test 1: 
         findPrev(), cleanup()

      Results:
         Pos after findPrev 5
         Passed
   *///****************************************************

   cout << "******************* Test 1 *******************" << endl;

   List A;
   List B;
   runTest(&A, &B);

   /*******************************************************
      Test 2: 
         length(, font(), back() exceptions

      Results:
         0
         List: front(): empty list
         continuing without interruption
         List: back(): empty list
         continuing without interruption

   *///****************************************************

   cout << "******************* Test 2 *******************" << endl;

   List l;
   cout << l.length() << endl;

   try{
      l.front();
   } catch ( std::length_error& e ){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }

   try{
      l.back();
   } catch ( std::length_error& e ){
      cout << e.what() << endl;
      cout << "continuing without interruption\n" << endl;
   }

   /*******************************************************
      Test 3: 
         insertBefore(), front(), back(), length(), position()

      Results:
         (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
         front = 1
         back = 10
         length = 10
         position = 10

   *///****************************************************

   cout << "******************* Test 3 *******************" << endl;

   ListElement i;
   for (i = 1; i <= 10; i++) {
      l.insertBefore(i);
   }
   cout << l.to_string() << endl;
   cout << "front = " + to_string(l.front()) << endl;
   cout << "back = " + to_string(l.back()) << endl;
   cout << "length = " + to_string(l.length()) << endl;
   cout << "position = " + to_string(l.position()) << endl;

   /*******************************************************
      Test 4: 
         peekNext(), peekPrev(), eraseAfter()

      Results:
         List: peekNext(): cursor at back
         continuing without interruption
         peekPrev = 10
         List: eraseAfter(): cursor at back
         continuing without interruption

   *///****************************************************

   cout << "******************* Test 4 *******************" << endl;
   try {
      cout << "peekNext = " + to_string(l.peekNext()) << endl;
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   try {
      cout << "peekPrev = " + to_string(l.peekPrev()) << endl;
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   try {
      l.eraseAfter();
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }

   /*******************************************************
      Test 5: 
         List manipulations

      Results:
         (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 33)
         front = 1
         back = 33
         length = 11
         position = 10
         peekNext = 33
         peekPrev = 10

   *///****************************************************

   cout << "******************* Test 5 *******************" << endl;
   i = 33;
   l.insertAfter(33);
   cout << l.to_string() << endl;
   cout << "front = " + to_string(l.front()) << endl;
   cout << "back = " + to_string(l.back()) << endl;
   cout << "length = " + to_string(l.length()) << endl;
   cout << "position = " + to_string(l.position()) << endl;
   try {
      cout << "peekNext = " + to_string(l.peekNext()) << endl;
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   try {
      cout << "peekPrev = " + to_string(l.peekPrev()) << endl;
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }

   /*******************************************************
      Test 6: 
         eraseAfter(), eraseBefore()

      Results:
         (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 33)
         front = 1
         back = 33
         length = 11
         position = 10
         peekNext = 33
         peekPrev = 10
         trying eraseAfter 
         (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
         trying eraseBefore 
         (1, 2, 3, 4, 5, 6, 7, 8, 9)

   *///****************************************************

   cout << "******************* Test 6 *******************" << endl;
   try {
      cout << "trying eraseAfter "<< endl;
      l.eraseAfter();
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   cout << l.to_string() << endl;
   try {
      cout << "trying eraseBefore "<< endl;
      l.eraseBefore();
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   cout << l.to_string() << endl;

   /*******************************************************
      Test 7: 
         clear(), eraseBefore()

      Results:
         trying eraseAfter 
         (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
         trying eraseBefore 
         (1, 2, 3, 4, 5, 6, 7, 8, 9)
         after clearing
         length = 0
         List: front(): empty list
         continuing without interruption
         List: back(): empty list
         continuing without interruption

   *///****************************************************

   cout << "******************* Test 7 *******************" << endl;
   cout << "after clearing" << endl;
   l.clear();
   cout << "length = " + to_string(l.length()) << endl;
   try{
      l.front();
   } catch ( std::length_error& e ){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }

   try{
      l.back();
   } catch ( std::length_error& e ){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   cout << l.to_string() << endl;

   /*******************************************************
      Test 8: 
         moveFront(), moveBack(), setBefore, setAfter(), moveNext()

      Results:
         moveNext = 1
         movePrev = 10
         (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
         (33, 33, 3, 4, 5, 6, 7, 8, 9, 10)
         peekNext = 3
         peekPrev = 33

   *///****************************************************

   cout << "******************* Test 8 *******************" << endl;
   for (i = 1; i <= 10; i++) {
      l.insertBefore(i);
   }
   l.moveFront();
   cout << "moveNext = " + to_string(l.moveNext()) << endl;
   l.moveBack();
   cout << "movePrev = " + to_string(l.movePrev()) << endl;
   cout << l.to_string() << endl;
   l.moveFront();
   l.moveNext();
   l.setAfter(33);
   l.setBefore(33);
   l.moveNext();
   cout << l.to_string() << endl;
   try {
      cout << "peekNext = " + to_string(l.peekNext()) << endl;
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }
   try {
      cout << "peekPrev = " + to_string(l.peekPrev()) << endl;
   } catch (std::range_error& e){
      cout << e.what() << endl;
      cout << "continuing without interruption" << endl;
   }

   /*******************************************************
      Test 9: 
         findNext(), findPrev()

      Results:
         finding 8:
         found 8 at pos 8
         finding -3:
         could not find -3
         cursor is at 0
         could not find -3
         cursor is at 10

   *///****************************************************

   cout << "******************* Test 9 *******************" << endl;
   l.moveFront();
   cout << "finding 8:" << endl;
   int x = l.findNext(8);
   if (x == -1) {
      cout << "could not find 8" << endl;
   }
   else {
      cout << "found 8 at pos " + to_string(x) << endl;
   }
   cout << "finding -3:" << endl;
   x = l.findPrev(-3);
   if (x == -1) {
      cout << "could not find -3" << endl;
   }
   else {
      cout << "found -3 at pos " + to_string(x) << endl;
   }
   cout << "cursor is at " + to_string(l.position()) << endl;
   x = l.findNext(-3);
   if (x == -1) {
      cout << "could not find -3" << endl;
   }
   else {
      cout << "found -3 at pos " + to_string(x) << endl;
   }
   cout << "cursor is at " + to_string(l.position()) << endl;

   /*******************************************************
      Test 10: 
         cleanup()

      Results:
         list before cleanup:
         cursor is at 8
         (33, 33, 3, 4, 5, 6, 7, 8, 9, 33)
         peekPrev = 8
         peekNext = 9
         list after cleanup:
         (33, 3, 4, 5, 6, 7, 8, 9)
         cursor is at 7

   *///****************************************************

   cout << "******************* Test 10 *******************" << endl;
   l.moveBack();
   l.setBefore(33);
   l.movePrev();
   l.movePrev();
   cout << "list before cleanup:" << endl;
   cout << "cursor is at " + to_string(l.position()) << endl;
   cout << l.to_string() << endl;
   cout << "peekPrev = " + to_string(l.peekPrev()) << endl;
   cout << "peekNext = " + to_string(l.peekNext()) << endl;
   l.cleanup();
   cout << "list after cleanup:" << endl;
   cout << l << endl;
   cout << "cursor is at " + to_string(l.position()) << endl;

   /*******************************************************
      Test 11: 
         concat(), equals()

      Results:
         (33, 33, 33, 33)
         (33, 3, 4, 5, 6, 7, 8, 9, 33, 33, 33, 33)
         cursor is at 0
         l does not equals k
         (33, 3, 4, 5, 6, 7, 8, 9, 33, 33, 33, 33)
         cursor is at 0
         a equals k
         (33, 3, 4, 5, 6, 7, 8, 9)
         (33, 3, 4, 5, 6, 7, 8, 9, 33, 33, 33, 33)
         cursor is at 0
         cursor is at 10

   *///****************************************************

   cout << "******************* Test 11 *******************" << endl;
   List j;
   for (i = 0; i <= 3; i++) {
      j.insertBefore(33);
   }
   cout << j.to_string() << endl;
   List k = l.concat(j);
   cout << k.to_string() << endl;
   cout << "cursor is at " + to_string(k.position()) << endl;
   if (l == k) {
      cout << "l equals k" << endl;
   }
   else {
      cout << "l does not equals k" << endl;
   }
   List a = k;
   cout << a.to_string() << endl;
   cout << "cursor is at " + to_string(a.position()) << endl;
   if (a.equals(k)) {
      cout << "a equals k" << endl;
   }
   else {
      cout << "a does not equals k" << endl;
   }
   cout << l << endl;

   l = k;
   cout << l << endl;
   cout << "cursor is at " + to_string(l.position()) << endl;
   for (int x = 0; x < 10; x++) {
      l.moveNext();
   }
   cout << "cursor is at " + to_string(l.position()) << endl;
   return(0);
}
