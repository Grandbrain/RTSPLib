#------------------------------------------------------------------------------#
#                                Base settings                                 #
#------------------------------------------------------------------------------#

TEMPLATE		=		app
TARGET			=		rtspclientgui
QT				+=		widgets network
CONFIG			+=		c++17 strict_c++


#------------------------------------------------------------------------------#
#                                Project macros                                #
#------------------------------------------------------------------------------#

DEFINES			+=															\
						QT_DEPRECATED_WARNINGS								\
						NETWORK_PROTOCOL_EXTENDED=0							\

#------------------------------------------------------------------------------#
#                            Project files settings                            #
#------------------------------------------------------------------------------#

include($$absolute_path(Core.pri, Core))
include($$absolute_path(Decoders.pri, Decoders))
include($$absolute_path(Playback.pri, Playback))
include($$absolute_path(Utilities.pri, Utilities))


#------------------------------------------------------------------------------#
#                            External dependencies                             #
#------------------------------------------------------------------------------#

CLIENT_TARGET		=	rtspclient
CLIENT_DIRECTORY	=	RTSPClient
CLIENT_INCLUDE_PATH	=	$$absolute_path($$CLIENT_DIRECTORY, $$SOURCE_PATH)
CLIENT_LIBRARY_PATH	=	$$clean_path($$OUT_PWD/../../$$CLIENT_DIRECTORY)

FFMPEG_DIRECTORY	=	$$find_directory($$EXTERNAL_PATH, "ffmpeg-*")
FFMPEG_INCLUDE_PATH	=	$$find_include_path($$EXTERNAL_PATH, $$FFMPEG_DIRECTORY)
FFMPEG_LIBRARY_PATH	=	$$find_library_path($$EXTERNAL_PATH, $$FFMPEG_DIRECTORY)


#------------------------------------------------------------------------------#
#                          Include directories settings                        #
#------------------------------------------------------------------------------#

INCLUDEPATH			+=														\
						$$CLIENT_INCLUDE_PATH								\
						$$FFMPEG_INCLUDE_PATH								\


DEPENDPATH			+=														\
						$$CLIENT_INCLUDE_PATH								\
						$$FFMPEG_INCLUDE_PATH								\


#------------------------------------------------------------------------------#
#                           External libraries settings                        #
#------------------------------------------------------------------------------#

LIBS				+=														\
						-L$$CLIENT_LIBRARY_PATH								\
						-L$$FFMPEG_LIBRARY_PATH								\

LIBS				+=														\
						-l$$CLIENT_TARGET									\
						-lavcodec											\
						-lavdevice											\
						-lavfilter											\
						-lavformat											\
						-lavutil											\
						-lswresample										\
						-lswscale											\
