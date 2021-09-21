#include "../include/Shader.h"
#include "../include/Utilities.h"

struct Shader::UniformBinder {
    UniformBinder(Shader& shader, const char* name) {
        location = glGetUniformLocation(shader.m_ShaderProgram, name);
    }
    
    int location;
};

Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_ShaderProgram(glCreateProgram()), m_VertexShader(glCreateShader(GL_VERTEX_SHADER)), m_FragmentShader(glCreateShader(GL_FRAGMENT_SHADER)) {
    Create(vertexPath, fragmentPath);
}

void Shader::Initialize() {
    m_ShaderProgram = glCreateProgram();
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}

void Shader::Create(const char* vertexPath, const char* fragmentPath) {
    //Used for compile / linking status checks
    char errorBuf[512];
    int success;

    //Setting up vertex shader
    std::string vertexSource = ReadFile(vertexPath);
    const char* vs = vertexSource.c_str();
    glShaderSource(m_VertexShader, 1, &vs, nullptr);
    glCompileShader(m_VertexShader);
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_VertexShader, 512, nullptr, errorBuf);
        std::cout << "COMPILE ERROR >> FAILED TO COMPILE VERTEX SHADER" << std::endl << errorBuf;
    }

    //Setting up fragment shader
    std::string fragmentSource = ReadFile(fragmentPath);
    const char* fs = fragmentSource.c_str();
    glShaderSource(m_FragmentShader, 1, &fs, nullptr);
    glCompileShader(m_FragmentShader);
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_VertexShader, 512, nullptr, errorBuf);
        std::cout << "COMPILE ERROR >> FAILED TO COMPILE FRAGMENT SHADER" << std::endl << errorBuf;
    }

    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);
    glLinkProgram(m_ShaderProgram);
    glad_glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderProgram, 512, nullptr, errorBuf);
        std::cout << "LINKING ERROR >> FAILED TO LINK SHADER PROGRAM" << std::endl << errorBuf;
    }

    //Cleaning up
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

void Shader::SetUniform(const char* name, bool value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform1i(binder.location, value);
    }
}

void Shader::SetUniform(const char* name, float value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform1f(binder.location, value);
    }
}

void Shader::SetUniform(const char* name, int32_t value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform1i(binder.location, value);
    }
}

void Shader::SetUniform(const char* name, uint32_t value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform1ui(binder.location, value);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec2b value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform2i(binder.location, value.x, value.y);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec2f value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform2f(binder.location, value.x, value.y);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec2i value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform2i(binder.location, value.x, value.y);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec2ui value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform2ui(binder.location, value.x, value.y);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec3b value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform3i(binder.location, value.x, value.y, value.z);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec3f value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform3f(binder.location, value.x, value.y, value.z);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec3i value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform3i(binder.location, value.x, value.y, value.z);
    }
}

void Shader::SetUniform(const char* name, const glsl::vec::vec3ui value) {
    UniformBinder binder(*this, name);
    if (binder.location != -1) {
        glUniform3ui(binder.location, value.x, value.y, value.z);
    }
}

void Shader::Use() {
    glUseProgram(m_ShaderProgram);
}

unsigned Shader::ID() {
    return m_ShaderProgram;
}