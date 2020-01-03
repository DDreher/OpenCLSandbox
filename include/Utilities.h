#pragma once
#include <utility>
#include <string>

namespace mpp
{
    enum ReturnCode;
}

class Utility
{
public:
    static std::pair<mpp::ReturnCode, std::string> ReadFile(const std::string& file_name);
    static uint32_t GetNextMultipleOf(uint32_t num_to_round, uint32_t num_multiple);
};
