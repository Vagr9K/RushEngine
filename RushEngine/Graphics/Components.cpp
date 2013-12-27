#include "Components.h"
void TextFont::InitOldCpp ()
        {
		PointSize=12;
		FontOutline =0;
		FontStyle = NORMAL;
		Index = 0;
		FontKerning = false;
	}
TextFont::TextFont (string FontPath)
        {
		InitOldCpp();
		this->FontPath = FontPath;

	}

