#include <string>

class HtmlStmtNode
{
public:
    std::string* html;
    int cur_id;
    static int GLOBAL_ID;

    static HtmlStmtNode* CreateNode(std::string* html);

    std::string IdTag();
};