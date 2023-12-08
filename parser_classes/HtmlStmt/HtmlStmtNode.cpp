class HtmlStmtNode
{
public:
    std::string* html;

    static HtmlStmtNode* CreateNode(std::string* html);
};

HtmlStmtNode* HtmlStmtNode::CreateNode(std::string* html)
{
    HtmlStmtNode* tmp = new HtmlStmtNode();
    tmp->html = html;
    return tmp;
};
