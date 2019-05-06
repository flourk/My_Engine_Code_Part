#include "shader_compiler.h"
#include <iostream>

#include <cstdio>

#include <render/shader.h>

#include <core/log.h>

void ShaderCompiler::Clear()
{
    m_vertexCodeMap.clear();
    m_fragmentCodeMap.clear();
    m_codeblockMap.clear();
}

Shader* ShaderCompiler::Compile(const String& path)
{
    FILE* f = fopen(path.c_str(), "r");

    YY_BUFFER_STATE bp = yy_create_buffer(f, YY_BUF_SIZE);
    yy_switch_to_buffer(bp);

    ParserContext* context = createParserContext();
    yyparse(context);

    Shader* shader = new Shader();

    Parse(context, context->rootNode, shader);

    GenerateShaderCodes(shader);

    deleteParserContext(context);

    Clear();

    return shader;
}

void ShaderCompiler::Parse(ParserContext* ctx, ASTNode* node, Shader* shader)
{
    switch(node->nodeType)
    {
        case NT_VERTEX:
        {
            std::cout << "Parse Vertex:" << std::endl;
            ASTNamedCodeNode* cNode = (ASTNamedCodeNode*) node;
            ParseShaderNode(ctx, cNode, m_vertexCodeMap);
        }
        return;
        case NT_FRAGMENT:
        {
            std::cout << "Parse Fragment:" << std::endl;
            ASTNamedCodeNode* cNode = (ASTNamedCodeNode*) node;
            ParseShaderNode(ctx, cNode, m_fragmentCodeMap);
        }
        return;

        case NT_CODEBLOCK:
        {
            std::cout << "Parse Code Block:" << std::endl;
            ASTNamedCodeNode* cNode = (ASTNamedCodeNode*) node;
            ParseCodeBlockNode(ctx, cNode, m_codeblockMap);
        }
        return;
        case NT_NAMEDCODE:
        {
            ASTNamedCodeNode* pNode = (ASTNamedCodeNode*) node;
            std::cout << "name: " << contextGetString(ctx, pNode->nameIdx) << std::endl;
            std::cout << "code: " << contextGetString(ctx, pNode->codeIdx) << std::endl;
        }
        break;
        case NT_TECHNIQUE:
        {
            Technique* tech = new Technique();
            ParseTechniqueNode(ctx, node, tech);
            shader->AddTechnique(tech);
        }
        return;

        default:
            break;
    }

    for(ASTNode* child = node->firstChild; child; child = child->next)
    {
        Parse(ctx, child, shader);
    }
}

void ShaderCompiler::ParseTechniqueNode(ParserContext* ctx, ASTNode* node, Technique* tech)
{
    for(ASTNode* child = node->firstChild; child; child = child->next)
    {
        if(child->nodeType != NT_PASS)
        {
            logConsole << "(ShaderCompiler)" << "type is not pass type";
            continue;
        }
        
        Pass* pass = new Pass();

        ASTPassNode* passNode = (ASTPassNode*)child;
        ParsePassNode(ctx, passNode, pass);
        tech->AddPass(pass);
    }
}

void ShaderCompiler::ParsePassNode(ParserContext* ctx, ASTPassNode* passNode, Pass* pass)
{
    const char* name = contextGetString(ctx, passNode->nameIdx);
    pass->SetName(name);

    pass->GetVertexShaderCode().name = contextGetString(ctx, passNode->vertexNameIdx);
    pass->GetFragmentShaderCode().name = contextGetString(ctx, passNode->fragmentNameIdx);

    for(ASTNode* child = passNode->firstChild; child; child = child->next)
    {
        ParsePassState(ctx, pass, child);
    }
}

void ShaderCompiler::ParsePassState(ParserContext* ctx, Pass* pass, ASTNode* node)
{
    switch(node->nodeType)
    {
        case NT_CULLMODE:
        {
            ASTCullModeNode* cullModeNode = (ASTCullModeNode*)node;
            RasterState& raster = pass->GetRasterState();
            raster.cullEnable = cullModeNode->enable == 0 ? false : true;
            if(cullModeNode->frontFace == POV_CW)
            {
                raster.cullFrontFace = CULL_CW;
            }
            else
            {
                raster.cullFrontFace = CULL_CCW;
            }

            if(cullModeNode->face == POV_Back)
            {
                raster.cullFace = CULL_BACK;
            }
            else if(cullModeNode->face == POV_Front)
            {
                raster.cullFace = CULL_FRONT;
            }
            else if(cullModeNode->face == POV_Front_And_Back)
            {
                raster.cullFace = CULL_FRONT_AND_BACK;
            }
        }
        break;
    }
}



void ShaderCompiler::ParseShaderNode(ParserContext* ctx, ASTNamedCodeNode* node, std::map<String, ParseShaderCode>& codeMap)
{
    const char* name = contextGetString(ctx, node->nameIdx);
    const char* code = contextGetString(ctx, node->codeIdx);

    auto it = codeMap.find(name);
    if(it != codeMap.end())
    {
        logConsole << "(ShaderCompiler)" << "have same code name : " << name;
    }

    ParseShaderCode parseShaderCode;
    parseShaderCode.code = code;

    if(node->firstChild != NULL)
    {
        if(node->firstChild->nodeType != NT_REQUIRE)
        {
            logConsole << "(ShaderCompiler)" << "Shader Node can only hava require node : ";
        }

        ASTRequireNode * requireNode = (ASTRequireNode*)node->firstChild;
        for(int i = 0; i < requireNode->count; i++)
        {
            const char* requireName = contextGetString(ctx, requireNode->requireNameIdxes[i]);
            parseShaderCode.requireNames.insert(requireName);
        }
    }

    codeMap.insert(std::make_pair(name, parseShaderCode));
}

void ShaderCompiler::ParseCodeBlockNode(ParserContext* ctx, ASTNamedCodeNode* node,  std::map<String, const char*>& codeMap)
{
    const char* name = contextGetString(ctx, node->nameIdx);
    const char* code = contextGetString(ctx, node->codeIdx);

    auto it = codeMap.find(name);
    if(it != codeMap.end())
    {
        logConsole << "(ShaderCompiler)" << "have same code name : " << name;
    }

    codeMap.insert(std::make_pair(name, code));
}


void ShaderCompiler::GenerateShaderCodes(Shader* shader)
{
    int techCount = shader->GetTechniqueCount();

    for(int i = 0; i < techCount; i++)
    {
        Technique* tech = shader->GetTechnique(i);

        int passCount = tech->GetPassCount();
        for(int j = 0; j < passCount; j++)
        {
            Pass* pass = tech->GetPass(j);

            ShaderCode& vertex = pass->GetVertexShaderCode();
            GenerateShaderCode(pass, m_vertexCodeMap, m_codeblockMap, vertex);

            ShaderCode& fragment = pass->GetFragmentShaderCode();
            GenerateShaderCode(pass, m_fragmentCodeMap, m_codeblockMap, fragment);
        }
        tech->Compile();
    }
}

void ShaderCompiler::GenerateShaderCode(const Pass* pass, const std::map<String, ParseShaderCode>& codeMap, 
    std::map<String, const char*> blockMap,  ShaderCode& shaderCode)
{
    auto codeIt = codeMap.find(shaderCode.name);
    if(codeIt == codeMap.end())
    {
        logConsole << "(ShaderCompiler)" << "Pass : " << pass->GetName() << " can't find vertex code : " << shaderCode.name;
        return;
    }

    shaderCode.code.append("#version 330 core");

    const ParseShaderCode& parseShaderCode = codeIt->second;

    if(parseShaderCode.requireNames.size() > 0)
    {
        for(auto it = parseShaderCode.requireNames.begin(); it != parseShaderCode.requireNames.end(); it++)
        {
            auto findIt = blockMap.find(*it);
            if(findIt != blockMap.end())
            {
                shaderCode.code.append(findIt->second);
            }
        }
    }

    shaderCode.code.append(parseShaderCode.code);
}
