#include <viewblaster/viewblaster.hpp>

using namespace viewblaster;

class SimpleApp : public App
{
public:
    utils::Result<utils::Void> EarlyInitialize() override
    {
        auto R = App::EarlyInitialize();
        if (R.HasMessage())
            return R;
        utils::AssertResult(SetAppTitle("Simple App"));
        return {utils::Void{}};
    }
};

int main(int argc, char* argv[])
{
    SimpleApp{}.Run();
    return 0;
}
