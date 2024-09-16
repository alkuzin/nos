cmake_minimum_required(VERSION 3.20.0)

# Set project name & programming languages
project(NOS LANGUAGES CXX ASM_NASM)

# Check if the compiler is g++
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires g++ as the C++ compiler!")
endif()

set(CMAKE_CXX_STANDARD 23)          # Using C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Enforce the standard
set(CMAKE_CXX_EXTENSIONS OFF)       # Disable compiler-specific extensions

# Set paths
set(INCLUDE_DIR        ${CMAKE_SOURCE_DIR}/../include)
set(KERNEL_DIR         ${CMAKE_SOURCE_DIR}/../kernel)
set(BOOT_DIR           ${CMAKE_SOURCE_DIR}/../boot)
set(LIB_DIR            ${CMAKE_SOURCE_DIR}/../lib)
set(KERNEL_DRIVERS_DIR ${KERNEL_DIR}/drivers)
set(KERNEL_COMMON_DIR  ${KERNEL_DIR}/common)
set(KERNEL_SHELL_DIR   ${KERNEL_DIR}/shell)
set(KERNEL_CPU_DIR     ${KERNEL_DIR}/cpu)
set(KERNEL_GFX_DIR     ${KERNEL_DIR}/gfx)
set(KERNEL_FS_DIR      ${KERNEL_DIR}/fs)
set(KERNEL_MM_DIR      ${KERNEL_DIR}/mm)

# List of kernel library source files
set(LIB_SOURCES
    "${LIB_DIR}/math/math.cpp"
    "${LIB_DIR}/string/string.cpp"
    "${LIB_DIR}/stdlib/stdlib.cpp"
    "${LIB_DIR}/stdlib/sort.cpp"
    "${LIB_DIR}/stdlib/panic.cpp"
    "${LIB_DIR}/stdlib/printk.cpp"
    "${LIB_DIR}/stdlib/vsnprintk.cpp"
)

# List of kernel core source files
set(KERNEL_SOURCES
    "${KERNEL_DIR}/kernel.cpp"
    "${KERNEL_DIR}/version.cpp"

    # Kernel common directory:
    "${KERNEL_COMMON_DIR}/login.cpp"
    "${KERNEL_COMMON_DIR}/nosstd.cpp"
    "${KERNEL_COMMON_DIR}/tty.cpp"
    
    # Kernel cpu directory:
    "${KERNEL_CPU_DIR}/gdt.cpp"
    "${KERNEL_CPU_DIR}/idt.cpp"
    "${KERNEL_CPU_DIR}/irq.cpp"

    # Kernel drivers directory:
    "${KERNEL_DRIVERS_DIR}/keyboard.cpp"
    "${KERNEL_DRIVERS_DIR}/timer.cpp"

    # Kernel fs directory:
    "${KERNEL_FS_DIR}/initrd.cpp"
    "${KERNEL_FS_DIR}/vfs.cpp"

    # Kernel gfx directory:
    "${KERNEL_GFX_DIR}/gfx.cpp"
    "${KERNEL_GFX_DIR}/vbe.cpp"
    "${KERNEL_GFX_DIR}/vbefont.cpp"

    # Kernel mm directory:
    "${KERNEL_MM_DIR}/kheap.cpp"
    "${KERNEL_MM_DIR}/mm.cpp"
    "${KERNEL_MM_DIR}/pmm.cpp"
    "${KERNEL_MM_DIR}/vmm.cpp"

    # Kernel shell directory:
    "${KERNEL_SHELL_DIR}/cmd.cpp"
    "${KERNEL_SHELL_DIR}/ksh.cpp"
    "${KERNEL_SHELL_DIR}/ls.cpp"
)

# List of kernel assembly source files
set(ASM_SOURCES
    "${KERNEL_CPU_DIR}/gdt_flush.s"
    "${KERNEL_CPU_DIR}/idt_flush.s"
    "${BOOT_DIR}/boot.s"
)

# List of all source files
set(SOURCES
    ${LIB_SOURCES}
    ${KERNEL_SOURCES}
)

set(CXXFLAGS
    "-Wall"                 # Enable all compiler's warning messages
    "-Wextra"               # Enable additional warning messages not covered by -Wall
    "-Werror"               # Treat all warnings as errors
    "-g"                    # Generate debug information
    "-std=c++23"            # Use the C++23 standard
    "-m32"                  # Generate 32-bit code
    "-O2"                   # Optimize the code for performance (level 2 optimization)
    "-nostdlib"             # Do not link against the standard library
    "-nodefaultlibs"        # Do not use the default libraries
    "-fno-pie"              # Disable Position Independent Executable (PIE) generation (security feature)
    "-fno-exceptions"       # Disable support for C++ exceptions
    "-fno-rtti"             # Disable Run-Time Type Information (RTTI) support
    "-fno-stack-protector"  # Disable stack protection (security feature)
    "-fno-builtin"          # Disable built-in functions
    "-ffreestanding"        # Indicate that the code does not rely on any standard library features
)

set(LDFLAGS 
    "-z" "noexecstack"        # Preventing execution of code on the stack (security feature)
    "-m" "elf_i386"           # Specify the output format as ELF for 32-bit x86 architecture
)

set(ASMFLAGS
    "-f elf"                  # Generate output in the ELF format.
)

# List to hold the object files generated from assembly
set(ASM_OBJECTS)

# Custom command to assemble each assembly file using NASM
foreach(ASM_FILE ${ASM_SOURCES})
    get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)     # Base name without extension
    set(OBJ_FILE ${CMAKE_CURRENT_BINARY_DIR}/${ASM_NAME}.o)  # Output object file
    list(APPEND ASM_OBJECTS ${OBJ_FILE})

    add_custom_command(
        OUTPUT ${OBJ_FILE}
        COMMAND nasm ${ASMFLAGS} -o ${OBJ_FILE} ${ASM_FILE}
        DEPENDS ${ASM_FILE}
    )
endforeach()

# Single object file from the C++ source files and the assembly files
add_library(kernel_objects OBJECT ${SOURCES} ${ASM_OBJECTS})

# Compiler and linker flags
target_compile_options(kernel_objects PRIVATE ${CXXFLAGS})

# Include directories
target_include_directories(kernel_objects PRIVATE ${INCLUDE_DIR} ${LIB_DIR})

# Executable that uses the object file
add_executable(kernel ${ASM_OBJECTS} $<TARGET_OBJECTS:kernel_objects>)

set_source_files_properties(
  ${ASM_OBJECTS}
  properties
  external_object true
  generated true
)

# Link the additional object files
target_link_libraries(kernel PRIVATE ${ASM_OBJECTS})

# Set the linker to ld & link with custom linker script
set_target_properties(${NAME} PROPERTIES LINK_FLAGS "${LDFLAGS} -T ${LINKER_SCRIPT}")
set(CMAKE_CXX_LINK_EXECUTABLE "ld <LINK_FLAGS> -T${BOOT_DIR}/linker.ld -o <TARGET> <OBJECTS> ")
target_link_options(kernel PRIVATE ${LDFLAGS})

# Set project variables
set(NAME "kernel")
set(ISO_DIR "${CMAKE_BINARY_DIR}/iso")
set(NAME_ISO "${CMAKE_BINARY_DIR}/nos.iso")

# Custom command to build the ISO
add_custom_target(build-iso ALL DEPENDS ${NAME}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_DIR}/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${NAME}> ${ISO_DIR}/boot/kernel.elf
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/../boot/grub/grub.cfg ${ISO_DIR}/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o ${NAME_ISO} ${ISO_DIR}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building ISO image"
)

# Custom command to initialize the ISO with QEMU
add_custom_target(init-iso
    COMMAND qemu-system-i386 -m 2024 -cdrom ${NAME_ISO}
    DEPENDS build-iso
    COMMENT "Initializing ISO with QEMU"
)

# Custom command to initialize the build
add_custom_target(init DEPENDS init-iso)

# Custom command for debugging
add_custom_target(debug
    COMMAND qemu-system-i386 -s -S -m 2024 -cdrom ${NAME_ISO} & gdb ${CMAKE_BINARY_DIR}/${NAME} -ex "target remote localhost:1234" -tui
    DEPENDS build-iso
    COMMENT "Debugging with GDB"
)