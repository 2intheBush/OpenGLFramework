#include "Sprite.h"

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

	//create VBO and IBO for object
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}

Sprite::Sprite(const char* oFileName, unsigned int location[2], unsigned int size[2], unsigned int offset[2])
{
	int imageWidth, imageHeight;
	spriteID = loadTexture(oFileName, imageWidth, imageHeight, bpp);
	unsigned int bpp = 4;
	vertices[0].position[0] = location[0] - size[0] + offset[0];
	vertices[0].position[1] = location[1] - size[1] + offset[1];
	vertices[0].uv[0] = imageWidth / vertices[0].position[0];
	vertices[0].uv[1] = imageHeight / vertices[0].position[1];

	vertices[1].position[0] = location[0] - size[0] + offset[0];
	vertices[1].position[1] = location[1] + size[1] + offset[1];
	vertices[1].uv[0] = imageWidth / vertices[1].position[0];
	vertices[1].uv[1] = imageHeight / vertices[1].position[1];
	
	vertices[2].position[0] = location[0] + size[0] + offset[0];
	vertices[2].position[1] = location[1] + size[1] + offset[1];
	vertices[2].uv[0] = imageWidth / vertices[2].position[0];
	vertices[2].uv[1] = imageHeight / vertices[2].position[1];

	vertices[3].position[0] = location[0] + size[0] + offset[0];
	vertices[3].position[1] = location[1] - size[1] + offset[1];
	vertices[3].uv[0] = imageWidth / vertices[3].position[0];
	vertices[3].uv[1] = imageHeight / vertices[3].position[1];

	for (int i = 0; i < 4; i++)
	{
		vertices[i].position[2] = 0.0f;
		vertices[i].position[3] = 1.0f;
		vertices[i].color[0] = 1.f;
		vertices[i].color[1] = 1.f;
		vertices[i].color[2] = 1.f;
		vertices[i].color[3] = 1.f;
	}
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
