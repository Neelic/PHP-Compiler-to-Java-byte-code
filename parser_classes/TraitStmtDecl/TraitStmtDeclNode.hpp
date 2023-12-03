class TraitStmtDeclNode
{
public:
    std::string* id;
    std::vector<ClassStmtNode*>* stmt_list;

    static TraitStmtDeclNode* Create(std::string* id, std::vector<ClassStmtNode*>* stmt_list);
};