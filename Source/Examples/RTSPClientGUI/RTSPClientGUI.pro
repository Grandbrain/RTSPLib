#------------------------------------------------------------------------------#
#                                Base settings                                 #
#------------------------------------------------------------------------------#

QT				+=		widgets
TEMPLATE		=		app
TARGET			=		rtspclientgui
CONFIG			+=		c11 c++11 strict_c strict_c++
EXTERNAL_PATH	=		$$PWD/../../../External


#------------------------------------------------------------------------------#
#                              Project definitions                             #
#------------------------------------------------------------------------------#

DEFINES			+=															\
						QT_DEPRECATED_WARNINGS								\


#------------------------------------------------------------------------------#
#                            Project files settings                            #
#------------------------------------------------------------------------------#

include(Core/Core.pri)
include(Decoders/Decoders.pri)
include(Playback/Playback.pri)


#------------------------------------------------------------------------------#
#                          Include directories settings                        #
#------------------------------------------------------------------------------#

INCLUDEPATH		+=															\
						$$PWD/../../										\
						$$PWD/../../RTSPClient								\
						$$EXTERNAL_PATH/ffmpeg-4.2.0/include				\

DEPENDPATH		+=															\
						$$PWD/../../										\
						$$PWD/../../RTSPClient								\
						$$EXTERNAL_PATH/ffmpeg-4.2.0/include				\


#------------------------------------------------------------------------------#
#                           External libraries settings                        #
#------------------------------------------------------------------------------#

LIBS			+=															\
						-L$$OUT_PWD/../../RTSPClient/ -lrtspclient			\

unix:!macx {
	contains (QMAKE_HOST.arch, x86_64) {
		CONFIG (debug, debug|release) {
			LIBS		+=																\
								-L$$EXTERNAL_PATH/ffmpeg-4.2.0/lib/linux/x64/debug/		\
		}
		else {
			LIBS		+=																\
								-L$$EXTERNAL_PATH/ffmpeg-4.2.0/lib/linux/x64/release/	\
		}

		LIBS		+=														\
							-lavcodec										\
							-lavdevice										\
							-lavfilter										\
							-lavformat										\
							-lavutil										\
							-lswresample									\
							-lswscale										\
	}
	else {
		error("Currently, the project cannot be built under 32-bit architecture.")
	}
}
