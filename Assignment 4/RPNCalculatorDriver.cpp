/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <stack>
#include <iomanip>

// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

RPNCalculator::RPNCalculator(){
  stackHead=NULL;
}

RPNCalculator::~RPNCalculator(){
  while (stackHead!=NULL){
    Operand* ptr=NULL;
    ptr=stackHead;
    // ptr.pop();
    stackHead=stackHead->next;
  }
  stackHead=NULL;
}

bool RPNCalculator:: isEmpty(){
  if(stackHead==NULL){
    return true;
  }
  else{
    return false;
  }
}

void RPNCalculator::push(float numberr){
  Operand* node= new Operand;
  Operand* node2= new Operand;
  node->number=numberr;
  node2=stackHead;
  stackHead=node;
  stackHead->next=node2;
}

void RPNCalculator:: pop(){
  if (stackHead==NULL){
    cout << "Stack empty, cannot pop an item."<<endl;
    return;
  }
  else{
    Operand* point = NULL;
    point = stackHead;
    stackHead=stackHead->next;
    delete point;
  }
}

Operand* RPNCalculator:: peek(){
  if (stackHead==NULL){
    cout << "Stack empty, cannot peek."<<endl;
    return NULL;
  }
  else{
    return stackHead;
  }
}

bool RPNCalculator:: compute (string symbol){
  if (stackHead!=NULL){
    if (symbol == "+"){
      float value=peek()->number;
      float temp=stackHead->number;
      pop();
      if (stackHead!=NULL){
        float value2 = peek()->number;
        pop();
        push(value2+value);
      }
      else{
        cout << "err: not enough operands" << endl;
        push(temp);
        return false;
      }  
    }
    else if (symbol == "*"){
      float value=peek()->number;
      float temp=stackHead->number;
      pop();
      if (stackHead!=NULL){
        float value2 = peek()->number;
        pop();
        push(value2*value);
      }
      else{
        cout << "err: not enough operands" << endl;
        push(temp);
        return false;
      }  
    }
    else{
      cout << "err: invalid operation" << endl;
      return false;
    }
  }
  else{
    cout << "err: not enough operands" << endl;
    return false;
  }
}

int main()
{
  // TODO - Declare a stack to hold the operands
  RPNCalculator operands;
  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;
  while(true)
  {
    cout << "#> ";
    string input="";
    getline (cin,input);
    /* TODO
       1. Read input (operators and operands) until you encounter a "="
       2. Use the isNumber function to check if the input is an operand
       3. push all operands to the stack
       4. If input is not an operand, call the compute function to evaluate
          the partial expression
    */
    if (input!="="){
      if (isNumber(input)){
        //push operands to the stack
        operands.push(stof(input));      
      }
      else{
        //compute function to evaluate
        if (input=="="){
          break;
        }
        else{
          operands.compute(input);
        }
      } 
      if (operands.isEmpty()==true){
        cout << "No operands: Nothing to evaluate" << endl;
        // return 0;
      } 
    }
    else{
      break;
    } 
  }
   // TODO - If the stack is empty then print "No operands: Nothing to evaluate" 

  /* TODO - Validate the expression
      1. If valid then print the result
      2. Else, print "Invalid expression"*/
  if (operand.isEmpty()){
    cout <<"No operands: Nothing to evaluate"<<endl;
    return 0;
  }
  float temp=operands.peek()->number;
  operands.pop();
  if (operands.getStackHead()!=NULL){
    cout << "Invalid expression" << endl;
  }
  else{
    cout << std::setprecision(3)<<temp;
  }
}