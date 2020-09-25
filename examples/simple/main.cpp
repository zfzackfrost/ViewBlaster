#include <viewblaster/viewblaster.hpp>

using namespace viewblaster;

int main(int argc, char* argv[])
{
    auto* Buf    = new Buffer(64);
    auto FillRes = Buf->Fill(nullptr, 128);
    if (FillRes.HasMessage())
    {
        utils::PrintMessage(FillRes.Message());
    }
    delete Buf;
    return 0;
}
