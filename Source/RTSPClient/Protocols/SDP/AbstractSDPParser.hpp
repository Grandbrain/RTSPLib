/// \file AbstractSDPParser.hpp
/// \brief Contains classes and functions declarations that provide abstract SDP
/// parser interface.
/// \bug No known bugs.

#ifndef ABSTRACTSDPPARSER_HPP
#define ABSTRACTSDPPARSER_HPP

#include "SDPMediaTrackInfo.hpp"

#include <QLinkedList>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that provides abstract SDP parser interface.
		class AbstractSDPParser {
		public:

			/// Destructor.
			virtual ~AbstractSDPParser() = 0;

		public:

			/// Parses SDP document to find media track information.
			/// \param[in]	sdpData	SDP document data.
			/// \return List of parsed SDP media tracks.
			virtual QLinkedList<SDPMediaTrackInfo> parse(
				const QByteArray& sdpData) = 0;
		};
	}
}

#endif
