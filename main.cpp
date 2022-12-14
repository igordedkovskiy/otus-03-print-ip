// homework #3: print ip.

#include <vector>
#include <list>
#include <string>
#include "print_ip.h"

using namespace print_ip_ns;

int main()
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));

    std::string s{"3.6.9.0.2"};
    print_ip(s);

    std::vector<ip_field_t> v{1,2,3,4,5,6};
    print_ip(v);

    std::list<ip_field_t> l{2,4,6,7,9};
    print_ip(l);

    return 0;
}
