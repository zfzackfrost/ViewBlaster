/**
 * @file Buffer.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief `AbstractBuffer` class declaration.
 */

#pragma once

#include <cstdint>

#include <viewblaster/common/utils/Result.hpp>

namespace viewblaster {
    class AbstractBuffer
    {
    public:
        /**
         * @brief Constructor
         */
        AbstractBuffer(uint64_t Size)
        {
        }

        /**
         * @brief Fill a buffer with the provided data
         */
        virtual utils::Result<utils::Void> Fill(const void* Data, uint64_t DataSize) = 0;
        
        /**
         * @brief Get the size of the buffer in bytes.
         */
        virtual utils::Result<uint64_t> GetSize() = 0;
    };
} // namespace viewblaster
