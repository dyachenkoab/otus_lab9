#include <async.h>

int main()
{
    auto id = packer::connect(3);
    auto id1 = packer::connect(3);
    packer::recieve("one", id);
    packer::recieve("one", id);
    packer::recieve("one", id);

    packer::recieve("two", id1);
    packer::recieve("two", id1);
    packer::recieve("two", id1);
    packer::disconnect(id);
    packer::disconnect(id1);
    return 0;
}
