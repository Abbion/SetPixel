#ifndef _SP_BITMAP_LAODER_H_
#define _SP_BITMAP_LAODER_H_
#include <string>
#include "spVector.h"
#include "spColor.h"


namespace sp {
	
	//BMP - 24/32 bit, non-RLE, non-transparent
	//Loads and manages BMP images
	class BitMapTexture
	{
	public:
		BitMapTexture(const std::string& filepath, bool vFlip, bool alpha = false, const sp::Color& alphaColor = sp::Color(1.0, 0.0, 1.0));
		~BitMapTexture();

		sp::Color sampleFragment(const sp::vector2f& pos) const;
		sp::vector2i getSize() const;
		bool hasAlpha() const;
		const sp::Color getAlphaColor() const;

		void FreeData();

	private:
		unsigned int 	m_width;
		unsigned int 	m_height;
		unsigned char*	m_data;
		bool			m_alpha;
		sp::Color		m_alphaColor;

	private:
		bool load(const std::string& filepath, const bool VFlip);

		void VerticalFlip();
		bool m_LoadBMP(std::fstream& file, const bool VFlip);
	};
}


#endif //BITMAP_LOADER