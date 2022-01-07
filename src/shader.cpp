#include "shader.h"

#include <fstream>
#include <iostream>

static const std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName) {

    program = glCreateProgram();
    shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for (unsigned int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(program, shaders[i]);

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texCoord");

    glLinkProgram(program);
    CheckShaderError(program, GL_LINK_STATUS, true, "Program linking failed");

    glValidateProgram(program);
    CheckShaderError(program, GL_VALIDATE_STATUS, true, "Program is invalid");
}

Shader::~Shader() {

    for (unsigned int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    glDeleteProgram(program);
}

void Shader::Bind() {

    glUseProgram(program);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType) {

    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
        std::cerr << "Shader creation failed" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed");

    return shader;
}

static const std::string LoadShader (const std::string& fileName) {
    
    std::ifstream file;
    file.open(fileName);

    std::string output;
    std::string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

static void CheckShaderError (GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg) {

    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE) {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMsg << ": '" << strtok(error, "\n") << "'" << std::endl;
    }
}