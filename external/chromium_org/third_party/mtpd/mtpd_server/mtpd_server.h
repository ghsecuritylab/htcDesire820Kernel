#ifndef __dbusxx__mtpd_server_mtpd_server_h__ADAPTOR_MARSHALL_H
#define __dbusxx__mtpd_server_mtpd_server_h__ADAPTOR_MARSHALL_H
#include <dbus-c++/dbus.h>
#include <cassert>

namespace org {
namespace chromium {

class Mtpd_adaptor
  : public ::DBus::InterfaceAdaptor
{
public:
    Mtpd_adaptor()
    : ::DBus::InterfaceAdaptor("org.chromium.Mtpd")
    {
        register_method(Mtpd_adaptor, EnumerateStorages, _EnumerateStorages_stub);
        register_method(Mtpd_adaptor, GetStorageInfo, _GetStorageInfo_stub);
        register_method(Mtpd_adaptor, OpenStorage, _OpenStorage_stub);
        register_method(Mtpd_adaptor, CloseStorage, _CloseStorage_stub);
        register_method(Mtpd_adaptor, ReadDirectoryByPath, _ReadDirectoryByPath_stub);
        register_method(Mtpd_adaptor, ReadDirectoryById, _ReadDirectoryById_stub);
        register_method(Mtpd_adaptor, ReadFileChunkByPath, _ReadFileChunkByPath_stub);
        register_method(Mtpd_adaptor, ReadFileChunkById, _ReadFileChunkById_stub);
        register_method(Mtpd_adaptor, GetFileInfoByPath, _GetFileInfoByPath_stub);
        register_method(Mtpd_adaptor, GetFileInfoById, _GetFileInfoById_stub);
        register_method(Mtpd_adaptor, IsAlive, _IsAlive_stub);
    }
    const ::DBus::IntrospectedInterface *introspect() const
    {
        static const ::DBus::IntrospectedArgument EnumerateStorages_args[] =
        {
            { "storageList", "as", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument GetStorageInfo_args[] =
        {
            { "storageName", "s", true },
            { "storageInfo", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument OpenStorage_args[] =
        {
            { "storageName", "s", true },
            { "mode", "s", true },
            { "handle", "s", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument CloseStorage_args[] =
        {
            { "handle", "s", true },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument ReadDirectoryByPath_args[] =
        {
            { "handle", "s", true },
            { "filePath", "s", true },
            { "results", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument ReadDirectoryById_args[] =
        {
            { "handle", "s", true },
            { "fileId", "u", true },
            { "results", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument ReadFileChunkByPath_args[] =
        {
            { "handle", "s", true },
            { "filePath", "s", true },
            { "offset", "u", true },
            { "count", "u", true },
            { "data", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument ReadFileChunkById_args[] =
        {
            { "handle", "s", true },
            { "fileId", "u", true },
            { "offset", "u", true },
            { "count", "u", true },
            { "data", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument GetFileInfoByPath_args[] =
        {
            { "handle", "s", true },
            { "filePath", "s", true },
            { "info", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument GetFileInfoById_args[] =
        {
            { "handle", "s", true },
            { "fileId", "u", true },
            { "info", "ay", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument IsAlive_args[] =
        {
            { "result", "b", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument MTPStorageAttached_args[] =
        {
            { "storageName", "s", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedArgument MTPStorageDetached_args[] =
        {
            { "storageName", "s", false },
            { 0, 0, 0 }
        };
        static const ::DBus::IntrospectedMethod Mtpd_adaptor_methods[] =
        {
            { "EnumerateStorages", EnumerateStorages_args },
            { "GetStorageInfo", GetStorageInfo_args },
            { "OpenStorage", OpenStorage_args },
            { "CloseStorage", CloseStorage_args },
            { "ReadDirectoryByPath", ReadDirectoryByPath_args },
            { "ReadDirectoryById", ReadDirectoryById_args },
            { "ReadFileChunkByPath", ReadFileChunkByPath_args },
            { "ReadFileChunkById", ReadFileChunkById_args },
            { "GetFileInfoByPath", GetFileInfoByPath_args },
            { "GetFileInfoById", GetFileInfoById_args },
            { "IsAlive", IsAlive_args },
            { 0, 0 }
        };
        static const ::DBus::IntrospectedMethod Mtpd_adaptor_signals[] =
        {
            { "MTPStorageAttached", MTPStorageAttached_args },
            { "MTPStorageDetached", MTPStorageDetached_args },
            { 0, 0 }
        };
        static const ::DBus::IntrospectedProperty Mtpd_adaptor_properties[] =
        {
            { 0, 0, 0, 0 }
        };
        static const ::DBus::IntrospectedInterface Mtpd_adaptor_interface =
        {
            "org.chromium.Mtpd",
            Mtpd_adaptor_methods,
            Mtpd_adaptor_signals,
            Mtpd_adaptor_properties
        };
        return &Mtpd_adaptor_interface;
    }
    virtual std::vector< std::string > EnumerateStorages(::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > GetStorageInfo(const std::string& storageName, ::DBus::Error &error) = 0;
    virtual std::string OpenStorage(const std::string& storageName, const std::string& mode, ::DBus::Error &error) = 0;
    virtual void CloseStorage(const std::string& handle, ::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > ReadDirectoryByPath(const std::string& handle, const std::string& filePath, ::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > ReadDirectoryById(const std::string& handle, const uint32_t& fileId, ::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > ReadFileChunkByPath(const std::string& handle, const std::string& filePath, const uint32_t& offset, const uint32_t& count, ::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > ReadFileChunkById(const std::string& handle, const uint32_t& fileId, const uint32_t& offset, const uint32_t& count, ::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > GetFileInfoByPath(const std::string& handle, const std::string& filePath, ::DBus::Error &error) = 0;
    virtual std::vector< uint8_t > GetFileInfoById(const std::string& handle, const uint32_t& fileId, ::DBus::Error &error) = 0;
    virtual bool IsAlive(::DBus::Error &error) = 0;
    
    void MTPStorageAttached(const std::string &storageName)
    {
        ::DBus::SignalMessage __sig("MTPStorageAttached");
        ::DBus::MessageIter __wi = __sig.writer();
        __wi << storageName;
        emit_signal(__sig);
    }
    void MTPStorageDetached(const std::string &storageName)
    {
        ::DBus::SignalMessage __sig("MTPStorageDetached");
        ::DBus::MessageIter __wi = __sig.writer();
        __wi << storageName;
        emit_signal(__sig);
    }
private:
    ::DBus::Message _EnumerateStorages_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        std::vector< std::string > __argout;
        __argout = EnumerateStorages(__error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _GetStorageInfo_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string storageName; __ri >> storageName;
        std::vector< uint8_t > __argout;
        __argout = GetStorageInfo(storageName, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _OpenStorage_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string storageName; __ri >> storageName;
        std::string mode; __ri >> mode;
        std::string __argout;
        __argout = OpenStorage(storageName, mode, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _CloseStorage_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        CloseStorage(handle, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        return __reply;
    }
    ::DBus::Message _ReadDirectoryByPath_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        std::string filePath; __ri >> filePath;
        std::vector< uint8_t > __argout;
        __argout = ReadDirectoryByPath(handle, filePath, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _ReadDirectoryById_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        uint32_t fileId; __ri >> fileId;
        std::vector< uint8_t > __argout;
        __argout = ReadDirectoryById(handle, fileId, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _ReadFileChunkByPath_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        std::string filePath; __ri >> filePath;
        uint32_t offset; __ri >> offset;
        uint32_t count; __ri >> count;
        std::vector< uint8_t > __argout;
        __argout = ReadFileChunkByPath(handle, filePath, offset, count, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _ReadFileChunkById_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        uint32_t fileId; __ri >> fileId;
        uint32_t offset; __ri >> offset;
        uint32_t count; __ri >> count;
        std::vector< uint8_t > __argout;
        __argout = ReadFileChunkById(handle, fileId, offset, count, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _GetFileInfoByPath_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        std::string filePath; __ri >> filePath;
        std::vector< uint8_t > __argout;
        __argout = GetFileInfoByPath(handle, filePath, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _GetFileInfoById_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        ::DBus::MessageIter __ri = __call.reader();
        std::string handle; __ri >> handle;
        uint32_t fileId; __ri >> fileId;
        std::vector< uint8_t > __argout;
        __argout = GetFileInfoById(handle, fileId, __error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
    ::DBus::Message _IsAlive_stub(const ::DBus::CallMessage &__call)
    {
        ::DBus::Error __error;
        bool __argout;
        __argout = IsAlive(__error);
        if (__error.is_set())
            return ::DBus::ErrorMessage(__call, __error.name(), __error.message());
        ::DBus::ReturnMessage __reply(__call);
        ::DBus::MessageIter __wi = __reply.writer();
        __wi << __argout;
        return __reply;
    }
};
}}
#endif  