#include <string>

class HtmlStmtNode
{
public:
    std::string* html;

    static HtmlStmtNode* CreateNode(std::string* html);
};