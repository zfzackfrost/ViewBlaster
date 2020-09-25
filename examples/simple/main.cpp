#include <viewblaster/viewblaster.hpp>

using namespace viewblaster;

class SimpleApp : public App
{
public:
    utils::Result<utils::Void> Initialize() override
    {
        auto R = App::Initialize();
        if (R.HasMessage())
            return R;
        SetAppTitle("Simple App");
        return {utils::Void{}};
    }
};

int main(int argc, char* argv[])
{
    SimpleApp{}.Run();
    return 0;
}
