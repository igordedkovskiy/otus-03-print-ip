#include <vector>
#include "gtest/gtest.h"
#include "print_ip.h"

TEST(TEST_PRINT_IP_METHOD, process_integers)
{
    using print_ip_ns::print_ip_helpers::process;
    {
        const char c = -1;
        std::vector<short> vec;
        for(const auto it:process(c))
            vec.emplace_back(it);
        ASSERT_TRUE(vec[0] == 255);
    }
    {
        const short c = 0;
        std::vector<short> vec;
        for(const auto it:process(c))
            vec.emplace_back(it);
        ASSERT_TRUE(vec[0] == 0);
        ASSERT_TRUE(vec[1] == 0);
    }
    {
        const int c = 2130706433;
        std::vector<short> vec;
        for(const auto it:process(c))
            vec.emplace_back(it);
        ASSERT_TRUE(vec[0] == 0x7F);
        ASSERT_TRUE(vec[1] == 0x00);
        ASSERT_TRUE(vec[2] == 0x00);
        ASSERT_TRUE(vec[3] == 0x01);
    }
    {
        const auto c = static_cast<long>(8875824491850138409);
        std::vector<short> vec;
        for(const auto it:process(c))
            vec.emplace_back(it);
        // ‭7B2D4359 65708329‬
        if(sizeof(long) == 4)
        {
            ASSERT_TRUE(vec[0] == 0x65);
            ASSERT_TRUE(vec[1] == 0x70);
            ASSERT_TRUE(vec[2] == 0x83);
            ASSERT_TRUE(vec[3] == 0x29);
        }
        else if(sizeof(long) > 4)
        {
            ASSERT_TRUE(vec[0] == 0x7B);
            ASSERT_TRUE(vec[1] == 0x2D);
            ASSERT_TRUE(vec[2] == 0x43);
            ASSERT_TRUE(vec[3] == 0x59);
            ASSERT_TRUE(vec[4] == 0x65);
            ASSERT_TRUE(vec[5] == 0x70);
            ASSERT_TRUE(vec[6] == 0x83);
            ASSERT_TRUE(vec[7] == 0x29);
        }
    }
}

TEST(TEST_PRINT_IP_METHOD, process_containers)
{
    using print_ip_ns::print_ip_helpers::process;
    std::vector<print_ip_ns::ip_field_t> ints {0,1,2,3,4,5,6,7,255};
    std::vector<print_ip_ns::ip_field_t> vec;
    for(const auto it:process(ints))
        vec.emplace_back(it);
    ASSERT_TRUE(vec == ints);
    {
        std::vector<int> vec;
        for(const auto it:process(ints))
            vec.emplace_back(it);
        ASSERT_TRUE(vec.size() == ints.size());
        for(std::size_t cntr{0}; cntr < vec.size(); ++cntr)
            ASSERT_TRUE(vec[cntr] == ints[cntr]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
