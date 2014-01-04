#include "DrawGL.h"

void DrawGL::InitOldCpp ()
        {
		mainWindow = NULL;
		ManagerGR = NULL;
		EventEngine = NULL;
		DeltaX = 0;
		DeltaY = 0;
	}
bool DrawGL::GLErrorTest (string FuntionName)
        {
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
		{
			EventEngine->SystemEvents.GraphicsError("OpenGL error in function " + FuntionName + " : " + to_string(static_cast<long long>(static_cast<int>(Error))));
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

		glEnable(GL_TEXTURE_2D);

		glViewport(0, 0, WinWidth, WinHeight);

		glMatrixMode(GL_PROJECTION);

		glOrtho(0, WinWidth, WinHeight, 0, 0.f, 4.f);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClear(GL_COLOR_BUFFER_BIT);

		return GLErrorTest("InitOpenGL()");

	}

void DrawGL::AddToBufferFROMTEXTURE(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextureInfo TextureData,GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
        {
        	float KX = TextureData.KxKy.KX;
        	float KY = TextureData.KxKy.KY;
        	GLuint TextureID = TextureData.TextureID;
			glTranslatef(X + DeltaX, Y + DeltaY, 0.0);

			glRotatef(AngleX, 1.0, 0.0, 0.0);
			glRotatef(AngleY, 0.0, 1.0, 0.0);
			glRotatef(AngleZ, 0.0, 0.0, 1.0);

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

		
			glBindTexture(GL_TEXTURE_2D, 0);
			
			glBindTexture(GL_TEXTURE_2D, TextureID);
			
			glVertexPointer(3, GL_FLOAT, 0, &Trg1Sz);
			
			glTexCoordPointer(2, GL_FLOAT, 0, &Trg1Crd);
			
			glDrawArrays(GL_TRIANGLES, 0, 3);
			

			glVertexPointer(3, GL_FLOAT, 0, &Trg2Sz);
			
			glTexCoordPointer(2, GL_FLOAT, 0, &Trg2Crd);
			
			glDrawArrays(GL_TRIANGLES, 0, 3);
			

			glLoadIdentity();


			GLErrorTest("AddToBufferFROMTEXTURE()");
	}
void DrawGL::AddToBufferFROMPATH (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
        {
		TextureInfo TextureID = ManagerGR->LoaderGL(Path);
		AddToBufferFROMTEXTURE(X, Y, H, W, TextureID, AngleX, AngleY, AngleZ);
	}
void DrawGL::AddToBufferFROMTEXT (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
        {
		TextureInfo TextureID = ManagerGR->GetTextImageGL(Font, Text, DrawMode, Foreground, Background);
		AddToBufferFROMTEXTURE(X, Y, H, W, TextureID, AngleX, AngleY, AngleZ);
	}
DrawGL::DrawGL (GraphicsManager * ManagerGR, SDL_Window * mainWindow, int Height, int Width, EventingEngine * Events)
        {
		InitOldCpp();
		this->ManagerGR = ManagerGR;
		this->mainWindow = mainWindow;
		this->EventEngine = Events;
		this->WinHeight = Height;
		this->WinWidth = Width;
		if (InitOpenGL() == false)
		{
			EventEngine->SystemEvents.GraphicsError("OpenGL initialization error in function DrawGL().");
		}
	}
DrawGL::~ DrawGL ()
        {
		ManagerGR->ClearPreLoadGL(1.0);
		SDL_GL_MakeCurrent(NULL, NULL);
		SDL_GL_DeleteContext(ContextGL);
	}
void DrawGL::SetViewPort (int X, int Y, int Height, int Width)
    {
		glViewport(X, Y, Width, Height);
		//DeltaX = X;
		//DeltaY = Y;
		
	}
void DrawGL::StartBuffer ()
        {
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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
void DrawGL::PushBuffer ()
        {
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
		SDL_GL_SwapWindow(mainWindow);
	}
void DrawGL::ClearAll ()
        {
		ManagerGR->ClearPreLoadGL(1.0);
	}

