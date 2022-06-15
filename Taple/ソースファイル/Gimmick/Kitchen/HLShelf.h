//===================================================== =
//									  LShelf.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ```````````````
// 2020/11/** §ìŠJn
//		01/23 LšƒLƒbƒ`ƒ“’I
//```````````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define HLSHELF_SIZE_X (1)
#define HLSHELF_SIZE_Y (5)
#define HLSHELF_SIZE_Z (1)


class HLShelf :public Gimmick //ƒLƒbƒ`ƒ“’IƒNƒ‰ƒX
{
public:
	HLShelf(void) {}
	virtual ~HLShelf(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
