#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Base/Definitions.h"
#include "Base/OpenCLManager.h"
#include "Base/Utilities.h"
#include "HashTable/HashTable.h"

#include <stdio.h>
#include <iostream>

TEST_CASE("HashTable", "[gpu]")
{
    OpenCLManager* mgr = OpenCLManager::GetInstance();
    mgr->LoadKernel(mpp::filenames::KERNELS_HASHTABLE, { mpp::kernels::HASHTABLE_INSERT, mpp::kernels::HASHTABLE_RETRIEVE});

    SECTION("Try to retrieve element from empty table")
    {
        std::vector<uint32_t> keys = { 42 };

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()));
        REQUIRE(success == true);

        std::vector<uint32_t> retrieved_vals = hash_table.Get(keys);
        REQUIRE(retrieved_vals.size() == keys.size());
        REQUIRE(retrieved_vals[0] == static_cast<uint32_t>(mpp::constants::EMPTY));
    }

    SECTION("Try to retrieve multiple elements from empty table")
    {
        std::vector<uint32_t> keys = { 1, 2, 3, 10, 11, 42 };

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()));
        REQUIRE(success == true);

        std::vector<uint32_t> retrieved_vals = hash_table.Get(keys);
        REQUIRE(retrieved_vals.size() == keys.size());
        for(auto val : retrieved_vals)
        {
            REQUIRE(val == mpp::constants::EMPTY_32);
        }
    }

    SECTION("Insert one element")
    {
        std::vector<uint32_t> keys = { 1 };
        std::vector<uint32_t> values = { 123 };

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);
    }

    SECTION("Retrieve one element")
    {
        std::vector<uint32_t> keys = { 42 };
        std::vector<uint32_t> values = { 123 };
        
        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);

        std::vector<uint32_t> retrieved_vals = hash_table.Get(keys);
        REQUIRE(retrieved_vals.size() == keys.size());
        REQUIRE(retrieved_vals == values);
    }

    SECTION("Retrieve multiple elements")
    {
        std::vector<uint32_t> keys = { 1, 2, 3, 10, 11, 42 };
        std::vector<uint32_t> values = { 123, 1, 8, 9, 20, 40 };
        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);

        std::vector<uint32_t> retrieved_vals = hash_table.Get(keys);
        REQUIRE(retrieved_vals.size() == keys.size());
        REQUIRE(retrieved_vals == values);
    }

    SECTION("Insert thousand elements")
    {
        uint32_t num_elements = 1000;
        std::vector<uint32_t> keys;
        std::vector<uint32_t> values;

        for(uint32_t i=0; i<num_elements; ++i)
        {
            keys.push_back(i);
            values.push_back(i+3);
        }

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);
    }

    SECTION("Retrieve thousand elements")
    {
        uint32_t num_elements = 1000;
        std::vector<uint32_t> keys;
        std::vector<uint32_t> values;

        for (uint32_t i = 0; i < num_elements; ++i)
        {
            keys.push_back(i);
            values.push_back(i + 3);
        }

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);

        std::vector<uint32_t> retrieved_vals = hash_table.Get(keys);
        REQUIRE(retrieved_vals.size() == keys.size());
        REQUIRE(retrieved_vals == values);
    }

    SECTION("Insert a million elements")
    {
        uint32_t num_elements = 1'000'000;
        std::vector<uint32_t> keys;
        std::vector<uint32_t> values;

        for (uint32_t i = 0; i < num_elements; ++i)
        {
            keys.push_back(i);
            values.push_back(i + 3);
        }

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);
    }

    SECTION("Retrieve a million elements")
    {
        uint32_t num_elements = 1'000'000;
        std::vector<uint32_t> keys;
        std::vector<uint32_t> values;

        for (uint32_t i = 0; i < num_elements; ++i)
        {
            keys.push_back(i);
            values.push_back(i + 3);
        }

        HashTable hash_table;
        bool success = hash_table.Init(static_cast<uint32_t>(keys.size()), keys, values);
        REQUIRE(success == true);

        std::vector<uint32_t> retrieved_vals = hash_table.Get(keys);
        REQUIRE(retrieved_vals.size() == keys.size());
        REQUIRE(retrieved_vals == values);
    }
}
