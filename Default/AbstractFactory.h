#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CObj*		Create(float _iX, float _iY)
	{
		CObj*		pInstance = new T;
		pInstance->Set_Pos(_iX, _iY);
		pInstance->Initialize();

		return pInstance;
	}

public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};
