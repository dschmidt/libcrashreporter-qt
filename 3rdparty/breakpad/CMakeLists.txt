if(UNIX)
    list(APPEND breakpadSources
        google-breakpad/src/client/minidump_file_writer.cc
        google-breakpad/src/common/convert_UTF.cc
        google-breakpad/src/common/string_conversion.cc
    )

    if(APPLE)
        list(APPEND breakpadSources
            google-breakpad/src/client/mac/crash_generation/crash_generation_client.cc
            google-breakpad/src/client/mac/crash_generation/crash_generation_server.cc
            google-breakpad/src/client/mac/handler/breakpad_nlist_64.cc
            google-breakpad/src/client/mac/handler/dynamic_images.cc
            google-breakpad/src/client/mac/handler/exception_handler.cc
            google-breakpad/src/client/mac/handler/minidump_generator.cc
            google-breakpad/src/client/mac/handler/protected_memory_allocator.cc
            google-breakpad/src/common/mac/file_id.cc
            google-breakpad/src/common/mac/macho_id.cc
            google-breakpad/src/common/mac/macho_utilities.cc
            google-breakpad/src/common/mac/macho_walker.cc
            google-breakpad/src/common/mac/string_utilities.cc
            google-breakpad/src/common/mac/macho_reader.cc
            google-breakpad/src/common/md5.cc
            google-breakpad/src/common/mac/MachIPC.mm
            google-breakpad/src/common/dwarf/dwarf2reader.cc
            google-breakpad/src/common/mac/bootstrap_compat.cc
            google-breakpad/src/common/dwarf_cfi_to_module.cc
        )
    else()
        list(APPEND breakpadSources
            google-breakpad/src/client/linux/crash_generation/crash_generation_client.cc
            google-breakpad/src/client/linux/handler/exception_handler.cc
            google-breakpad/src/client/linux/handler/minidump_descriptor.cc
            google-breakpad/src/client/linux/log/log.cc
            google-breakpad/src/client/linux/minidump_writer/linux_dumper.cc
            google-breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
            google-breakpad/src/client/linux/minidump_writer/minidump_writer.cc
            google-breakpad/src/common/linux/elfutils.cc
            google-breakpad/src/common/linux/file_id.cc
            google-breakpad/src/common/linux/guid_creator.cc
            google-breakpad/src/common/linux/linux_libc_support.cc
            google-breakpad/src/common/linux/memory_mapped_file.cc
            google-breakpad/src/common/linux/safe_readlink.cc
        )
    endif()
endif()

if(WIN32)
    add_definitions( -DUNICODE )
    list(APPEND breakpadSources
        google-breakpad/src/client/windows/handler/exception_handler.cc
        google-breakpad/src/client/windows/crash_generation/crash_generation_client.cc
        google-breakpad/src/common/windows/guid_string.cc
    )
endif()


include_directories(.)
# ADD_DEFINITIONS( -fPIC )
add_library(crashreporter-breakpad STATIC ${breakpadSources} )
target_include_directories(crashreporter-breakpad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/google-breakpad/src/)

if(NOT MSVC)
    target_link_libraries(crashreporter-breakpad pthread)
endif()

if(WIN32 AND NOT MSVC)
    add_definitions(-fshort-wchar)
    target_link_libraries(crashreporter-breakpad "mingwex")
endif()
