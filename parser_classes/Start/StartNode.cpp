#include "StartNode.hpp"

int StartNode::GLOBAL_ID = 0;

StartNode *StartNode::CreateNode(TopStmtList *top_stmt_list) {
    auto *tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    tmp->cur_id = StartNode::GLOBAL_ID++;
    return tmp;
}

static StartNode *CreateNodeFromHtmlBefore(HtmlStmtNode *html_before, TopStmtList *top_stmt_list)
{
    auto *tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    tmp->html_before = html_before;
    tmp->cur_id = StartNode::GLOBAL_ID++;
    return tmp;
}

static StartNode *CreateNodeFromHtmlAfter(TopStmtList *top_stmt_list, HtmlStmtNode *html_after)
{
    auto *tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    tmp->html_after = html_after;
    tmp->cur_id = StartNode::GLOBAL_ID++;
    return tmp;
}
static StartNode *CreateNodeFromHtmlAround(HtmlStmtNode *html_before, TopStmtList *top_stmt_list, HtmlStmtNode *html_after)
{
    auto *tmp = new StartNode();
    tmp->top_stmt_list = top_stmt_list;
    tmp->html_before = html_before;
    tmp->html_after = html_after;
    tmp->cur_id = StartNode::GLOBAL_ID++;
    return tmp; 
}

static StartNode *CreateNodeFromHtmlOnly(HtmlStmtNode *html_after)
{
    auto *tmp = new StartNode();
    tmp->html_after = html_after;
    tmp->cur_id = StartNode::GLOBAL_ID++;
    return tmp; 
}

std::string * StartNode::idTag() const {
    auto *tmp = new std::string(std::string("Start") + std::to_string(this->cur_id));
    return tmp;
}
