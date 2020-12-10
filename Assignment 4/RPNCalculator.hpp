/****************************************************************/
/*                     RPNCalculator Class                      */
/****************************************************************/
/* LEAVE THIS FILE AS IS! DO NOT MODIFY ANYTHING! =]            */
/****************************************************************/

#pragma once
#include <string>

struct Operand
{
    float number;
    Operand* next;
};

class RPNCalculator
{
public:
  RPNCalculator();
  ~RPNCalculator();
  bool isEmpty();
  void push(float num);
  void pop();
  Operand* peek();
  Operand* getStackHead() { return stackHead; } // no need to implement this
  bool compute(std::string symbol);
private:
  Operand* stackHead; // pointer to the top of the stack
};
