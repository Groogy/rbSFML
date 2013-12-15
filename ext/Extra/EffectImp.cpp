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

#include <gl/glew.h>
#include <gl/gl.h>
 
#include "EffectImp.hpp"
#include <fstream>
#include <cassert>
#include <algorithm>
#include <locale>

namespace
{
    GLenum GetGLShaderType(ShaderType type)
    {
        switch(type)
        {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::Geometry:
            return GL_GEOMETRY_SHADER;
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        default:
            assert(false && "Invalid shader type");
        }
    }

    std::string GetShaderTypeAsString(ShaderType type)
    {
        switch(type)
        {
        case ShaderType::Vertex:
            return "Vertex";
        case ShaderType::Geometry:
            return "Geometry";
        case ShaderType::Fragment:
            return "Fragment";
        default:
            assert(false && "Invalid shader type");
        }
    }

    std::string stripWhitespace(const std::string& source)
    {
        std::string result;
        for(int index = 0, size = source.size(); index < size; index++)
        {
            char character = source[index];
            if(!std::isspace(character))
                result += character;
        }
        return result;
    }

    std::string getValueForSettingsParameter(const std::string& source, const std::string& symbol)
    {
        std::string fullSymbol = symbol + "=";
        std::size_t index = source.find(fullSymbol);
        if(index != std::string::npos)
        {
            index += fullSymbol.size();
            std::size_t endIndex = source.find(';', index);
            return source.substr(index, endIndex - index);
        }
        return "";
    }

    void compileSettingParameter(bool& value, const std::string& source, const std::string& symbol)
    {
        std::string valueStr = getValueForSettingsParameter(source, symbol);
        if(valueStr == "true")
        {
            value = true;
        }
        else if(valueStr == "false")
        {
            value = false;
        }
        else if(valueStr != "")
        {
            throw ShaderException("Failed to compile boolean value('" + valueStr + "') for setting '" + symbol + "'");
        }
    }

    void compileSettingsParameter(ShaderDepthSettings::Function& value, const std::string& source, const std::string& symbol)
    {
        std::string valueStr = getValueForSettingsParameter(source, symbol);
        if(valueStr == "Always")
        {
            value = ShaderDepthSettings::Function::Always;
        }
        else if(valueStr == "Never")
        {
            value = ShaderDepthSettings::Function::Never;
        }
        else if(valueStr == "Less")
        {
            value = ShaderDepthSettings::Function::Less;
        }
        else if(valueStr == "Greater")
        {
            value = ShaderDepthSettings::Function::Greater;
        }
        else if(valueStr == "LessEqual")
        {
            value = ShaderDepthSettings::Function::LessEqual;
        }
        else if(valueStr == "GreaterEqual")
        {
            value = ShaderDepthSettings::Function::GreaterEqual;
        }
        else if(valueStr == "Equal")
        {
            value = ShaderDepthSettings::Function::Equal;
        }
        else if(valueStr == "NotEqual")
        {
            value = ShaderDepthSettings::Function::NotEqual;
        }
        else if(valueStr != "")
        {
            throw ShaderException("Failed to compile boolean value('" + valueStr + "') for setting '" + symbol + "'");
        }
    }

    void compileSettingsParameter(ShaderBlendSettings::Factor& value, const std::string& source, const std::string& symbol)
    {
        std::string valueStr = getValueForSettingsParameter(source, symbol);
        if(valueStr == "One")
        {
            value = ShaderBlendSettings::Factor::One;
        }
        else if(valueStr == "Zero")
        {
            value = ShaderBlendSettings::Factor::Zero;
        }
        else if(valueStr == "Source")
        {
            value = ShaderBlendSettings::Factor::Source;
        }
        else if(valueStr == "OneMinusSource")
        {
            value = ShaderBlendSettings::Factor::OneMinusSource;
        }
        else if(valueStr == "Destination")
        {
            value = ShaderBlendSettings::Factor::Destination;
        }
        else if(valueStr == "OneMinusDesitnation")
        {
            value = ShaderBlendSettings::Factor::OneMinusDesitnation;
        }
        else if(valueStr == "SourceAlpha")
        {
            value = ShaderBlendSettings::Factor::SourceAlpha;
        }
        else if(valueStr == "OneMinusSourceAlpha")
        {
            value = ShaderBlendSettings::Factor::OneMinusSourceAlpha;
        }
        else if(valueStr == "DestinationAlpha")
        {
            value = ShaderBlendSettings::Factor::DestinationAlpha;
        }
        else if(valueStr == "OneMinusDestinationAlpha")
        {
            value = ShaderBlendSettings::Factor::OneMinusDestinationAlpha;
        }
        else if(valueStr == "Constant")
        {
            value = ShaderBlendSettings::Factor::Constant;
        }
        else if(valueStr == "OneMinusConstant")
        {
            value = ShaderBlendSettings::Factor::OneMinusConstant;
        }
        else if(valueStr == "ConstantAlpha")
        {
            value = ShaderBlendSettings::Factor::ConstantAlpha;
        }
        else if(valueStr == "OneMinusConstantAlpha")
        {
            value = ShaderBlendSettings::Factor::OneMinusConstantAlpha;
        }
        else if(valueStr != "")
        {
            throw ShaderException("Failed to compile boolean value('" + valueStr + "') for setting '" + symbol + "'");
        }
    }

    void compileSettingsParameter(ShaderBlendSettings::Function& value, const std::string& source, const std::string& symbol)
    {
        std::string valueStr = getValueForSettingsParameter(source, symbol);
        if(valueStr == "Add")
        {
            value = ShaderBlendSettings::Function::Add;
        }
        else if(valueStr == "Subtract")
        {
            value = ShaderBlendSettings::Function::Subtract;
        }
        else if(valueStr == "ReverseSubstract")
        {
            value = ShaderBlendSettings::Function::ReverseSubstract;
        }
        else if(valueStr == "Min")
        {
            value = ShaderBlendSettings::Function::Min;
        }
        else if(valueStr == "Max")
        {
            value = ShaderBlendSettings::Function::Max;
        }
        else if(valueStr != "")
        {
            throw ShaderException("Failed to compile boolean value('" + valueStr + "') for setting '" + symbol + "'");
        }
    }
}

ShaderException::ShaderException(ShaderType type, const std::string& message)
: std::runtime_error(GetShaderTypeAsString(type) + " Shader object compilation failed: " + message)
{
}

ShaderException::ShaderException(const std::string& message)
: std::runtime_error(message)
{
}

ShaderException::~ShaderException() throw()
{
}

ShaderParser::ShaderParser()
: myFilePath()
, mySource()
, myDefines()
, myCustomDefines()
, myPreParseCommands()
, myShaderSources()
, myDepthSettings()
, myBlendSettings()
{
    PreParseCommand command;
    command.tag = "#include ";
    command.parser = [](std::string argument, ShaderParser& parser) -> std::string {
        std::ifstream fileStream(argument);
        if(!fileStream.is_open())
            fileStream.open(parser.getDirectory() + '/' + argument);

        std::string source((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        return source;
    };

    myPreParseCommands.push_back(command);

    command.tag = "#define ";
    command.parser = [](std::string argument, ShaderParser& parser) -> std::string {
        std::string define = argument;
        std::string value = "";
        std::size_t defineEnd = argument.find(' ');
        if(defineEnd != std::string::npos)
        {
            define = argument.substr(0, defineEnd);
            value = argument.substr(defineEnd + 1);
        }
        parser.setDefine(define, value);
        return "#define " + argument;
    };

    myPreParseCommands.push_back(command);

    myDepthSettings.enabled = false;
    myDepthSettings.function = ShaderDepthSettings::Function::Always;

    myBlendSettings.enabled = false;
    myBlendSettings.sourceFactor = ShaderBlendSettings::Factor::One;
    myBlendSettings.destinationFactor = ShaderBlendSettings::Factor::One;
    myBlendSettings.function = ShaderBlendSettings::Function::Add;

}

ShaderParser::~ShaderParser()
{
}

void ShaderParser::parseFile(const std::string& path)
{
    myFilePath = path;
    std::ifstream fileStream(path);
    std::string source((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    parse(source);
}

void ShaderParser::parse(const std::string& source)
{
    mySource = preProcess(source);
    std::array<std::string, 5> shaderNames = {
        "vertex",
        "geometry",
        "fragment",
        "depth",
        "blend"
    };

    std::size_t startIndex = 0;
    std::size_t endIndex = 0;
    while(endIndex != std::string::npos)
    {
        endIndex = mySource.find('\n', startIndex);
        if(endIndex != std::string::npos)
        {
            std::string line = mySource.substr(startIndex, endIndex - startIndex);
            ShaderType type = ShaderType::None;
            for(std::size_t typeIndex = 0; typeIndex < 5; typeIndex++)
            {
                if(line == shaderNames[typeIndex])
                {
                    if(typeIndex <= 2)
                    {
                        type = static_cast<ShaderType>(typeIndex + 1);
                        endIndex = appendSourceTo(type, endIndex + 1);
                    }
                    else if(typeIndex == 3)
                    {
                        endIndex = parseDepthSettings(endIndex + 1);
                        type = ShaderType::Count;
                    }
                    else if(typeIndex == 4)
                    {
                        endIndex = parseBlendSettings(endIndex + 1);
                        type = ShaderType::Count;
                    }
                    break;
                }
            }

            if(type == ShaderType::None)
            {
                myShaderSources[0] += line + "\n";
            }
        }
        startIndex = endIndex + 1;
    }

}

void ShaderParser::setDefine(const std::string& define, const std::string& value)
{
    myCustomDefines.insert(std::make_pair(define, value));
}

const std::string& ShaderParser::getDefine(const std::string& define) const
{
    auto it = myCustomDefines.find(define);
    if(it != myCustomDefines.end())
        return it->second;

    it = myDefines.find(define);
    assert(it != myDefines.end());
    return it->second;
}

bool ShaderParser::hasDefine(const std::string& define) const
{
    return myCustomDefines.find(define) != myCustomDefines.end() || myDefines.find(define) != myDefines.end();
}

bool ShaderParser::hasShader(ShaderType type) const
{
    return !myShaderSources[static_cast<int>(type)].empty();
}

std::string ShaderParser::getDefineSource() const
{
    std::string source = "";
    for(auto it = myCustomDefines.begin(), end = myCustomDefines.end(); it != end; it++)
    {
        source += "#define " + it->first + " " + it->second + "\n";
    }

    return source;
}

const std::string& ShaderParser::getFullShaderSource() const
{
    return mySource;
}

std::string ShaderParser::getShaderSource(ShaderType type) const
{
    return getDefineSource() + myShaderSources[0] + myShaderSources[static_cast<int>(type)];
}

const ShaderDepthSettings& ShaderParser::getDepthSettings() const
{
    return myDepthSettings;
}

const ShaderBlendSettings& ShaderParser::getBlendSettings() const
{
    return myBlendSettings;
}

const std::string& ShaderParser::getFilePath() const
{
    return myFilePath;
}

std::string ShaderParser::getDirectory() const
{
    std::size_t index = myFilePath.find_last_of('/');
    if(index != std::string::npos)
        return myFilePath.substr(0, index);
    else
        return "";
}

std::string ShaderParser::preProcess(std::string source)
{
    std::for_each(myPreParseCommands.begin(), myPreParseCommands.end(), [this, &source](const PreParseCommand& command) {
        std::size_t startIndex = 0;
        std::size_t endIndex = 0;
        while(startIndex != std::string::npos)
        {
            startIndex = source.find(command.tag, endIndex);
            if(startIndex != std::string::npos)
            {
                std::size_t argumentStartIndex = startIndex + command.tag.size();

                endIndex = source.find('\n', startIndex);
                std::string argument = source.substr(argumentStartIndex, endIndex - argumentStartIndex);
                std::string result = command.parser(argument, *this);
                source.replace(startIndex, endIndex - startIndex, result);
            }
        }
    });
    return source;
}

std::size_t ShaderParser::parseSourceFrom(std::size_t startIndex, std::string& resultingSource)
{
    int scopeCount = 0;
    bool hasStartedScope = false;
    std::size_t endIndex = startIndex;
    while(endIndex != std::string::npos)
    {
        endIndex = mySource.find('\n', startIndex);
        if(endIndex != std::string::npos)
        {
            std::string line = mySource.substr(startIndex, endIndex - startIndex);

            if(line.find('}') != std::string::npos)
            {
                scopeCount--;
            }

            if(hasStartedScope && scopeCount <= 0)
            {
                endIndex++;
                break;
            }
            else if(hasStartedScope)
            {
                if(line.find('t') == 0)
                    line.erase(0);
                if(line.find("    ") == 0)
                    line.erase(0, 4);

                if(line.back() != '\n')
                    resultingSource += line + "\n";
            }

            if(line.find('{') != std::string::npos)
            {
               hasStartedScope = true;
               scopeCount++;
            }
        }
        startIndex = endIndex + 1;
    }

    return endIndex;
}

std::size_t ShaderParser::appendSourceTo(ShaderType type, std::size_t startIndex)
{
    std::string resultingSource;
    std::size_t endIndex = parseSourceFrom(startIndex, resultingSource);
    myShaderSources[static_cast<std::size_t>(type)] = resultingSource;
    return endIndex;
}

std::size_t ShaderParser::parseDepthSettings(std::size_t startIndex)
{
    std::string resultingSource;
    std::size_t endIndex = parseSourceFrom(startIndex, resultingSource);

    resultingSource = stripWhitespace(resultingSource);
    compileSettingParameter(myDepthSettings.enabled, resultingSource, "enabled");
    compileSettingsParameter(myDepthSettings.function, resultingSource, "function");

    return endIndex;
}

std::size_t ShaderParser::parseBlendSettings(std::size_t startIndex)
{
    std::string resultingSource;
    std::size_t endIndex = parseSourceFrom(startIndex, resultingSource);

    resultingSource = stripWhitespace(resultingSource);
    compileSettingParameter(myBlendSettings.enabled, resultingSource, "enabled");
    compileSettingsParameter(myBlendSettings.sourceFactor, resultingSource, "sourceFactor");
    compileSettingsParameter(myBlendSettings.destinationFactor, resultingSource, "destinationFactor");
    compileSettingsParameter(myBlendSettings.function, resultingSource, "function");

    return endIndex;
}

ShaderObject::ShaderObject()
: myType(ShaderType::None)
, myShaderID(0)
{
}

ShaderObject::~ShaderObject()
{
    if(myShaderID > 0)
    {
        glDeleteShader(myShaderID);
    }
}

void ShaderObject::loadFromFile(const std::string& path, ShaderType type)
{
    std::ifstream fileStream(path);
    std::string source((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    loadFromString(source, type);
}

void ShaderObject::loadFromString(const std::string& source, ShaderType type)
{
    myType = type;
    myShaderID = glCreateShader(GetGLShaderType(type));

    const char* sourcePointer = source.c_str();
    glShaderSource(myShaderID, 1, &sourcePointer, NULL);
    glCompileShader(myShaderID);

    GLint status = GL_FALSE;
    glGetShaderiv(myShaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(myShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(myShaderID, infoLogLength, NULL, strInfoLog);

        throw ShaderException(myType, strInfoLog);

        delete[] strInfoLog;
    }
}

GLuint ShaderObject::getGLIdentifier() const
{
    return myShaderID;
}

Shader::Shader()
: myShaderProgram(0)
, myObjects()
, myUniforms()
, myTextures()
, myDepthSettings()
, myBlendSettings()
{
}

Shader::~Shader()
{
    if(myShaderProgram > 0)
    {
        glDeleteProgram(myShaderProgram);
    }
}

void Shader::loadFromFile(const std::string& path)
{
    std::ifstream fileStream(path);
    std::string source((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

    loadFromString(source);
}

void Shader::loadFromString(const std::string& source)
{
    ShaderParser parser;
    parser.parse(source);

    loadFromParser(parser);
}

void Shader::loadFromParser(const ShaderParser& parser)
{
    std::size_t count = static_cast<std::size_t>(ShaderType::Count);
    for(std::size_t index = static_cast<std::size_t>(ShaderType::Vertex); index < count; index++)
    {
        ShaderType type = static_cast<ShaderType>(index);
        if(parser.hasShader(type))
        {
            std::unique_ptr<ShaderObject> object(new ShaderObject());
            object->loadFromString(parser.getShaderSource(type), type);
            myObjects.push_back(std::move(object));
        }
    }

    myShaderProgram = glCreateProgram();

    for(std::size_t index = 0; index < myObjects.size(); index++)
    	glAttachShader(myShaderProgram, myObjects[index]->getGLIdentifier());

    glLinkProgram(myShaderProgram);

    GLint status;
    glGetProgramiv (myShaderProgram, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(myShaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(myShaderProgram, infoLogLength, NULL, strInfoLog);

        throw ShaderException(std::string("Shader linker failure: ") + strInfoLog);

        delete[] strInfoLog;
    }

    for(std::size_t index = 0; index < myObjects.size(); index++)
    	glDetachShader(myShaderProgram, myObjects[index]->getGLIdentifier());

    myDepthSettings = parser.getDepthSettings();
    myBlendSettings = parser.getBlendSettings();
}

void Shader::setParameter(const std::string& name, float value)
{
    bind(false);

    GLint uniformLocation = getUniformLocation(name);
    glUniform1f(uniformLocation, value);
}

void Shader::setParameter(const std::string& name, float value1, float value2)
{
  bind(false);
  
  GLint uniformLocation = getUniformLocation(name);
  glUniform2f(uniformLocation, value1, value2);
}

void Shader::setParameter(const std::string& name, float value1, float value2, float value3)
{
  bind(false);
  
  GLint uniformLocation = getUniformLocation(name);
  glUniform3f(uniformLocation, value1, value2, value3);
}

void Shader::setParameter(const std::string& name, float value1, float value2, float value3, float value4)
{
  bind(false);
  
  GLint uniformLocation = getUniformLocation(name);
  glUniform4f(uniformLocation, value1, value2, value3, value4);
}

void Shader::setParameter(const std::string& name, const sf::Vector2f& value)
{
    bind(false);

    GLint uniformLocation = getUniformLocation(name);
    glUniform2f(uniformLocation, value.x, value.y);
}

void Shader::setParameter(const std::string& name, const sf::Vector3f& value)
{
    bind(false);

    GLint uniformLocation = getUniformLocation(name);
    glUniform3f(uniformLocation, value.x, value.y, value.z);
}

void Shader::setParameter(const std::string& name, const sf::Texture& value)
{
    bind(false);

    GLint uniformLocation = getUniformLocation(name);
    myTextures[ uniformLocation ] = &value;
}

GLint Shader::getUniformLocation(const std::string& name)
{
    auto iterator = myUniforms.find(name);
    if(iterator != myUniforms.end())
    {
        return iterator->second;
    }

    GLint location = glGetUniformLocation(myShaderProgram, name.c_str());
    myUniforms.insert(std::make_pair(name, location));
    return location;
}

void Shader::bind(bool useSettings) const
{
    glUseProgram(myShaderProgram);
    if(useSettings)
    {
        if(myDepthSettings.enabled)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(myDepthSettings.function);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }

        if(myBlendSettings.enabled)
        {
            glEnable(GL_BLEND);
            glBlendFunc(myBlendSettings.sourceFactor, myBlendSettings.destinationFactor);
            glBlendEquation(myBlendSettings.function);
        }
        else
        {
            glDisable(GL_BLEND);
        }

        auto textureIt = myTextures.begin();
        for(std::size_t index = 0, size = myTextures.size(); index < size; index++)
        {
            GLint slot = static_cast<GLsizei>(index + 1);
            glUniform1i(textureIt->first, slot);
            glActiveTexture(GL_TEXTURE0 + slot);
            sf::Texture::bind(textureIt->second);
            textureIt++;
        }
        glActiveTexture(GL_TEXTURE0);
    }
}

void Shader::unbind() const
{
  glUseProgram( 0 );
  sf::Texture::bind(NULL);
  
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);
}
