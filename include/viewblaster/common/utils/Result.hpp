/**
 * @file Result.hpp
 * @author Zachary Frost
 * @copyright See repository LICENSE file
 * @brief Result value types and helpers.
 */

#pragma once

#include <viewblaster/config.hpp>

#include <optional>
#include <string>
#include <tuple>

#include <fmt/color.h>
#include <fmt/core.h>

#define VIEW_BLASTER_RETURN_IF_ERR(Res)                                                                      \
                                                                                                             \
    {                                                                                                        \
        auto R = Res;                                                                                        \
        if (R.HasMessage() && R.MessageLvl() == ::viewblaster::utils::E_MessageLevel::Error)                 \
            return {R.Message()};                                                                            \
        else if (R.HasMessage())                                                                             \
            ::viewblaster::utils::PrintMessage(R.Message());                                                 \
    }

namespace viewblaster::utils {
    enum class E_MessageLevel
    {
        Debug,
        Success,
        Warning,
        Error,
    };
    using MessageT = std::tuple<std::string, E_MessageLevel>;

    struct Void final
    { };

    template <typename T>
    struct [[nodiscard]] Result
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
            : mValue(Val)
            , mMsg(Msg)
        { }
        Result(const T Val, const std::string MsgText, const E_MessageLevel MsgLevel)
            : mValue(Val)
            , mMsg(MessageT {MsgText, MsgLevel})
        { }
        [[nodiscard]] T Value() const { return *mValue; }
        [[nodiscard]] MessageT Message() const { return *mMsg; }
        [[nodiscard]] auto MessageTxt() const { return std::get<0>(Message()); }
        [[nodiscard]] auto MessageLvl() const { return std::get<1>(Message()); }
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
        case E_MessageLevel::Success:
            Prefix = "SCS";
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
            fmt::fg(Lvl == E_MessageLevel::Error
                        ? fmt::terminal_color::red
                        : Lvl == E_MessageLevel::Warning
                              ? fmt::terminal_color::yellow
                              : Lvl == E_MessageLevel::Success ? fmt::terminal_color::green
                                                               : fmt::terminal_color::bright_black),
#endif
            "-- [{0}]: {1}\n",
            Prefix,
            Txt);
    }

    template <typename T>
    void AssertResult(const Result<T>& R)
    {
        if (R.HasMessage())
        {
            auto Msg = R.Message();
            PrintMessage(R.Message());
            auto Level = std::get<1>(Msg);
            if (Level == E_MessageLevel::Error)
            {
                std::exit(EXIT_FAILURE);
            }
        }
    }
} // namespace viewblaster::utils
