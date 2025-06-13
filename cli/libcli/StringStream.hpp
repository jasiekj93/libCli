#pragma once

#include <libcli/IOStream.hpp>
#include <libcli/Configuration.hpp>

namespace cli
{
    class StringStream : public IOStream
    {
    public:
        StringStream() = default;

        void write(char c) override;
        void write(etl::string_view str) override;
        void flush() override { clear(); }

        size_t size() const override;

        void clear();

    protected:
        bool readFrom(char& c, size_t position) override;
        bool readFrom(etl::istring&, size_t count, size_t position) override;
        bool readFrom(char*, size_t count, size_t position) override;

    private:
        etl::string<Configuration::IO_STREAM_SIZE> buffer;
    };
}