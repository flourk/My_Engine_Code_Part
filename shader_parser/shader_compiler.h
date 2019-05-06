#pragma once

#include <vector>
#include <map>
#include <set>
#include <core/string_ex.h>
#include <render/pass.h>


extern "C"
{
    #define YY_NO_UNISTD_H 1
    #include "parser.h"
    #include "lexer.h"
}


struct ParseShaderCode {
    const char* code;
    std::set<const char*> requireNames;
};

class Shader;
class Technique;
class Pass;

class ShaderCompiler {
public:
    Shader* Compile(const String& path);

private:
    void Parse(ParserContext* ctx, ASTNode* node, Shader* shader);
    void ParseTechniqueNode(ParserContext* ctx, ASTNode* node, Technique* tech);
    void ParsePassNode(ParserContext* ctx, ASTPassNode* passNode, Pass* pass);
    void ParsePassState(ParserContext* ctx, Pass* pass, ASTNode* node);

    void ParseShaderNode(ParserContext* ctx, ASTNamedCodeNode* node,  std::map<String, ParseShaderCode>& codeMap);
    void ParseCodeBlockNode(ParserContext* ctx, ASTNamedCodeNode* node,  std::map<String, const char*>& codeMap);


    void GenerateShaderCodes(Shader* shader);
    void GenerateShaderCode(const Pass* pass, const std::map<String, ParseShaderCode>& codeMap, 
        std::map<String, const char*> blockMap, ShaderCode& shaderCode);

    void Clear();

private:

    std::map<String, ParseShaderCode> m_vertexCodeMap;
    std::map<String, ParseShaderCode> m_fragmentCodeMap;
    std::map<String, const char*> m_codeblockMap;
};