#include "Shader.h"

Shader::Shader(const char* filepath)
{
    std::ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = 0, VERTEX = 1, FRAGMENT = 2
    };

    std::string line;
    std::string sources[3];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            sources[(int)type] += (line + '\n');
        }
    }
    /*
    std::cout << "Shaders parsed!" << std::endl;
    std::cout << "vertex: " << std::endl << sources[1]<< std::endl;
    std::cout << "fragment:"<< std::endl << sources[2]<< std::endl;
    std::cout << "trash:" << std::endl << sources[0] << std::endl;
    */

    ID =  CreateShader(sources[1], sources[2]);
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //dolaczanie shaderow do programu
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    //Error handling
    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        std::cout << "FAILED TO LINK " << std::endl;
    }
    //shadery dolaczone - mozemy zwolnic pamiec
    //chill - sa juz zapisane w programie
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();//lub &source[0] - wskaznik do poczatku 
    glShaderSource(id, 1, &src, nullptr);//co, ile, wskaznik do wskaznika do zrodla, dlugosc
    glCompileShader(id);

    //Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*)alloca(len * sizeof(char));//alloc on stack
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << "FAILED TO COMPILE "
            << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
            << " SHADER!"
            << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
void Shader::Activate()
{
    glUseProgram(ID);
}
void Shader::Delete()
{
    glDeleteProgram(ID);
}