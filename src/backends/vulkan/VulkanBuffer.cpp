#include <viewblaster/backends/vulkan/VulkanBuffer.hpp>

#include <fmt/core.h>

namespace viewblaster {
    VulkanBuffer::VulkanBuffer(uint64_t Size)
        : AbstractBuffer(Size)
    {
        mSize = Size;
    }

    utils::Result<utils::Void> VulkanBuffer::Fill(const void* Data, uint64_t DataSize)
    {
        auto Size = GetSize().Value();
        if (Size == 0)
        {
            return {"VulkanBuffer::Fill : Buffer size is 0", utils::E_MessageLevel::Error};
        }
        if (DataSize > Size)
        {
            return {fmt::format(
                        "VulkanBuffer::Fill : Data size ({0} bytes) is larger than buffer size ({1} bytes)",
                        DataSize,
                        Size),
                    utils::E_MessageLevel::Error};
        }
        return {utils::Void {}};
    }

    utils::Result<uint64_t> VulkanBuffer::GetSize() { return {mSize}; }
} // namespace viewblaster
