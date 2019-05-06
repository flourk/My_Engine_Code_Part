#include "ast.h"
#include <memory.h>
#include <string.h>

static void deleteNode(ASTNode* node)
{
    if(node->firstChild != NULL)
    {
        deleteNode(node->firstChild);
    }

    if(node->next != NULL)
    {
        deleteNode(node->next);
    }

    free(node);
    node = NULL;
}

static void GrowIfNeed(ParserContext* context, int size)
{
    if((context->tableSize - context->writePos) < (size + 1))
    {
        int newSize = 2 * context->tableSize;
        char* newStringTable = (char*)malloc(newSize);
        memcpy(newStringTable, context->stringTable, context->tableSize);
        free(context->stringTable);
        context->stringTable = newStringTable;
        context->tableSize = newSize;
    }
}


ParserContext* createParserContext()
{
    ParserContext* ctx = (ParserContext*)malloc(sizeof(ParserContext));
    ctx->rootNode = createNode(NT_ROOT);
    ctx->bracketDepth = 0;
    ctx->tableSize = 1024;
    ctx->writePos = 0;
    ctx->stringTable = (char*)malloc(ctx->tableSize);
    ctx->stackHead = NULL;

    return ctx;
}

void deleteParserContext(ParserContext* ptr)
{
    if(ptr == NULL)
        return;

    free(ptr->stringTable);
    deleteNode(ptr->rootNode);

    //TODO stack

    free(ptr);
}

ASTNode* createNode(NodeType nodeType)
{
    ASTNode* retNode = NULL;
    switch(nodeType)
    {
        case NT_ROOT:
        case NT_TECHNIQUE:
        {
            ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
            retNode = (ASTNode*)node;
        }
        break;
        case NT_VERTEX:
        case NT_FRAGMENT:
        case NT_CODEBLOCK:
        {
            ASTNamedCodeNode* node = (ASTNamedCodeNode*)malloc(sizeof(ASTNamedCodeNode));
            node->nameIdx = -1;
            node->codeIdx = -1;
            retNode = (ASTNode*)node;
        }
        break;
        case NT_PASS:
        {
            ASTPassNode* node = (ASTPassNode*)malloc(sizeof(ASTPassNode));
            retNode = (ASTNode*)node;
        }
        break;
        case NT_REQUIRE:
        {
            ASTRequireNode* node = (ASTRequireNode*)malloc(sizeof(ASTRequireNode));
            node->count = 0;
            retNode = (ASTNode*)node;
        }
        break;
        case NT_CULLMODE:
        {
            ASTCullModeNode* node = (ASTCullModeNode*)malloc(sizeof(ASTCullModeNode));
            node->enable = 0;
            node->frontFace = POV_CCW;
            node->face = POV_Back;

            retNode = (ASTNode*)node;
        }
        default:
        break;
    }

    retNode->nodeType = nodeType;
    retNode->firstChild = NULL;
    retNode->lastChild = NULL;
    retNode->next = NULL;

    return retNode;
}

void nodeAddChild(ASTNode* node, ASTNode* child)
{
    if(node->lastChild)
    {
        node->lastChild->next = child;
        node->lastChild = child;
    }
    else
    {
        node->lastChild = child;
        node->firstChild = child;
    }
}

int contextAddString(ParserContext* context, const char* value)
{
    int len = strlen(value);
    GrowIfNeed(context, len + 1);
    int pos = context->writePos;
    memcpy(context->stringTable + context->writePos, value, len + 1);
    context->writePos += len + 1;
    return pos;
}

char* contextGetString(ParserContext* context, int idx)
{
    if(idx >= context->tableSize && idx < 0)
        return NULL;

    return context->stringTable + idx;
}

void pushNode(ParserContext* context, ASTNode* node)
{
    StackElem* elem = (StackElem*)malloc(sizeof(StackElem));
    elem->value = node;
    elem->next = context->stackHead;
    context->stackHead = elem;
    context->topNode = context->stackHead->value;
}

void popNode(ParserContext* context)
{
    if(!context->stackHead)
        return;

    StackElem* elem = context->stackHead;
    context->stackHead = elem->next;
    if(context->stackHead)
    {
        context->topNode = context->stackHead->value;
    }
    free(elem);
}