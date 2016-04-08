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
# - Try to find CZMQPP headers and libraries
#
# Usage of this module as follows:
#
#     find_package(CZMQPP)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  CZMQPP_ROOT_DIR  Set this variable to the root installation of
#                            CZMQPP if the module has problems finding
#                            the proper installation path.
#
# Variables defined by this module:
#
#  CZMQPP_FOUND              System has CZMQPP libs/headers
#  CZMQPP_LIBRARIES          The CZMQPP libraries
#  CZMQPP_INCLUDE_DIR        The location of CZMQPP headers

find_path(CZMQPP_ROOT_DIR
  NAMES include/czmq++/czmqpp.hpp
  )

find_library(CZMQPP_LIBRARY
    NAMES libczmq++.a  libczmq++.la libczmq++.so 
    HINTS ${CZMQ_ROOT_DIR}/lib
    )

find_path(CZMQPP_INCLUDE_DIR
  NAMES czmqpp.hpp
  HINTS ${CZMQ_ROOT_DIR}/include
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CZMQPP DEFAULT_MSG
  CZMQPP_LIBRARY
  CZMQPP_INCLUDE_DIR
  )

set(CZMQPP_INCLUDE_DIRS ${CZMQPP_INCLUDE_DIR})
set(CZMQPP_LIBRARIES ${CZMQPP_LIBRARY})

mark_as_advanced(
  CZMQPP_ROOT_DIR
  CZMQPP_LIBRARY
  CZMQPP_INCLUDE_DIR
  )

