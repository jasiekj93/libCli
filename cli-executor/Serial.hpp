#pragma once

/**
 * @file Serial.hpp
 * @author Adrian Szczepanski
 * @date 10-06-2025
 */

#include <string>

#include <etl/string.h>
#include <etl/span.h>

#include <libcli/IOStream.hpp>

class Serial : public cli::OutputStream
{
public:
    Serial(std::string_view path);
    ~Serial();

    void write(etl::string_view) override;
    void write(char) override;

    etl::span<const uint8_t> read();

private:
    static constexpr size_t BUFFER_SIZE = 0x20000;

    int handle;
    etl::array<uint8_t, BUFFER_SIZE> buffer;
};