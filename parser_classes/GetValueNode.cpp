class GetValueNode
{
public:
    int count = 1;

    static GetValueNode* Create();
};

GetValueNode *GetValueNode::Create()
{
    return new GetValueNode();
}
