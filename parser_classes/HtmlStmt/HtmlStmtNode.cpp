#include "HtmlStmtNode.hpp"

HtmlStmtNode* HtmlStmtNode::CreateNode(std::string* html)
{
    HtmlStmtNode* tmp = new HtmlStmtNode();
    tmp->html = html;
    return tmp;
};
