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
# - Try to find ZeroMQ headers and libraries
#
# Usage of this module as follows:
#
#     find_package(ZeroMQ)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  ZeroMQ_ROOT  Set this variable to the root installation of
#                            ZeroMQ if the module has problems finding
#                            the proper installation path.
#
# Variables defined by this module:
#
#  ZeroMQ_FOUND              System has ZeroMQ libs/headers
#  ZeroMQ_LIBRARIES          The ZeroMQ libraries
#  ZeroMQ_INCLUDE        The location of ZeroMQ headers

find_path(ZeroMQ_ROOT
  NAMES include/zmq.h
  )

find_library(ZeroMQ_LIBRARY
    NAMES libzmq-static.a zmq libzmq
    HINTS ${ZeroMQ_ROOT}/lib
    )

find_path(ZeroMQ_INCLUDE
  NAMES zmq.h
  HINTS ${ZeroMQ_ROOT}/include
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZeroMQ DEFAULT_MSG
  ZeroMQ_LIBRARY
  ZeroMQ_INCLUDE
  )

set(ZeroMQ_INCLUDE_DIRS ${ZeroMQ_INCLUDE})
set(ZeroMQ_LIBRARIES ${ZeroMQ_LIBRARY})

mark_as_advanced(
  ZeroMQ_ROOT
  ZeroMQ_LIBRARY
  ZeroMQ_INCLUDE
  )

