//==========================================
//									  StudyBook.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/01/05 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define STUDY_BOOK_SIZE_X (5)
#define STUDY_BOOK_SIZE_Y (1)
#define STUDY_BOOK_SIZE_Z (1)


//===== ƒNƒ‰ƒX’è‹` =====
class StudyBook :public Gimmick	// –{ƒNƒ‰ƒX
{
public:
	StudyBook(void);
	virtual ~StudyBook(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};
