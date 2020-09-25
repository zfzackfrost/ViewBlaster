/**
 * @file Result.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief Result value types and helpers.
 */

#pragma once

#include <viewblaster/config.hpp>

#include <string>
#include <tuple>
#include <optional>

#include <fmt/color.h>
#include <fmt/core.h>

namespace viewblaster::utils {
    enum class E_MessageLevel
    {
        Debug,
        Info,
        Warning,
        Error,
    };
    using MessageT = std::tuple<std::string, E_MessageLevel>;

    struct Void final
    { };

    template <typename T>
    struct Result
    {
        Result(const T Val)
            : mValue(Val)
        { }
        Result(const MessageT Msg)
            : mMsg(Msg)
        { }
        Result(const std::string MsgText, const E_MessageLevel MsgLevel)
            : mMsg(MessageT {MsgText, MsgLevel})
        { }
        Result(const T Val, const MessageT Msg)
            : mValue(Val), mMsg(Msg)
        { }
        Result(const T Val, const std::string MsgText, const E_MessageLevel MsgLevel)
            : mValue(Val), mMsg(MessageT {MsgText, MsgLevel})
        { }
        [[nodiscard]] T Value() const { return *mValue; }
        [[nodiscard]] MessageT Message() const { return *mMsg; }
        [[nodiscard]] bool HasValue() const { return mValue.has_value(); }
        [[nodiscard]] bool HasMessage() const { return mMsg.has_value(); }

    private:
        std::optional<MessageT> mMsg;
        std::optional<T> mValue;
    };

    inline void PrintMessage(MessageT Msg)
    {
        auto Txt = std::get<0>(Msg);
        auto Lvl = std::get<1>(Msg);

        std::string Prefix = "";
        switch (Lvl)
        {
        case E_MessageLevel::Debug:
            Prefix = "DEB";
            break;
        case E_MessageLevel::Info:
            Prefix = "INF";
            break;
        case E_MessageLevel::Warning:
            Prefix = "WRN";
            break;
        case E_MessageLevel::Error:
            Prefix = "ERR";
            break;
        }

        fmt::print(
#ifdef VIEW_BLASTER_COLORED_OUTPUT
            fmt::fg(Lvl == utils::E_MessageLevel::Error
                        ? fmt::terminal_color::red
                        : Lvl == utils::E_MessageLevel::Warning ? fmt::terminal_color::yellow
                                                                : fmt::terminal_color::green),
#endif
            "[{0}] -- {1}",
            Prefix,
            Txt);
    }
} // namespace viewblaster::utils
