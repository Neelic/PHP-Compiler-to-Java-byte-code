class HtmlStmtNode
{
public:
    std::string* html;

    static HtmlStmtNode* Create(std::string* html);
};

HtmlStmtNode* HtmlStmtNode::Create(std::string* html)
{
    HtmlStmtNode* tmp = new HtmlStmtNode();
    tmp->html = html;
    return tmp;
};
