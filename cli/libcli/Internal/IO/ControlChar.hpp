#pragma once

/**
 * @file ControlChar.hpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

namespace cli::Internal::IO::ControlChar
{
    static constexpr char NEW_LINE = '\r';    
    static constexpr char ESCAPE_CHAR = '\e';    
    static constexpr char BACKSPACE = 0x7F;    
    static constexpr char TAB = '\t';    
}