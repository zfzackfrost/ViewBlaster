/**
 * @file VulkanBuffer.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief `VulkanBuffer` class
 */

#pragma once

#include <viewblaster/common/render/Buffer.hpp>

namespace viewblaster {
    class VulkanBuffer : public AbstractBuffer
    {
    public:
        /**
         * @brief Constructor
         */
        VulkanBuffer(uint64_t Size);

        /**
         * @brief Fill a buffer with the provided data
         */
        utils::Result<utils::Void> Fill(const void* Data, uint64_t DataSize) override;
        
        /**
         * @brief Get the size of the buffer in bytes.
         */
        utils::Result<uint64_t> GetSize() override;

    private:
        uint64_t mSize;
    };

    using Buffer = VulkanBuffer;
} // namespace viewblaster
