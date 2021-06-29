cmake_minimum_required(VERSION 3.10) # TODO: find minimal version
set(PROJECT_NAME hpicview)
project(${PROJECT_NAME})

# TODO: move all libjpeg-related commands into separate CMakeLists.txt
# TODO: find way of hiding this self-build version of libjpeg so it does not clash with the one loaded by wxWidgets
# TODO: until the former is done, at least check for compatibility during build
set(JPEGTRAN_SOURCES
# selectively compiling the necessary parts of libjpeg for static linking
#submodules/libjpeg/jdatasrc.c # for jpeg_mem_src
#submodules/libjpeg/jcapimin.c # for jpeg_finish_compress
#submodules/libjpeg/jmemmgr.c # for jinit_memory_mgr
#submodules/libjpeg/jmemnobs.c # for in-memory jpeg_open_backing_store
#submodules/libjpeg/jdapimin.c # for jpeg_destroy_decompress
#submodules/libjpeg/jdatadst.c # for jpeg_mem_dest
#submodules/libjpeg/jcomapi.c # for jpeg_abort
#submodules/libjpeg/jdmarker.c # for jpeg_resync_to_restart
#submodules/libjpeg/jctrans.c # for jpeg_copy_critical_parameters
#submodules/libjpeg/jcarith.c # for jinit_arith_encoder
#submodules/libjpeg/jaricom.c # for jpeg_aritab
#submodules/libjpeg/jdtrans.c # for jpeg_read_coefficients
#submodules/libjpeg/jdcoefct.c # for jinit_d_coef_controller
#submodules/libjpeg/jdarith.c # for jinit_arith_decoder
#submodules/libjpeg/jdinput.c # for jpeg_core_output_dimensions
#submodules/libjpeg/jutils.c # for jcopy_block_row
# dependencies of the implementations above
#submodules/libjpeg/cdjpeg.h
#submodules/libjpeg/transupp.h
#submodules/libjpeg/jinclude.h
#submodules/libjpeg/jpeglib.h
#submodules/libjpeg/jerror.h
#submodules/libjpeg/jinclude.h
#submodules/libjpeg/jpeglib.h
#submodules/libjpeg/jmemsys.h
#submodules/libjpeg/jinclude.h
#submodules/libjpeg/jpeglib.h
# TODO: add dependencies recursively

# brute-force aproach: just compile everything not having a main function
submodules/libjpeg/cderror.h
submodules/libjpeg/cdjpeg.c
submodules/libjpeg/cdjpeg.h
submodules/libjpeg/jaricom.c
submodules/libjpeg/jcapimin.c
submodules/libjpeg/jcapistd.c
submodules/libjpeg/jcarith.c
submodules/libjpeg/jccoefct.c
submodules/libjpeg/jccolor.c
submodules/libjpeg/jcdctmgr.c
submodules/libjpeg/jchuff.c
submodules/libjpeg/jcinit.c
submodules/libjpeg/jcmainct.c
submodules/libjpeg/jcmarker.c
submodules/libjpeg/jcmaster.c
submodules/libjpeg/jcomapi.c
submodules/libjpeg/jcparam.c
submodules/libjpeg/jcprepct.c
submodules/libjpeg/jcsample.c
submodules/libjpeg/jctrans.c
submodules/libjpeg/jdapimin.c
submodules/libjpeg/jdapistd.c
submodules/libjpeg/jdarith.c
submodules/libjpeg/jdatadst.c
submodules/libjpeg/jdatasrc.c
submodules/libjpeg/jdcoefct.c
submodules/libjpeg/jdcolor.c
submodules/libjpeg/jdct.h
submodules/libjpeg/jddctmgr.c
submodules/libjpeg/jdhuff.c
submodules/libjpeg/jdinput.c
submodules/libjpeg/jdmainct.c
submodules/libjpeg/jdmarker.c
submodules/libjpeg/jdmaster.c
submodules/libjpeg/jdmerge.c
submodules/libjpeg/jdpostct.c
submodules/libjpeg/jdsample.c
submodules/libjpeg/jdtrans.c
submodules/libjpeg/jerror.c
submodules/libjpeg/jerror.h
submodules/libjpeg/jfdctflt.c
submodules/libjpeg/jfdctfst.c
submodules/libjpeg/jfdctint.c
submodules/libjpeg/jidctflt.c
submodules/libjpeg/jidctfst.c
submodules/libjpeg/jidctint.c
submodules/libjpeg/jinclude.h
submodules/libjpeg/jmemmgr.c
submodules/libjpeg/jmemnobs.c
submodules/libjpeg/jmemsys.h
submodules/libjpeg/jmorecfg.h
submodules/libjpeg/jpegint.h
submodules/libjpeg/jpeglib.h
submodules/libjpeg/jquant1.c
submodules/libjpeg/jquant2.c
submodules/libjpeg/jutils.c
submodules/libjpeg/jversion.h
submodules/libjpeg/transupp.c
submodules/libjpeg/transupp.h
)
# auto-generating jconfig.h. it must exist so the compiler does not pick up the system-suppiled one (if there is one)
if(MSVC)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libjpeg/jconfig.vc ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h # this actually seems to suffice
        DEPENDS ${JPEGTRAN_SOURCES}
    )
    file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libjpeg/jconfig.h) # must delete UNIX variant to avoid compiler confusion
elseif(UNIX)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libjpeg
        COMMAND ./configure
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libjpeg/jconfig.h ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h
        DEPENDS ${JPEGTRAN_SOURCES}
    )
else()
    message(FATAL_ERROR "I have no idea how to generate jconfig.h on this system.")
endif()
set(CPPJPEGTRAN_NAME cppjpegtran)
add_library(${CPPJPEGTRAN_NAME} STATIC
src/jpegtran.cpp
src/jpegtran.hpp 
${JPEGTRAN_SOURCES}
${CMAKE_CURRENT_BINARY_DIR}/jconfig.h
)
target_include_directories(${CPPJPEGTRAN_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} submodules/libjpeg)
set_target_properties(${CPPJPEGTRAN_NAME} PROPERTIES C_VISIBILITY_PRESET hidden)

add_subdirectory(submodules/wxWEBPHandler)

#set(Boost_USE_STATIC_LIBS ON) # on Windows, this may lead to the slightly confusing error "Could NOT find Boost (missing: filesystem) (found version "1.74.0")"
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
add_executable(${PROJECT_NAME} WIN32 
src/about.cpp
src/clipboard.cpp
src/directory_iteration.cpp
src/droptarget.hpp
src/extensions.cpp
src/extensions.hpp
src/file_handling.cpp
src/GUIFrame.cpp
src/GUIFrame.h
src/hpicviewApp.cpp
src/hpicviewApp.hpp
src/hpicviewMain.cpp
src/hpicviewMain.hpp
src/rotate.cpp
src/zoom.cpp
src/sstatbmp.cpp
src/sstatbmp.h
)
target_include_directories(${PROJECT_NAME} PRIVATE submodules/wxWEBPHandler/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE wxUSE_WEBP wxOVERRIDE=)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} Boost::filesystem ${CPPJPEGTRAN_NAME} wxWEBPHandler)
if(MSVC)
    target_sources(${PROJECT_NAME} PRIVATE src/hpicview.rc resources/icon.ico) # executable icon
    # have MSVC shut up about ansi C functions being "unsafe"
    target_compile_definitions(${CPPJPEGTRAN_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    # TODO: also suppress MSVC C4996
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    # TODO: find out how to handle https://stackoverflow.com/questions/3007312/resolving-lnk4098-defaultlib-msvcrt-conflicts-with
endif()

install(TARGETS ${PROJECT_NAME}
RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# TODO optional for i in *.svg ; do inkscape --without-gui $i --export-height=48 -e $i.png ; done
# TODO install resources/icon.svg to …/share/icons/hicolor/scalable/apps/hpicview.svg
# TODO install hpicview.desktop …/share/applications/hpicview.desktop
