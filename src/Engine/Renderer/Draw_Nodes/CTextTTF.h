
#ifndef CTEXTTTF_H_
#define CTEXTTTF_H_

#include "CSprite.h"
#include "Resources/CFontTTF.h"

class CTextTTF: public CSprite
{
	public:
		CTextTTF();
		void		InitTextTTF(const std::string &aPathToTTF);
		void		SetTextTTF(const std::string& aText, const EV_Color &aColor, const TTextureAlign aAlign = TEXTUREALIGN_CENTER);
		void		SetTextSizeTTF(const u32 aTextSize);
		virtual 	~CTextTTF();
	private:
		CFontTTF	m_TTFont;



};

#endif /* CTEXTTTF_H_ */
