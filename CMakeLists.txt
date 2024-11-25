cmake_minimum_required(VERSION 3.25)

project(
        

        BoundWeaponFix
        VERSION 1.0.0


        # ConsiderateFollowers
        # VERSION 1.2.1


        # StaffEnchanting
        # VERSION 1.1.0
        LANGUAGES CXX

        

)



set(PROJECT_LICENSE "MIT")
set(PROJECT_FRIENDLY_NAME ${PROJECT_NAME})
set(PROJECT_LONG_NAME "SKSE CommonLibSSE-NG Plugin")
set(PROJECT_DESCRIPTION ${PROJECT_LONG_NAME})

set(PROJECT_COPYRIGHT "Copyright")


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GNUInstallDirs)
include(addpluginsources)
include(pluginconfig)
include(plugintarget)
include(pluginpackage)
include("${PROJECT_SOURCE_DIR}/local.cmake" OPTIONAL)

######## dependencies


### ==================================== DISABLE all Boost related items

# set(Boost_NO_WARN_NEW_VERSIONS 1)
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_USE_MULTITHREADED  ON)
# find_package(Boost REQUIRED COMPONENTS)
# if(Boost_FOUND)
#     target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
#     target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
# endif()