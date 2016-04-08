##=============================================================================
##
##  Copyright (c) Kitware, Inc.
##  All rights reserved.
##  See LICENSE.txt for details.
##
##  This software is distributed WITHOUT ANY WARRANTY; without even
##  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
##  PURPOSE.  See the above copyright notice for more information.
##
##=============================================================================
# - Try to find CZMQ headers and libraries
#
# Usage of this module as follows:
#
#     find_package(CZMQ)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  CZMQ_ROOT_DIR  Set this variable to the root installation of
#                            CZMQ if the module has problems finding
#                            the proper installation path.
#
# Variables defined by this module:
#
#  CZMQ_FOUND              System has CZMQ libs/headers
#  CZMQ_LIBRARIES          The CZMQ libraries
#  CZMQ_INCLUDE_DIR        The location of CZMQ headers

find_path(CZMQ_ROOT_DIR
  NAMES include/czmq.h
  )

find_library(CZMQ_LIBRARY
    NAMES libczmq.a  libczmq.la libczmq.so 
    HINTS ${CZMQ_ROOT_DIR}/lib
    )

find_path(CZMQ_INCLUDE_DIR
  NAMES czmq.h
  HINTS ${CZMQ_ROOT_DIR}/include
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CZMQ DEFAULT_MSG
  CZMQ_LIBRARY
  CZMQ_INCLUDE_DIR
  )

set(CZMQ_INCLUDE_DIRS ${CZMQ_INCLUDE_DIR})
set(CZMQ_LIBRARIES ${CZMQ_LIBRARY})

mark_as_advanced(
  CZMQ_ROOT_DIR
  CZMQ_LIBRARY
  CZMQ_INCLUDE_DIR
  )

