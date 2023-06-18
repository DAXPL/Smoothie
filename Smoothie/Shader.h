#pragma once
#include <iostream>
#include <GL/glew.h>
#include <fstream>
#include <string>
#include <sstream>

class Shader 
{
public: 
	unsigned int ID;
	Shader(const char* file, bool debugInfo = false);

	void Activate();
	void Delete();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};