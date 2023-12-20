#include <string>

#include "../Vector_classes/TopStmtList/TopStmtList.hpp"

extern std::string GRAPH_STR;

class HtmlStmtNode;

class StartNode
{
public:
    static int GLOBAL_ID;
    int cur_id;
    HtmlStmtNode *html_before;
    HtmlStmtNode *html_after;
    TopStmtList *top_stmt_list;

    static StartNode *CreateNode(TopStmtList *top_stmt_list);
    static StartNode *CreateNodeFromHtmlBefore(HtmlStmtNode *html_before, TopStmtList *top_stmt_list);
    static StartNode *CreateNodeFromHtmlAfter(TopStmtList *top_stmt_list, HtmlStmtNode *html_after);
    static StartNode *CreateNodeFromHtmlAround(HtmlStmtNode *html_before, TopStmtList *top_stmt_list, HtmlStmtNode *html_after);
    static StartNode *CreateNodeFromHtmlOnly(HtmlStmtNode *html_after);
    std::string * idTag() const;
};