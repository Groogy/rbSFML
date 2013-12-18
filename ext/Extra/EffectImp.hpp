/* Copyright (C) 2013 Henrik Valter Vogelius Hansson (groogy@groogy.se)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef EXTRA_EFFECT_IMP_HPP
#define EXTRA_EFFECT_IMP_HPP

#include <map>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

enum class ShaderType
{
    None,
    Vertex,
    Geometry,
    Fragment,
    Count
};

class ShaderException : public std::runtime_error
{
public:
    ShaderException(ShaderType type, const std::string& message);
    ShaderException(const std::string& message);
    ~ShaderException() throw();
};

struct ShaderDepthSettings
{
    enum Function
    {
        Always          = GL_ALWAYS,
        Never           = GL_NEVER,
        Less            = GL_LESS,
        Greater         = GL_GREATER,
        LessEqual       = GL_LEQUAL,
        GreaterEqual    = GL_GEQUAL,
        Equal           = GL_EQUAL,
        NotEqual        = GL_NOTEQUAL

    };
    bool enabled;
    Function function;
};

struct ShaderStencilSettings
{
  enum Function
  {
    Always          = GL_ALWAYS,
    Never           = GL_NEVER,
    Less            = GL_LESS,
    Greater         = GL_GREATER,
    LessEqual       = GL_LEQUAL,
    GreaterEqual    = GL_GEQUAL,
    Equal           = GL_EQUAL,
    NotEqual        = GL_NOTEQUAL    
  };
  
  enum Operation
  {
    Keep            = GL_KEEP,
    Zero            = GL_ZERO,
    Replace         = GL_REPLACE,
    Increase        = GL_INCR,
    IncreaseWrap    = GL_INCR_WRAP,
    Decrease        = GL_DECR,
    DecreaseWrap    = GL_DECR_WRAP,
    Invert          = GL_INVERT
  };
  
  bool enabled;
  Function function;
  int reference;
  unsigned int andMask;
  unsigned int mask;
  Operation testFail;
  Operation depthFail;
  Operation testPass;
  
};

struct ShaderBlendSettings
{
    enum Factor
    {
        One                         = GL_ONE,
        Zero                        = GL_ZERO,
        Source                      = GL_SRC_COLOR,
        OneMinusSource              = GL_ONE_MINUS_SRC_COLOR,
        Destination                 = GL_DST_COLOR,
        OneMinusDesitnation         = GL_ONE_MINUS_DST_COLOR,
        SourceAlpha                 = GL_SRC_ALPHA,
        OneMinusSourceAlpha         = GL_ONE_MINUS_SRC_ALPHA,
        DestinationAlpha            = GL_DST_ALPHA,
        OneMinusDestinationAlpha    = GL_ONE_MINUS_DST_ALPHA,
        Constant                    = GL_CONSTANT_COLOR,
        OneMinusConstant            = GL_ONE_MINUS_CONSTANT_COLOR,
        ConstantAlpha               = GL_CONSTANT_ALPHA,
        OneMinusConstantAlpha       = GL_ONE_MINUS_CONSTANT_ALPHA
    };

    enum Function
    {
        Add                 = GL_FUNC_ADD,
        Subtract            = GL_FUNC_SUBTRACT,
        ReverseSubstract    = GL_FUNC_REVERSE_SUBTRACT,
        Min                 = GL_MIN,
        Max                 = GL_MAX
    };

    bool enabled;
    Factor sourceFactor;
    Factor destinationFactor;
    Function function;
};

class ShaderParser : public sf::NonCopyable
{
public:
    struct PreParseCommand
    {
        std::string tag;
        std::function<std::string(std::string, ShaderParser&)> parser;
    };

    ShaderParser();
    ~ShaderParser();

    void parseFile(const std::string& path);
    void parse(const std::string& source);

    void setDefine(const std::string& define, const std::string& value);
    const std::string& getDefine(const std::string& define) const;
    bool hasDefine(const std::string& define) const;
    std::string getDefineSource() const;

    bool hasShader(ShaderType type) const;

    const std::string& getFullShaderSource() const;
    std::string getShaderSource(ShaderType type) const;

    const ShaderDepthSettings& getDepthSettings() const;
    const ShaderStencilSettings& getStencilSettings() const;
    const ShaderBlendSettings& getBlendSettings() const;

    const std::string& getFilePath() const;
    std::string getDirectory() const;

private:
    std::string preProcess(std::string source);
    std::size_t parseSourceFrom(std::size_t startIndex, std::string& resultingSource);
    std::size_t appendSourceTo(ShaderType type, std::size_t startIndex);
    std::size_t parseDepthSettings(std::size_t startIndex);
    std::size_t parseStencilSettings(std::size_t startIndex);
    std::size_t parseBlendSettings(std::size_t startIndex);

    std::string myFilePath;
    std::string mySource;
    std::map<std::string, std::string> myDefines;
    std::map<std::string, std::string> myCustomDefines;
    std::vector<PreParseCommand> myPreParseCommands;
    std::array<std::string, static_cast<std::size_t>(ShaderType::Count)> myShaderSources;
    ShaderDepthSettings myDepthSettings;
    ShaderStencilSettings myStencilSettings;
    ShaderBlendSettings myBlendSettings;
};

class ShaderObject : sf::NonCopyable
{
public:
    ShaderObject();
    ~ShaderObject();

    void loadFromFile(const std::string& path, ShaderType type);
    void loadFromString(const std::string& source, ShaderType type);

protected:
    friend class Shader;

    GLuint getGLIdentifier() const;

private:
    ShaderType myType;
    GLuint myShaderID;
};

class Shader : sf::NonCopyable
{
public:
    Shader();
    ~Shader();

    void loadFromFile(const std::string& path);
    void loadFromString(const std::string& source);
    void loadFromParser(const ShaderParser& parser);

    void setParameter(const std::string& name, float value);
    void setParameter(const std::string& name, float value1, float value2);
    void setParameter(const std::string& name, float value1, float value2, float value3);
    void setParameter(const std::string& name, float value1, float value2, float value3, float value4);
    void setParameter(const std::string& name, const sf::Vector2f& value);
    void setParameter(const std::string& name, const sf::Vector3f& value);
    void setParameter(const std::string& name, const sf::Texture& value);

    void bind(bool useSettings = true) const;
    void unbind() const;

private:
    GLint getUniformLocation(const std::string& name);

    GLuint myShaderProgram;
    std::vector<std::unique_ptr<ShaderObject>> myObjects;
    std::map<std::string, GLint> myUniforms;
    std::map<GLint, const sf::Texture*> myTextures;
    ShaderDepthSettings myDepthSettings;
    ShaderStencilSettings myStencilSettings;
    ShaderBlendSettings myBlendSettings;

};

#endif // EXTRA_EFFECT_IMP_HPP
