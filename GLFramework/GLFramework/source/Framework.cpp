#include "framework.h"



GLuint GLF::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint GLF::CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

const float* GLF::getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	float * toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}

void GLF::DrawSprite(Sprite& s_object)
{
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_ALPHA);
	glFrontFace(GL_CW);
	
	//check if Index buffer succeeded
	if (&s_object.uiIBO != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_object.uiIBO);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 4; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	//check if vertex buffer succeeded
	if (&s_object.uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, s_object.uiVBO);

		//allocate space on graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 4, NULL, GL_STATIC_DRAW);

		//get pointer to allocate space on graphics card
		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy to graphics card
		memcpy(vSBuffer, &s_object.vertices, sizeof(Vertex)* 4);

		//unmap and unbind
		glUnmapBuffer(GL_ARRAY_BUFFER);
		
	}


	//class shader program
	glUseProgram(uiProgramTextured);
	//ortho project onto shader
	glUniformMatrix4fv(MatrixIDTextured, 1, GL_FALSE, ortho);

	//bind VBO
	glBindTexture(GL_TEXTURE_2D, s_object.spriteID);
	glBindBuffer(GL_ARRAY_BUFFER, s_object.uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_object.uiIBO);


	//enable vertex array state
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	//specify where our vertex array is
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));
	//now we have UVs, we need to send that info to the graphics card
	/*
	this is where you tell the GPU how to extract each piece of data from the blob of data you are sending it,
	each Vertex struct has data and you have to tell it how it's structured as a whole, not each piece.
	the last param is where each piece of data starts in memory per vertex chunk.
	for each vertex chunk the vertices start at beginning (0) and are size of 4 floats, then there is color info
	this starts after the vertices, so it's 0 + the 4 floats and itself is size of 4 floats, then it's the
	UV coords which will start after (0 + 4 + 4) = 8.
	*/
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(std::vector<glm::vec2>), (void*)(sizeof(float)* 8));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));

	//draw to the screen
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, NULL);

	//unbind buffers 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}


bool GLF::IsMousePressed(KeyPressed key)
{
	return glfwGetMouseButton(Singleton::GetInstance()->window, key);
}

glm::vec2 GLF::MousePosition()
{
	double xPos;
	double yPos;
	
	glfwGetCursorPos(Singleton::GetInstance()->window, &xPos, &yPos);
	return glm::vec2(xPos, yPos);
}

void GLF::AnimateSprite(Sprite& a_sprite)
{
	float DistanceToNextAnim = a_sprite.vertices[3].uv[0] - a_sprite.vertices[0].uv[0] + .001;
	
	a_sprite.vertices[0].uv[0] += DistanceToNextAnim;

	a_sprite.vertices[1].uv[0] += DistanceToNextAnim;

	a_sprite.vertices[2].uv[0] += DistanceToNextAnim;

	a_sprite.vertices[3].uv[0] += DistanceToNextAnim;

}

void GLF::LoadCharMap(const char* pFileName)
{
	dump_to_stdout(pFileName);

	Singleton * myGlobal = Singleton::GetInstance();
	
	for (childElement = cursor; childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		CharValues TempChar;
		TempChar.id = childElement->IntAttribute("id");
		TempChar.x0 = childElement->IntAttribute("x");
		TempChar.y0 = childElement->IntAttribute("y");
		TempChar.width = childElement->IntAttribute("width");
		TempChar.height = childElement->IntAttribute("height");
		TempChar.x1 = TempChar.x0 + TempChar.width;
		TempChar.y1 = TempChar.y0 + TempChar.height;
		TempChar.xOffset = childElement->IntAttribute("xoffset");
		TempChar.yOffset = childElement->IntAttribute("yoffset");
		TempChar.xAdvance = childElement->IntAttribute("xadvance");
		myGlobal->CharMap.emplace(std::pair<int, CharValues>(TempChar.id, TempChar));
	}
	printf("Text Attributes Loaded\n");
} 

void GLF::DrawString(const char* str, int xPos, int yPos)
{
	Singleton * myGlobal = Singleton::GetInstance();
	while (*str)
	{
		DrawChar(*str, xPos, yPos);
		xPos += myGlobal->CharMap[*str].xAdvance;
		str++;
	}
}

void GLF::DrawChar(char ch, int xPos, int yPos)
{
	int location[2]{xPos, yPos};
	Sprite s("resources\\images\\Arial_0.png",location, ch);
	DrawSprite(s);
}
