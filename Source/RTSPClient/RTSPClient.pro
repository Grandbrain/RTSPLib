#------------------------------------------------------------------------------#
#                                Base settings                                 #
#------------------------------------------------------------------------------#

TARGET				=	rtspclient
TEMPLATE			=	lib
QT					-=	gui
QT					+=	network
CONFIG				+=	c11 c++11 strict_c strict_c++
DEFINES				+=	RTSPCLIENT_LIBRARY QT_DEPRECATED_WARNINGS


#------------------------------------------------------------------------------#
#                            Subdirectories settings                           #
#------------------------------------------------------------------------------#

include($$absolute_path(Base.pri, Base))
include($$absolute_path(Client.pri, Client))
include($$absolute_path(Payloads.pri, Payloads))
include($$absolute_path(Protocols.pri, Protocols))
include($$absolute_path(Utilities.pri, Utilities))


#------------------------------------------------------------------------------#
#                            External dependencies                             #
#------------------------------------------------------------------------------#

CURL_TARGET			=	curl
CURL_FILENAME		=	$$find_static_library_filename($$CURL_TARGET)
CURL_INCLUDE_PATH	=	$$find_include_path($$EXTERNAL_PATH, $$CURL_TARGET)
CURL_LIBRARY_PATH	=	$$find_library_path($$EXTERNAL_PATH, $$CURL_TARGET)
CURL_FILENAME_PATH	=	$$absolute_path($$CURL_FILENAME, $$CURL_LIBRARY_PATH)


#------------------------------------------------------------------------------#
#                          Include directories settings                        #
#------------------------------------------------------------------------------#

INCLUDEPATH			+=														\
						$$CURL_INCLUDE_PATH									\


DEPENDPATH			+=														\
						$$CURL_INCLUDE_PATH									\


#------------------------------------------------------------------------------#
#                           External libraries settings                        #
#------------------------------------------------------------------------------#

PRE_TARGETDEPS		+=														\
						$$CURL_FILENAME_PATH								\

LIBS				+=														\
						-L$$CURL_LIBRARY_PATH								\

LIBS				+=														\
						-l$$CURL_TARGET										\
