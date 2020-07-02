/// \file AbstractSDPParser.cpp
/// \brief Contains classes and functions definitions that provide abstract SDP
/// parser interface.
/// \bug No known bugs.

#include "AbstractSDPParser.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Destructor.
		/// \details Defaulted default destructor.
		AbstractSDPParser::~AbstractSDPParser() = default;

		/// Parses SDP document to find media track information.
		/// \details Virtual member function that intended to parse SDP data.
		/// \param[in]	sdpData	SDP document data.
		/// \return List of parsed SDP media tracks.
		QLinkedList<SDPMediaTrackInfo> AbstractSDPParser::parse(
			const QByteArray& sdpData) {

			return { };
		}
	}
}
