set(PROJECT_NAME CUtils)

# Source groups
set(Header_Files
    "Encryption.hpp"
    "INIParser.hpp"
    "NoisePerlin.hpp"
    "Notification.hpp"
    "Options.hpp"
    "RTTI.hpp"
    "Singleton.hpp"
    "SystemConfiguration.hpp"
    "Timer.hpp"
    "UnitTests.hpp"
    "StringHelper.hpp"
    "Macroses.hpp"
    "Filesystem.hpp"
    "Plugins.hpp"
    "Multithread.hpp"
    "Fusion.hpp"
    "Random.hpp"
    "Coroutine.hpp"
    "DateTime.hpp"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "Encryption.cpp"
    "INIParser.cpp"
    "NoisePerlin.cpp"
    "Notification.cpp"
    "Options.cpp"
    "RTTI.cpp"
    "Singleton.cpp"
    "SystemConfiguration.cpp"
    "Timer.cpp"
    "UnitTests.cpp"
    "StringHelper.cpp"
    "Macroses.cpp"
    "Filesystem.cpp"
    "Plugins.cpp"
    "Multithread.cpp"
    "Fusion.cpp"
    "Random.cpp"
    "Coroutine.cpp"
    "DateTime.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(no_group
	"Common.hpp"
)
source_group(" " FILES ${no_group})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
	${no_group}
)

# Target
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE CUtils)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

# Compile definitions
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_LIB;"
        "UNICODE;"
        "_UNICODE"
    )

elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_LIB;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

# Compile and link options
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
endif()
