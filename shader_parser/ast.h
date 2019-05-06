#pragma once

#define MAX_REQUIRE 32

typedef enum tagPassOptionValue {
    POV_CW = 0,
    POV_CCW,
    POV_Front,
    POV_Back,
    POV_Front_And_Back

} PassOptionValue;

typedef enum tagNodeType
{
    NT_ROOT,
    NT_VERTEX,
    NT_FRAGMENT,
    NT_CODEBLOCK,
    NT_NAMEDCODE,
    NT_TECHNIQUE,
    NT_PASS,
    NT_REQUIRE,
    NT_CULLMODE,
} NodeType;

#define AST_NODE_COMMON_DATA \
    NodeType nodeType; \
    struct stASTNode* firstChild; \
    struct stASTNode* lastChild; \
    struct stASTNode* next;



typedef struct stASTNode {
    AST_NODE_COMMON_DATA
} ASTNode;

typedef struct stNamedCodeNode {
    AST_NODE_COMMON_DATA
    int nameIdx;
    int codeIdx;
} ASTNamedCodeNode;

typedef struct stPassNode {
    AST_NODE_COMMON_DATA
    int nameIdx;
    int vertexNameIdx;
    int fragmentNameIdx;

} ASTPassNode;

typedef struct stRequireNode {
    AST_NODE_COMMON_DATA
    int count;
    int requireNameIdxes[MAX_REQUIRE];
} ASTRequireNode;

typedef struct stCullModeNode {
    AST_NODE_COMMON_DATA
    int enable;
    PassOptionValue frontFace;
    PassOptionValue face;
} ASTCullModeNode;

typedef struct stStackElem {
    ASTNode* value;
    struct stStackElem* next;
} StackElem;

typedef struct stParseContext
{
    ASTNode* rootNode;

    ASTNode* topNode;
    StackElem* stackHead;

    int bracketDepth;
    char* stringTable;
    int writePos;
    int tableSize;

} ParserContext;



ParserContext* createParserContext();
void deleteParserContext(ParserContext* ptr);

ASTNode* createNode(NodeType nodeType);

void nodeAddChild(ASTNode* node, ASTNode* child);

int contextAddString(ParserContext* context, const char* value);

char* contextGetString(ParserContext* context, int idx);

void pushNode(ParserContext* context, ASTNode* node);

void popNode(ParserContext* context);