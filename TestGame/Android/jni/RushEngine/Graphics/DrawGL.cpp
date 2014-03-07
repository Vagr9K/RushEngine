#include "DrawGL.h"
#include <string>
void Ortho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
#ifdef __WINDOWS__
	glOrtho(left, right, bottom, top, zNear, zFar);
#elif __ANDROID__
	glOthof(left, right, bottom, top, zNear, zFar);
#endif
}

void DrawGL::InitOldCpp ()
        {
		mainWindow = NULL;
		ManagerGR = NULL;
		EventEngine = NULL;
		ObjEngine = NULL;
		DeltaX = 0;
		DeltaY = 0;
		AspectX = 1.f;
		AspectY = 1.f;
		ZeroWidth = 0;
		ZeroHeight = 0;
		BufferStarted = false;
		BgkC = 0;
		WorldLC = 0;
		EffectLC = 0;
		InterfaceLC = 0;
		PrevColor.R = 1.f;
		PrevColor.G = 1.f;
		PrevColor.B = 1.f;
		PrevColor.Fade = 1.f;

		BindAllGL = false;

		FrameRate = 120;
		LastFrameTime = 0;
		AllowDraw = false;
		BlendEnabled = false;
	}
bool DrawGL::GLErrorTest (string FuntionName)
        {
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
		{
			EventEngine->SystemEvents->GraphicsError("OpenGL error in function " + FuntionName + " : " + std::to_string(static_cast<long long>(static_cast<int>(Error))));
			return false;
		}
		return true;
	}
bool DrawGL::InitOpenGL ()
        {
		ContextGL = SDL_GL_CreateContext(mainWindow);
		
		SDL_GL_MakeCurrent(mainWindow, ContextGL);

		SDL_GL_SetSwapInterval(1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);


		glClearColor(0, 0, 0, 0);
#ifdef __WINDOWS__
		glClearDepth(1.f);
#else 
		glClearDepthx(1.f);
#endif
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glViewport(0, 0, WinWidth, WinHeight);

		glMatrixMode(GL_PROJECTION);

		Ortho(0, (GLfloat)WinWidth, (GLfloat)WinHeight, 0, -1.f, 1.f);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glClear(GL_COLOR_BUFFER_BIT);

		return GLErrorTest("InitOpenGL()");

	}
bool DrawGL::CheckScreenZone(float x, float y, float h, float w, bool NoDelta)
	{
		float ActX;
		float ActY;
		if (NoDelta)
		{
			ActX = x/AspectX;
			ActY = y/AspectY;
		}
		else
		{
			ActX = (x - DeltaX)/AspectX;
			ActY = (y + DeltaY)/AspectY;
		}
		h = (h / 2)/AspectY;
		w = (w / 2)/AspectX;
		if ((ActX - w) <= WinWidth && (ActX + w) >= 0 && (ActY - h) <= WinHeight && (ActY + h) >= 0)
		{
			return true;
		}
		else if (((ActX - w) >= WinWidth && (ActX + w) <= 0) || ((ActY - h) >= WinHeight && (ActY + h) <= 0))
		{
			return true;
		}
		
		return false;
	}
void DrawGL::SetEffectMode(bool Status)
{
	if (Status && !BlendEnabled)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		BlendEnabled = true;
	} 
	else if (!Status && BlendEnabled)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		BlendEnabled = false;
	}
	
	
}
void DrawGL::AddToBufferFROMTEXTURE(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextureInfo TextureData,GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ, bool NoDelta, RGBColor* TextureColor, bool BindAll)
        {
        	float KX = TextureData.KxKy.KX;
        	float KY = TextureData.KxKy.KY;
        	GLuint TextureID = TextureData.TextureID;
			
			if (NoDelta)
			{
				glTranslatef(X, Y, 0.0);
			}
			else
			{
				glTranslatef(X - DeltaX, Y + DeltaY, 0.0);
			}

			if (AngleX != 0)
				glRotatef(AngleX, 1.0, 0.0, 0.0);
			if (AngleY != 0)
				glRotatef(AngleY, 0.0, 1.0, 0.0);
			if (AngleZ != 0)
				glRotatef(AngleZ, 0.0, 0.0, 1.0);

			if (TextureColor != NULL)
			{
				if (PrevColor == *TextureColor)
				{

				}
				else
				{
					glColor4f(TextureColor->R, TextureColor->G, TextureColor->B, TextureColor->Fade);
					PrevColor = *TextureColor;
				}
			}
			else
			{
				if (PrevColor.R == 1.f && PrevColor.G == 1.f && PrevColor.B == 1.f && PrevColor.Fade == 1.f)
				{

				}
				else
				{
					glColor4f(1.f, 1.f, 1.f, 1.f);
					PrevColor.R = 1.f;
					PrevColor.G = 1.f;
					PrevColor.B = 1.f; 
					PrevColor.Fade = 1.f;
				}
			}

			GLfloat Trg1Sz[] = {
							-W/2, -H/2, 0,
							-W/2,  H/2, 0,
							 W/2,  H/2, 0
						   };
			GLfloat Trg1Crd[] = {0,0 ,0,KY ,KX,KY};
			GLfloat Trg2Sz[] = {
							-W/2, -H/2, 0,
							 W/2, -H/2, 0,
							 W/2,  H/2, 0
						   };
			GLfloat Trg2Crd[] = {0,0 ,KX,0 ,KX,KY};
			if ((BindAll == false && BindAllGL == false) && PrevTextureID != TextureID)
			{
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindTexture(GL_TEXTURE_2D, TextureID);
					PrevTextureID = TextureID;
			}
			if (BindAll == true || BindAllGL == true)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindTexture(GL_TEXTURE_2D, TextureID);
				PrevTextureID = TextureID;
			}
			glVertexPointer(3, GL_FLOAT, 0, &Trg1Sz);
			glTexCoordPointer(2, GL_FLOAT, 0, &Trg1Crd);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glVertexPointer(3, GL_FLOAT, 0, &Trg2Sz);
			glTexCoordPointer(2, GL_FLOAT, 0, &Trg2Crd);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glLoadIdentity();
#ifdef _DEBUG
			GLErrorTest("AddToBufferFROMTEXTURE()");
#endif
	}
void DrawGL::AddToBufferFROMPATH (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
    {
		if (AllowDraw)
		{
			TextureInfo TextureID = ManagerGR->LoaderGL(Path);
			AddToBufferFROMTEXTURE(X, Y, H, W, TextureID, AngleX, AngleY, AngleZ);
		}
	}
void DrawGL::AddToBufferFROMTEXT (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
   {
		if (AllowDraw)
		{
			TextureInfo TextureID = ManagerGR->GetTextImageGL(Font, Text, DrawMode, Foreground, Background);
			AddToBufferFROMTEXTURE(X, Y, H, W, TextureID, AngleX, AngleY, AngleZ);
		}
	}
DrawGL::DrawGL (GraphicsManager * ManagerGR, SDL_Window * mainWindow, EventingEngine * Events)
        {
		InitOldCpp();
		this->ManagerGR = ManagerGR;
		this->ObjEngine = ManagerGR->GetObjEngine();
		this->mainWindow = mainWindow;
		this->EventEngine = Events;
		this->WinHeight = ManagerGR->WindowData->Height;
		this->WinWidth = ManagerGR->WindowData->Width;
		this->ZeroHeight = ManagerGR->WindowData->ZeroHeight;
		this->ZeroWidth = ManagerGR->WindowData->ZeroWidth;
		if (InitOpenGL() == false)
		{
			EventEngine->SystemEvents->GraphicsError("OpenGL initialization error in function DrawGL().");
		}
		BgkC = ObjEngine->GetBackgroundLCount();
		WorldLC = ObjEngine->GetWorldLCount();
		EffectLC = ObjEngine->GetEffectLCount();
		InterfaceLC = ObjEngine->GetInterfaceLCount();
	}
DrawGL::~ DrawGL ()
        {
		
		SDL_GL_MakeCurrent(NULL, NULL);
		SDL_GL_DeleteContext(ContextGL);
	}
void DrawGL::SetView(int X, int Y)
{
		DeltaX = X;
		DeltaY = Y;
	}
void DrawGL::StartBuffer ()
   {
	if (!BufferStarted)
	{
		AllowDraw = CheckDrawAllowance();
		CheckScreenState();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		BufferStarted = true;
	}
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
        {
		AddToBufferFROMPATH(X, Y, H, W, Path, AngleX, AngleY, AngleZ);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleZ)
        {
		AddToBufferFROMPATH(X, Y, H, W, Path, 0, 0, AngleZ);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path)
        {
		AddToBufferFROMPATH(X, Y, H, W, Path, 0, 0, 0);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
        {
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, AngleX, AngleY, AngleZ);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleZ)
        {
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, AngleZ);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
        {
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, 0);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
        {
		SDL_Color Foreground;
		Foreground.a = 0;
		Foreground.b = 0;
		Foreground.r = 0;
		Foreground.g = 0;
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, AngleX, AngleY, AngleZ);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Background, GLfloat AngleZ)
        {
		SDL_Color Foreground;
		Foreground.a = 0;
		Foreground.b = 0;
		Foreground.r = 0;
		Foreground.g = 0;
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, AngleZ);
	}
void DrawGL::AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Background)
        {
		SDL_Color Foreground;
		Foreground.a = 0;
		Foreground.b = 0;
		Foreground.r = 0;
		Foreground.g = 0;
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, 0);
	}
void DrawGL::SyncObjects(bool AutoPushBuffer, ObjectSyncMode SyncTo)
	{
		float DrawFactor = GlobalDrawFactor;
		if (BufferStarted == false)
		{
			StartBuffer();
		}
		if (AllowDraw)
		{
			int LayerID = 0;
			ObjectElement* CurrentElement = NULL;
			for (LayerID = 0; LayerID < WorldLC; LayerID++)
			{

				vector<ObjectElement*>* Layer = ObjEngine->getObjectsLayer(LayerID);
				for (unsigned int LayerElementID = 0; LayerElementID < Layer->size(); LayerElementID++)
				{
					CurrentElement = Layer->at(LayerElementID);
					CurrentElement->ObjectPtr->SyncData(SyncTo);
					DrawFromLayerElement(CurrentElement, DrawFactor, SyncTo);

				}
				LayerID++;

			}
			if (AutoPushBuffer == true)
			{
				PushBuffer();
			}
		}
		

	}
void DrawGL::SyncInterface(bool AutoPushBuffer)
{

	if (BufferStarted == false)
	{
		StartBuffer();
	}
	if (AllowDraw)
	{
		int LayerID = 0;
		InterfaceElement* CurrentElement = NULL;
		for (LayerID = 0; LayerID < InterfaceLC; LayerID++)
		{

			vector<InterfaceElement*>* Layer = ObjEngine->getInterfaceLayer(LayerID);
			for (unsigned int LayerElementID = 0; LayerElementID < Layer->size(); LayerElementID++)
			{
				CurrentElement = Layer->at(LayerElementID);
				CurrentElement->InterfacePtr->Refresh();
				DrawFromInterfaceElement(CurrentElement);

			}
			LayerID++;

		}
		if (AutoPushBuffer == true)
		{
			PushBuffer();
		}

	}

}

void DrawGL::DrawFromEffectElement(EffectElement* EffectEl, EffectSyncMode SyncMode, RGBColor* ParticleColor, TextureInfo* TInfo)
{
	string Path = EffectEl->Path;
	Particle* CurrentParticle = NULL;
	bool DrawBlack = false;
	if (EffectEl->DrawMode == NOBLEND)
		SetEffectMode(false);
	else if (EffectEl->DrawMode == BLEND)
		SetEffectMode(true);
	else if (EffectEl->DrawMode == BLACKBLEND)
	{
		SetEffectMode(true);
		DrawBlack = true;
	}
	for (int i = 0; i < EffectEl->ParticleCount; i++)
	{
		CurrentParticle = &EffectEl->ParticleArray[i];
		if (CurrentParticle->Active == true && (SyncMode == ACTIVE || SyncMode == ALLEFFECTS))
		{
			float X = WinWidth - CurrentParticle->X;
			float Y = WinHeight - CurrentParticle->Y;
			float H = CurrentParticle->H;
			float W = CurrentParticle->W;

			if (CheckScreenZone(X, Y, H, W))
			{	
				if (DrawBlack)
				{
					ParticleColor->R = 0.f;
					ParticleColor->G = 0.f;
					ParticleColor->B = 0.f;
					ParticleColor->Fade = 0.f;
					SetEffectMode(false);
					AddToBufferFROMTEXTURE(
						X,
						Y,
						H*1.5f,
						W*1.5f,
						*TInfo,
						0.f,
						0.f,
						CurrentParticle->Angle,
						false,
						ParticleColor,
						false
						);
					SetEffectMode(true);
				
				}
				ParticleColor->R = CurrentParticle->R;
				ParticleColor->G = CurrentParticle->G;
				ParticleColor->B = CurrentParticle->B;
				ParticleColor->Fade = CurrentParticle->Fade;
				AddToBufferFROMTEXTURE(
					X,
					Y,
					H,
					W,
					*TInfo,
					0.f,
					0.f,
					CurrentParticle->Angle,
					false,
					ParticleColor,
					false
					);
			}
		}
		if (CurrentParticle->Active == false && (SyncMode == INACTIVE || SyncMode == ALLEFFECTS))
		{
			float X = WinWidth - CurrentParticle->X;
			float Y = WinHeight - CurrentParticle->Y;
			float H = CurrentParticle->H;
			float W = CurrentParticle->W;

			if (CheckScreenZone(X, Y, H, W))
			{
				if (DrawBlack)
				{
					ParticleColor->R = 0.f;
					ParticleColor->G = 0.f;
					ParticleColor->B = 0.f;
					ParticleColor->Fade = 0.f;
					AddToBufferFROMTEXTURE(
						X,
						Y,
						H,
						W,
						*TInfo,
						0.f,
						0.f,
						CurrentParticle->Angle,
						false,
						ParticleColor,
						false
						);

				}
				ParticleColor->R = CurrentParticle->R;
				ParticleColor->G = CurrentParticle->G;
				ParticleColor->B = CurrentParticle->B;
				ParticleColor->Fade = CurrentParticle->Fade;

				AddToBufferFROMTEXTURE(
					X / AspectX,
					Y / AspectY,
					H / AspectY,
					W / AspectX,
					*TInfo,
					0.f,
					0.f,
					CurrentParticle->Angle,
					false,
					ParticleColor,
					false
					);
			}
		}
	}
	
}
void DrawGL::DrawFromInterfaceElement(InterfaceElement* Element)
{
	if (Element->Hidden == false)
	{
	
	if (Element->ImageExists == true)
	{
		IMG* Image = Element->Image;
		float X = static_cast<GLfloat>(Image->x);
		float Y = static_cast<GLfloat>(Image->y);
		float H = static_cast<GLfloat>(Image->h);
		float W = static_cast<GLfloat>(Image->w);
		float Angle = static_cast<GLfloat>(Image->Angle);
		if (CheckScreenZone(X, Y, H, W, true))
		{
			string Path = Image->Source;
			TextureInfo TInfo = ManagerGR->LoaderGL(Path);
			AddToBufferFROMTEXTURE(X, Y, H, W, TInfo, 0.f, 0.f, Angle, true);
		}


	}
	if (Element->TextExists == true)
	{
		TXT* Text = Element->Text;
		float X = static_cast<GLfloat>(Text->x);
		float Y = static_cast<GLfloat>(Text->y);
		float H = static_cast<GLfloat>(Text->h);
		float W = static_cast<GLfloat>(Text->w);
		float Angle = static_cast<GLfloat>(Text->Angle);
		if (CheckScreenZone(X, Y, H, W))
		{
			TextFont* Font = Text->Font;
			string Contents = Text->Content;
			SDL_Color* Foreground = Text->Foreground;
			SDL_Color* Background = Text->Background;
			Mode DrawMode = Text->DrawMode;

			bool DeleteBackground = false;
			bool DeleteForeground = false;
			if (Foreground == NULL)
			{
				Foreground = new SDL_Color();
				DeleteForeground = true;
				Foreground->a = 0;
				Foreground->g = 255;
				Foreground->b = 255;
				Foreground->r = 255;
			}
			if (Background == NULL)
			{
				DeleteBackground = true;
				Background = new SDL_Color();
				Background->a = 0;
				Background->b = 0;
				Background->r = 0;
				Background->g = 0;
			}
			TextureInfo TInfo = ManagerGR->GetTextImageGL(Font, Contents, DrawMode, *Foreground, *Background);
			AddToBufferFROMTEXTURE(X, Y, H, W, TInfo, 0.f, 0.f, Angle, true);
			if (DeleteForeground)
				delete Foreground;
			if (DeleteForeground)
				delete Background;
		}
	}


	}
}
void DrawGL::SyncEffects(bool AutoPushBuffer /* = false */, EffectSyncMode SyncMode /* = ALLEFFECTS */)
{
	if (BufferStarted == false)
	{
		StartBuffer();
	}
	if (AllowDraw)
	{
		SetEffectMode(true);
		int LayerID = 0;
		EffectElement* CurrentElement = NULL;
		RGBColor* ParticleColor = new RGBColor;
		for (LayerID = 0; LayerID < EffectLC; LayerID++)
		{

			vector<EffectElement*>* Layer = ObjEngine->getEffectLayer(LayerID);
			for (unsigned int LayerElementID = 0; LayerElementID < Layer->size(); LayerElementID++)
			{
				CurrentElement = Layer->at(LayerElementID);
				CurrentElement->PtrToEffect->Refresh();
				TextureInfo TInfo = ManagerGR->LoaderGL(CurrentElement->Path);
				DrawFromEffectElement(CurrentElement, SyncMode, ParticleColor, &TInfo);

			}
			LayerID++;

		}
		delete ParticleColor;
		SetEffectMode(false);
		if (AutoPushBuffer == true)
		{
			PushBuffer();
		}
	}
}

void DrawGL::DrawFromLayerElement(ObjectElement* Element, float DrawFactor, ObjectSyncMode SyncTo)
{
	if (Element->DrawFactor > 0.f)
	{
		DrawFactor = Element->DrawFactor;
	}
	else
	{
		DrawFactor = GlobalDrawFactor;
	}

	if (Element->ImageExists == true && (SyncTo == IMAGE || SyncTo == ALL))
	{
		IMG* Image = Element->Image;
		float X = WinWidth - static_cast<GLfloat>(Image->x)*DrawFactor;
		float Y = WinHeight - static_cast<GLfloat>(Image->y)*DrawFactor;
		float H = static_cast<GLfloat>(Image->h)*DrawFactor;
		float W = static_cast<GLfloat>(Image->w)*DrawFactor;
		float Angle = static_cast<GLfloat>(Image->Angle);
		if (CheckScreenZone(X, Y, H, W))
		{
			string Path = Image->Source;
			TextureInfo TextureData = ManagerGR->LoaderGL(Path);
			AddToBufferFROMTEXTURE(X, Y, H, W, TextureData, Angle, 0.f, 0.f, false, Element->Color, false);
		}
		
		
	}
	if (Element->TextExists == true && (SyncTo == TEXT || SyncTo == ALL))
	{
		TXT* Text = Element->Text;
		float X = WinWidth - static_cast<GLfloat>(Text->x)*DrawFactor;
		float Y = WinHeight - static_cast<GLfloat>(Text->y)*DrawFactor;
		float H = static_cast<GLfloat>(Text->h)*DrawFactor;
		float W = static_cast<GLfloat>(Text->w)*DrawFactor;
		float Angle = static_cast<GLfloat>(Text->Angle);
		if (CheckScreenZone(X, Y, H, W))
		{
			TextFont* Font = Text->Font;
			string Contents = Text->Content;
			SDL_Color* Foreground = Text->Foreground;
			SDL_Color* Background = Text->Background;
			Mode DrawMode = Text->DrawMode;

			bool DeleteBackground = false;
			bool DeleteForeground = false;
			if (Foreground == NULL)
			{
				Foreground = new SDL_Color();
				DeleteForeground = true;
				Foreground->a = 0;
				Foreground->g = 255;
				Foreground->b = 255;
				Foreground->r = 255;
			}
			if (Background == NULL)
			{
				DeleteBackground = true;
				Background = new SDL_Color();
				Background->a = 0;
				Background->b = 0;
				Background->r = 0;
				Background->g = 0;
			}

			TextureInfo TextureData = ManagerGR->GetTextImageGL(Font, Contents, DrawMode, *Foreground, *Background);
			AddToBufferFROMTEXTURE(X, Y, H, W, TextureData, Angle, 0.f, 0.f, false, Element->Color, false);
			if (DeleteForeground)
				delete Foreground;
			if (DeleteBackground)
				delete Background;
		}
		
		
	}
}
void DrawGL::PushBuffer ()
   {
	if (AllowDraw)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		SDL_GL_SwapWindow(mainWindow);
		
		AllowDraw = false;
	}
	BufferStarted = false;
	}
void DrawGL::ClearAll ()
        {
		ManagerGR->ClearPreLoadGL(1.0);
		PrevTextureID = -1;
	}

void DrawGL::setSyncFactor(float Factor)
{
	if (Factor > 0)
	{
		GlobalDrawFactor = Factor;
	}
	else
	{
		GlobalDrawFactor = 1.f;
	}
	
}
float DrawGL::getSyncFactor()
{
	return GlobalDrawFactor;
}
void DrawGL::CacheImage(string Path)
{
	ManagerGR->LoaderGL(Path);
}
void DrawGL::CacheText(TextFont* Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
{
	ManagerGR->GetTextImageGL(Font, Text, DrawMode, Foreground, Background);
}

void DrawGL::SyncBackground(bool AutoPushBuffer /* = false */)
{

	if (BufferStarted == false)
	{
		StartBuffer();
	}
	if (AllowDraw)
	{
		int LayerID = 0;
		BackgroundElement* CurrentElement = NULL;
		for (LayerID = 0; LayerID < WorldLC; LayerID++)
		{

			vector<BackgroundElement*>* Layer = ObjEngine->getBackgroundLayer(LayerID);
			for (unsigned int LayerElementID = 0; LayerElementID < Layer->size(); LayerElementID++)
			{
				CurrentElement = Layer->at(LayerElementID);
				DrawFromBackgroundElement(CurrentElement);
			}
			LayerID++;

		}
		if (AutoPushBuffer == true)
		{
			PushBuffer();
		}
	}
}
void DrawGL::DrawFromBackgroundElement(BackgroundElement* Element)
{

	if (Element->ImageExists == true)
	{
		IMG* Image = Element->Image;
		float X = WinWidth - static_cast<GLfloat>(Image->x);
		float Y = WinHeight - static_cast<GLfloat>(Image->y);
		float H = static_cast<GLfloat>(Image->h);
		float W = static_cast<GLfloat>(Image->w);
		if (CheckScreenZone(X, Y, H, W))
		{
			string Path = Image->Source;
			AddToBuffer(X, Y, H, W, Path);
		}


	}
	if (Element->TextExists == true)
	{
		TXT* Text = Element->Text;
		float X = WinWidth - static_cast<GLfloat>(Text->x);
		float Y = WinHeight - static_cast<GLfloat>(Text->y);
		float H = static_cast<GLfloat>(Text->h);
		float W = static_cast<GLfloat>(Text->w);
		if (CheckScreenZone(X, Y, H, W))
		{
			
			TextFont* Font = Text->Font;
			string Contents = Text->Content;
			SDL_Color* Foreground = Text->Foreground;
			SDL_Color* Background = Text->Background;
			Mode DrawMode = Text->DrawMode;

			bool DeleteBackground = false;
			bool DeleteForeground = false;
			if (Foreground == NULL)
			{
				Foreground = new SDL_Color();
				DeleteForeground = true;
				Foreground->a = 0;
				Foreground->g = 255;
				Foreground->b = 255;
				Foreground->r = 255;
			}
			if (Background == NULL)
			{
				DeleteBackground = true;
				Background = new SDL_Color();
				Background->a = 0;
				Background->b = 0;
				Background->r = 0;
				Background->g = 0;
			}
			AddToBuffer(X, Y, H, W, Font, Contents, DrawMode, *Foreground, *Background);
			if (DeleteForeground)
				delete Foreground;
			if (DeleteBackground)
				delete Background;
		}


	}
}

void DrawGL::SyncAll(bool AutoPushBuffer /* = false */)
{
	if (BufferStarted == false)
		StartBuffer();
	if (AllowDraw)
	{
		if (BgkC > 0)
			SyncBackground();

		if (WorldLC > 0)
			SyncObjects();

		if (EffectLC > 0)
			SyncEffects();

		if (InterfaceLC > 0)
			SyncInterface();

		if (AutoPushBuffer)
		{
			PushBuffer();
		}

	}
}

void DrawGL::RefreshData(int NewWidth, int NewHeight)
{
	
	if (NewWidth == 0)
	{
		NewWidth = 1;
	}
	if (NewHeight == 0)
	{
		NewHeight = 1;
	}
	AspectX = float(ZeroWidth) / float(WinWidth);
	AspectY = float(ZeroHeight) / float(WinHeight);

	SDL_GL_DeleteContext(ContextGL);
	InitOpenGL();
	
	glViewport(0, 0, static_cast<GLsizei>(NewWidth), static_cast<GLsizei>(NewHeight));

	glMatrixMode(GL_PROJECTION);					
	glLoadIdentity();									

	AspectX = AspectY;

	Ortho(0.f, NewWidth * AspectX, NewHeight * AspectY, 0.f, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);		

	glLoadIdentity();

	WinWidth = NewWidth;
	WinHeight = NewHeight;
	ManagerGR->WindowData->Height = NewHeight;
	ManagerGR->WindowData->Width = NewWidth;
	ManagerGR->WindowData->AspectX = AspectX;
	ManagerGR->WindowData->AspectY = AspectY;

	ClearAll();

}

void DrawGL::CheckScreenState()
{
	if (EventEngine->GlobalEvent.type == SDL_WINDOWEVENT)
	{
		if (EventEngine->GlobalEvent.window.event == SDL_WINDOWEVENT_RESIZED 
			|| EventEngine->GlobalEvent.window.event == SDL_WINDOWEVENT_MAXIMIZED
			|| EventEngine->GlobalEvent.window.event == SDL_WINDOWEVENT_RESTORED
			|| EventEngine->GlobalEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			RefreshData(EventEngine->GlobalEvent.window.data1, EventEngine->GlobalEvent.window.data2);
		}
	}
}

bool DrawGL::CheckFrames()
{
	Uint32 FrameTime = SDL_GetTicks();
	if ((static_cast<float>(FrameTime - LastFrameTime) * static_cast<float>(FrameRate) / 1000.f < 1.f))
	{
		return false;
	}
	else
	{
		LastFrameTime = SDL_GetTicks();
		return true;
	}
}

bool DrawGL::CheckDrawAllowance()
{
	return CheckFrames();
}

int DrawGL::getFrameRate()
{
	return FrameRate;
}

void DrawGL::setFrameRate(int FrameRate)
{
	if (FrameRate > 30)
		this->FrameRate = FrameRate;
	else
		this->FrameRate = 30;
}
