#pragma once

/**
 * @file IOStream.hpp
 * @author Adrian Szczepanski
 * @date 11-06-2025
 */

#include <etl/string.h>

#include <libcli/FormatSpecification.hpp>

namespace cli
{
    class OutputStream
    {
    public:
        virtual ~OutputStream() = default;

        OutputStream& operator<<(char);
        OutputStream& operator<<(etl::string_view);
        OutputStream& operator<<(const formatspec::Base&);

        virtual void write(char c) = 0;
        virtual void write(etl::string_view) = 0;
        virtual void flush() {}

    };

    class InputStream
    {
    public:
        InputStream(); 

        InputStream& operator>>(char&);
        InputStream& operator>>(etl::istring&);

        bool seekg(size_t pos);
        inline size_t tellg() { return position; }

        bool read(char& c);
        bool read(etl::istring& str, size_t count);
        bool read(char*, size_t limit);

        size_t available() const { return size() - position; }

        virtual size_t size() const = 0;
        virtual void sync() {}

    protected:
        virtual bool readFrom(char& c, size_t position) = 0;
        virtual bool readFrom(etl::istring& str, size_t count, size_t position) = 0;
        virtual bool readFrom(char* buffer, size_t count, size_t position) = 0;

    private:
        size_t position = 0; 
    };

    class IOStream : public OutputStream, public InputStream
    {
    public:
        virtual ~IOStream() = default;
    };
}