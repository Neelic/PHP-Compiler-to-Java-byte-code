#include "HtmlStmtNode.hpp"

int HtmlStmtNode::GLOBAL_ID = 0;

std::string *HtmlStmtNode::idTag() const {
    auto* tmp = new std::string(std::string("HtmlStmt") + std::to_string(this->cur_id));
    return tmp;
}

HtmlStmtNode* HtmlStmtNode::CreateNode(std::string* html)
{
    HtmlStmtNode* tmp = new HtmlStmtNode();
    tmp->html = html;
    tmp->cur_id = HtmlStmtNode::GLOBAL_ID++;
    return tmp;
};
