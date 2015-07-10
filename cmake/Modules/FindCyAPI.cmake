# Locate the Cypress API for
#
# This module defines the following variables:
# CYAPI_FOUND TRUE if the Cypress API was found
# CYAPI_HEADER_FILE The location of the API header
# CYAPI_INCLUDE_DIRS The location of header files
# CYAPI_LIBRARIES The Cypress library files
# CYPRESS_LICENSE Path to Cypress license shipped with FX3 SDK

if(NOT WIN32)
	return()
endif()
set(FX3_SDK_PATH "$ENV{FX3_INSTALL_PATH}" CACHE PATH "Path to the Cypress FX3 SDK")

if(NOT EXISTS "${FX3_SDK_PATH}")
	message(STATUS
	"Cypress backend not available. The following location does not exist: FX3_SDK_PATH=${FX3_SDK_PATH}")
	return()
endif()
find_file(CYAPI_HEADER_FILE
	NAMES
	CyAPI.h
	PATHS
	"${FX3_SDK_PATH}/library/cpp"
	PATH_SUFFIXES
	include inc
	)
mark_as_advanced(CYAPI_HEADER_FILE)

get_filename_component(CYAPI_INCLUDE_DIRS "${CYAPI_HEADER_FILE}" PATH)

if(MSVC)
	if(CMAKE_CL_64)
		set(CYAPI_ARCH x64)
	else(CMAKE_CL_64)
		set(CYAPI_ARCH x86)
	endif(CMAKE_CL_64)
elseif(CMAKE_COMPILER_IS_GNUCC)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CYAPI_ARCH x64)
	else(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CYAPI_ARCH x86)
	endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
endif()

find_library(CYAPI_LIBRARY
NAMES
CyAPI
PATHS
"${FX3_SDK_PATH}/library/cpp"
PATH_SUFFIXES
lib/${CYAPI_ARCH}
)
mark_as_advanced(CYAPI_LIBRARY)

if(CYAPI_LIBRARY)
	set(CYAPI_LIBRARIES "${CYAPI_LIBRARY}" SetupAPI.lib)
endif()

set(CYPRESS_LICENSE "${FX3_SDK_PATH}/license/license.txt")

if(CYAPI_INCLUDE_DIRS AND CYAPI_LIBRARIES)
	set(CYAPI_FOUND TRUE)
endif()
if(CYAPI_FOUND)
	set(CMAKE_REQUIRED_INCLUDES "${CYAPI_INCLUDE_DIRS}")
	message(STATUS "CyAPI includes: ${CYAPI_INCLUDE_DIRS}")
	message(STATUS "CyAPI libs: ${CYAPI_LIBRARIES}")	
endif()
if(NOT CYAPI_FOUND AND REQUIRED)
	message(FATAL_ERROR "Cypress API not found. Double-check your FX3_SDK_PATH value.")
endif()