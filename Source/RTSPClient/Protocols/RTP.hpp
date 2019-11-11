/// \file RTP.hpp
/// \brief Contains classes and functions declarations that provide Real-time
/// Transport Protocol (RTP) implementation.
/// \bug No known bugs.

#ifndef RTP_HPP
#define RTP_HPP

#include "Base/Export.hpp"

#include <QtCore>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Structure that defines an RTP packet.
		struct RTPPacket {

			/// Protocol version.
			quint8 version = 2;

			/// Number of padding bytes.
			quint8 padding = 0;

			/// Profile-specific marker.
			quint8 marker = 0;

			/// Payload type.
			quint8 type = 0;

			/// Packet sequence number.
			quint16 number = 0;

			/// Packet timestamp.
			quint32 timestamp = 0;

			/// Synchronization source.
			quint32 SSRC = 0;

			/// Contributing sources.
			QVector<quint32> CSRC;

			/// Extension header data.
			/// \warning This field is a reference
			/// and does not contain actual data.
			QByteArray extension;

			/// Payload data.
			/// \warning This field is a reference
			/// and does not contain actual data.
			QByteArray payload;
		};

		/// Class that provides RTP implementation.
		class RTSPCLIENT_EXPORT RTP {

			Q_DISABLE_COPY(RTP)

		public:

			/// Parses an RTP packet raw data.
			/// \return RTP packet.
			static RTPPacket parse(const QByteArray& data);
		};
	}
}

#endif
