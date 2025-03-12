#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename,GLenum shaderType) {
    auto shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType))
      return nullptr;
    return std::move(shader);
    // 유니크 포인터 타입으로 지정된 shader 를 Loadfile 함수에 넣어서
    //bool타입 리턴 함수이기 때문에 true를 리턴하면 초기화에 성공해서 move(shader)명령을 
    //통해 소유권이 함수 바깥으로 나갈 수 있게 된다
    //false를 리턴하면  shader는 nullptr로 초기화되고
    }

    bool Shader::LoadFile(const std::string& filename, GLenum shaderType) {
        auto result = LoadTextFile(filename);
        if (!result.has_value())
          return false; 
    
        auto& code = result.value();
        const char* codePtr = code.c_str();
        int32_t codeLength = (int32_t)code.length();

        // create and compile shader
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader);

      // check compile error
    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
    }