template<class CmdT, unsigned int CONSUMPTION>
class FixedConsumption : public CmdT
{
public:
    template<typename... Args>
    FixedConsumption(Args&&... args)
        : CmdT(std::forward<Args>(args)...)
    {}

    unsigned int getEnergyConsumption() const override
    {
        return CONSUMPTION;
    }
};