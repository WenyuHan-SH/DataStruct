#ifndef DATA_STRUCT_STACK_BASE_H
#define DATA_STRUCT_STACK_BASE_H
#include "Data_Struct_Stack_Define.h"

class Stack
{
public:
	Stack() {}
	virtual Status InitStack() = 0;
	virtual Status DestroyStack() = 0;
	virtual Status ClearStack() = 0;
	virtual int StackLength() const = 0;
	virtual Status GetTop(ElemType& eData)const = 0;
	virtual Status Push(const ElemType& eData) = 0;
	virtual Status Pop(ElemType& eData) = 0;
public:
	bool StackEmpty() const;
};

bool Stack::StackEmpty() const
{
	return 0 == StackLength();
}
#endif // !DATA_STRUCT_STACK_BASE_H
