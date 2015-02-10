#include "Sprite.h"



Sprite::Sprite(const char* o_fileName, float o_loc[2], int o_size[2])
{
	int imageWidth, imageHeight;
	bpp = 4;
	//Use load texture to apply texture to sprite I
	spriteID = loadTexture(o_fileName, imageWidth, imageHeight, bpp);
	
	//loading values into vec4 for uv coordinates
	float UVx = 0.f, UVy = .5f, UVz = .16f, UVw = 1.f;
	UVList.push_back(glm::vec2(UVx, UVy));
	UVList.emplace_back(glm::vec2(UVx, UVw));
	UVList.emplace_back(glm::vec2(UVz, UVw));
	UVList.emplace_back(glm::vec2(UVz, UVy));
	
	//vertex one
	vertices[0].position[0] = o_loc[0] - o_size[0] * .5f;
	vertices[0].position[1] = o_loc[1] - o_size[1] * .5f;
	vertices[0].uv[0] = UVList[0].x;
	vertices[0].uv[1] = UVList[0].y;

	//vertex two
	vertices[1].position[0] = o_loc[0] - o_size[0] * .5f;
	vertices[1].position[1] = o_loc[1] + o_size[1] * .5f;
	vertices[1].uv[0] = UVList[1].x;
	vertices[1].uv[1] = UVList[1].y;

	//Vertex three
	vertices[2].position[0] = o_loc[0] + o_size[0] * .5f;
	vertices[2].position[1] = o_loc[1] + o_size[1] * .5f;
	vertices[2].uv[0] = UVList[2].x;
	vertices[2].uv[1] = UVList[2].y;

	//Vertex four
	vertices[3].position[0] = o_loc[0] + o_size[0] * .5f;
	vertices[3].position[1] = o_loc[1] - o_size[1] * .5f;
	vertices[3].uv[0] = UVList[3].x;
	vertices[3].uv[1] = UVList[3].y;

	//uniform values for vertices
	for (int i = 0; i < 4; i++)
	{
		vertices[i].position[2] = 0.0f;
		vertices[i].position[3] = 1.0f;
		vertices[i].color[0] = 1.f;
		vertices[i].color[1] = 1.f;
		vertices[i].color[2] = 1.f;
		vertices[i].color[3] = 1.f;
		//vertices[i].uv[i] = UVList.push_back(glm::vec2(UVList[i].x, UVList[i].y));
		//vertices[i].uv[0] = UVList[i].x;
		//vertices[i].uv[1] = UVList[i].y;
	}

	//create VBO and IBO for object
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}

Sprite::Sprite(const char* o_fileName, float o_loc[2], int o_size[2], std::vector<glm::vec2> UVList)
{
	int imageWidth, imageHeight;
	bpp = 4;
	//Use load texture to apply texture to sprite I
	spriteID = loadTexture(o_fileName, imageWidth, imageHeight, bpp);
	//vertex one
	vertices[0].position[0] = o_loc[0] - o_size[0] * .5f;
	vertices[0].position[1] = o_loc[1] - o_size[1] * .5f;

	//vertex two
	vertices[1].position[0] = o_loc[0] - o_size[0] * .5f;
	vertices[1].position[1] = o_loc[1] + o_size[1] * .5f;

	//Vertex three
	vertices[2].position[0] = o_loc[0] + o_size[0] * .5f;
	vertices[2].position[1] = o_loc[1] + o_size[1] * .5f;

	//Vertex four
	vertices[3].position[0] = o_loc[0] + o_size[0] * .5f;
	vertices[3].position[1] = o_loc[1] - o_size[1] * .5f;

	//uniform values for vertices
	for (int i = 0; i < 4; i++)
	{
		vertices[i].position[2] = 0.0f;
		vertices[i].position[3] = 1.0f;
		vertices[i].color[0] = 1.f;
		vertices[i].color[1] = 1.f;
		vertices[i].color[2] = 1.f;
		vertices[i].color[3] = 1.f;
		//vertices[i].uv.push_back(glm::vec2(UVList[i].x, UVList[i].y));
		vertices[i].uv[0] = UVList[i].x;
		vertices[i].uv[1] = UVList[i].y;
	}
	//loading values into vec4 for uv coordinates
	float x = 0.f, y = .5f, z = .16f, w = 1.f;
	UVList.push_back(glm::vec2(x, y));
	UVList.emplace_back(glm::vec2(x, w));
	UVList.emplace_back(glm::vec2(z, w));
	UVList.emplace_back(glm::vec2(z, y));

	//create VBO and IBO for object
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}

Sprite::Sprite(const char* oFileName)
{
	Singleton * myGlobal = Singleton::GetInstance();
	
	int imageWidth, imageHeight;
	float fontSheetWidth, fontSheetHeight;
	spriteID = loadTexture(oFileName, imageWidth, imageHeight, bpp);
	fontSheetHeight = fontSheetWidth = imageHeight;
	for (int i = 0; i < 4; i++)
	{
		vertices[i].position[2] = 0.0f;
		vertices[i].position[3] = 1.0f;
		vertices[i].color[0] = 1.f;
		vertices[i].color[1] = 1.f;
		vertices[i].color[2] = 1.f;
		vertices[i].color[3] = 1.f;
	}

	//create VBO and IBO for object
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}

unsigned int Sprite::loadTexture(const char* o_fileName, int & a_iWidth, int & a_iHeight, int & a_iBPP)
{
	unsigned int uiTextureID = 0;
	//check file exists
	if (o_fileName != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(o_fileName, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_RGBA);

		//check for successful read
		if (pImageData)
		{
			//create opengl texture handle
			uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
				SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
			//clear what was read in from file now that it is stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if (uiTextureID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		return uiTextureID;
	}
}

void Sprite::UpdateVertices(float o_loc[2], int o_size[2])
{
	//vertex one
	vertices[0].position[0] = o_loc[0] - o_size[0] * .5f;
	vertices[0].position[1] = o_loc[1] - o_size[1] * .5f;

	//vertex two
	vertices[1].position[0] = o_loc[0] - o_size[0] * .5f;
	vertices[1].position[1] = o_loc[1] + o_size[1] * .5f;

	//Vertex three
	vertices[2].position[0] = o_loc[0] + o_size[0] * .5f;
	vertices[2].position[1] = o_loc[1] + o_size[1] * .5f;

	//Vertex four
	vertices[3].position[0] = o_loc[0] + o_size[0] * .5f;
	vertices[3].position[1] = o_loc[1] - o_size[1] * .5f;
}

void Sprite::UpdateChar(char ch, int location[2])
{
	Singleton * myGlobal = Singleton::GetInstance();
	float imageWidth,imageHeight;
	imageWidth = imageHeight = 256;

	vertices[0].position[0] = location[0] - .5f * myGlobal->CharMap[ch].width - .5f * myGlobal->CharMap[ch].xOffset;
	vertices[0].position[1] = location[1] - .5f * myGlobal->CharMap[ch].height - .5f * myGlobal->CharMap[ch].yOffset;
	vertices[0].uv[0] = myGlobal->CharMap[ch].x0 / imageWidth;
	vertices[0].uv[1] = myGlobal->CharMap[ch].y1 / imageHeight;

	vertices[1].position[0] = location[0] - .5f * myGlobal->CharMap[ch].width - .5f * myGlobal->CharMap[ch].xOffset;
	vertices[1].position[1] = location[1] + .5f * myGlobal->CharMap[ch].height - .5f * myGlobal->CharMap[ch].yOffset;
	vertices[1].uv[0] = myGlobal->CharMap[ch].x0 / imageWidth;
	vertices[1].uv[1] = myGlobal->CharMap[ch].y0 / imageHeight;

	vertices[2].position[0] = location[0] + .5f * myGlobal->CharMap[ch].width - .5f * myGlobal->CharMap[ch].xOffset;
	vertices[2].position[1] = location[1] + .5f * myGlobal->CharMap[ch].height - .5f * myGlobal->CharMap[ch].yOffset;
	vertices[2].uv[0] = myGlobal->CharMap[ch].x1 / imageWidth;
	vertices[2].uv[1] = myGlobal->CharMap[ch].y0 / imageHeight;

	vertices[3].position[0] = location[0] + .5f * myGlobal->CharMap[ch].width - .5f * myGlobal->CharMap[ch].xOffset;
	vertices[3].position[1] = location[1] - .5f * myGlobal->CharMap[ch].height - .5f * myGlobal->CharMap[ch].yOffset;
	vertices[3].uv[0] = myGlobal->CharMap[ch].x1 / imageWidth;
	vertices[3].uv[1] = myGlobal->CharMap[ch].y1 / imageHeight;
}
