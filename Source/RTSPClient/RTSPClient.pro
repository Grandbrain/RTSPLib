#------------------------------------------------------------------------------#
#                                Base settings                                 #
#------------------------------------------------------------------------------#

QT				-=		gui
QT				+=		network
TEMPLATE		=		lib
TARGET			=		rtspclient
CONFIG			+=		c11 c++11 strict_c strict_c++
EXTERNAL_PATH	=		$$PWD/../../External


#------------------------------------------------------------------------------#
#                              Project definitions                             #
#------------------------------------------------------------------------------#

DEFINES			+=															\
						RTSPCLIENT_LIBRARY									\
						QT_DEPRECATED_WARNINGS								\


#------------------------------------------------------------------------------#
#                             Project files settings                           #
#------------------------------------------------------------------------------#

include(Base/Base.pri)
include(Client/Client.pri)
include(Payloads/Payloads.pri)
include(Protocols/Protocols.pri)
include(Utilities/Utilities.pri)


#------------------------------------------------------------------------------#
#                          Include directories settings                        #
#------------------------------------------------------------------------------#

INCLUDEPATH		+=															\
						$$EXTERNAL_PATH/curl-7.65.1/include					\


DEPENDPATH		+=															\
						$$EXTERNAL_PATH/curl-7.65.1/include					\


#------------------------------------------------------------------------------#
#                           External libraries settings                        #
#------------------------------------------------------------------------------#

unix:!macx {
	contains (QMAKE_HOST.arch, x86_64) {
		CONFIG (debug, debug|release) {
			PRE_TARGETDEPS		+=																	\
										$$EXTERNAL_PATH/curl-7.65.1/lib/linux/x64/debug/libcurl.a	\

			LIBS				+=																	\
										-L$$EXTERNAL_PATH/curl-7.65.1/lib/linux/x64/debug/ -lcurl	\
		}
		else {
			PRE_TARGETDEPS		+=																	\
										$$EXTERNAL_PATH/curl-7.65.1/lib/linux/x64/release/libcurl.a	\

			LIBS				+=																	\
										-L$$EXTERNAL_PATH/curl-7.65.1/lib/linux/x64/release/ -lcurl	\
		}
	}
	else {
		error("Currently, the project cannot be built under 32-bit architecture.")
	}
}
