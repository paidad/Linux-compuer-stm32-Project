cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# 引入插件原生工具链配置
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/target.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)

project(StdPeriph_Template C CXX ASM)

# 1. 自动搜集所有源文件
file(GLOB_RECURSE APP_SOURCES "System/*.c" "User/*.c" "Hardware/*.c")
file(GLOB_RECURSE DRIVER_SOURCES "Library/*.c" "Start/*.c")
file(GLOB_RECURSE ASM_SOURCES "Start/*.s")

add_executable(${PROJECT_NAME} 
    ${APP_SOURCES} 
    ${DRIVER_SOURCES} 
    ${ASM_SOURCES}
)

# 2. 包含所有头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    System
    User
    Hardware
    Library
    Start
)

# 3. 核心宏定义 (决定生死)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    USE_STDPERIPH_DRIVER
    STM32F10X_MD
)

# 4. 编译与链接选项
target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -Wall
    -g3 -gdwarf-2
)

target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -T${CMAKE_CURRENT_SOURCE_DIR}/stm32f103x8_flash.ld
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
)