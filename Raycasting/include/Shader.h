#pragma once

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "Glsl.h"

class Shader {
    struct UniformBinder;
public:
    Shader() = default;
    Shader(const char* vertexPath, const char* fragmentPath);

public:
    void Initialize();
    void Create(const char* vertexPath, const char* fragmentPath);
    void Use();
    void SetUniform(const char* name, bool value);
    void SetUniform(const char* name, float value);
    void SetUniform(const char* name, int32_t value);
    void SetUniform(const char* name, uint32_t value);

    void SetUniform(const char* name, const glsl::vec::vec2b value);
    void SetUniform(const char* name, const glsl::vec::vec2f value);
    void SetUniform(const char* name, const glsl::vec::vec2i value);
    void SetUniform(const char* name, const glsl::vec::vec2ui value);

    void SetUniform(const char* name, const glsl::vec::vec3b value);
    void SetUniform(const char* name, const glsl::vec::vec3f value);
    void SetUniform(const char* name, const glsl::vec::vec3i value);
    void SetUniform(const char* name, const glsl::vec::vec3ui value);

    unsigned ID();

private:
    static std::string ReadShaderCode(const char* path);

private:
    unsigned m_ShaderProgram;
    unsigned m_FragmentShader;
    unsigned m_VertexShader;
};