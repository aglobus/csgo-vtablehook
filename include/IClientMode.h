class IClientMode
{
public:
    virtual             ~IClientMode() {}
    virtual bool        CreateMove(float flInputSampleTime, void* usercmd) = 0; // 21
};
