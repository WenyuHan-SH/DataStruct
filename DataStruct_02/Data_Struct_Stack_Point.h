#ifndef DATA_STRUCT_STACK_POINT_H
#define DATA_STRUCT_STACK_POINT_H
#include "Data_Struct_Stack_Base.h"

class StackPoint :public Stack
{
public:
	StackPoint() = default;
	Status InitStack()override;
	Status DestroyStack() override;
	Status ClearStack() override;
	int StackLength() const override;
	Status GetTop(ElemType& eData)const override;
	Status Push(const ElemType& eData) override;
	Status Pop(ElemType& eData) override;

private:
	SqStackPoint m_SqStackPoint;
};

Status StackPoint::InitStack()
{
	m_SqStackPoint.base = static_cast<ElemType*>(malloc(MAXSIZE * sizeof(ElemType)));
	if (!m_SqStackPoint.base)
	{
		LogDevError("m_SqStackPoint.base is null");
		return ERROR;
	}
	m_SqStackPoint.top = m_SqStackPoint.base;
	m_SqStackPoint.stackSize = MAXSIZE;
	return OK;
}

Status StackPoint::Push(const ElemType& eData)
{
	if (m_SqStackPoint.top - m_SqStackPoint.base >= m_SqStackPoint.stackSize)
	{
		m_SqStackPoint.base = static_cast<ElemType*>(
			realloc(m_SqStackPoint.base, (m_SqStackPoint.stackSize + INCREMENT) * sizeof(ElemType)));
		if (!m_SqStackPoint.base)
		{
			LogDevError("m_SqStackPoint.base is null");
			return ERROR;
		}
		m_SqStackPoint.top = m_SqStackPoint.base + m_SqStackPoint.stackSize;
		m_SqStackPoint.stackSize += INCREMENT;
	}
	*(m_SqStackPoint.top) = eData;
	m_SqStackPoint.top++;
	return OK;
}

Status StackPoint::Pop(ElemType& eData)
{
	if (m_SqStackPoint.base == m_SqStackPoint.top)
	{
		return OVERFLOW;
	}
	eData = *--(m_SqStackPoint.top);
	return OK;
}

Status StackPoint::GetTop(ElemType& eData)const
{
	if (m_SqStackPoint.base == m_SqStackPoint.top)
	{
		return OVERFLOW;
	}
	eData = *(m_SqStackPoint.top - 1);
	return OK;
}

int StackPoint::StackLength()const
{
	return m_SqStackPoint.top - m_SqStackPoint.base;
}

Status StackPoint::ClearStack()
{
	m_SqStackPoint.top = m_SqStackPoint.base;
	return OK;
}

Status StackPoint::DestroyStack()
{
	while (m_SqStackPoint.top != m_SqStackPoint.base)
	{
		auto temp = m_SqStackPoint.top;
		m_SqStackPoint.top--;
		free(temp);
	}
	m_SqStackPoint.base = m_SqStackPoint.top = nullptr;
	m_SqStackPoint.stackSize = 0;
	return OK;
}
#endif // !DATA_STRUCT_STACK_POINT_H


