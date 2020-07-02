/// \file RTPPacket.hpp
/// \brief Contains classes and functions declarations that provide Real-time
/// Transport Protocol (RTP) packet implementation.
/// \bug No known bugs.

#ifndef RTPPACKET_HPP
#define RTPPACKET_HPP

#include <QtCore>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that provides an RTP packet implementation.
		class RTPPacket final {
		public:

			/// Parses raw RTP data.
			/// \return RTP packet.
			static RTPPacket parse(const QByteArray& data);

		public:

			/// Indicates whether the packet is valid.
			/// \retval true if the packet is valid.
			/// \retval false if the packet is not valid.
			bool isValid() const noexcept;

			/// Returns protocol version.
			/// \return Protocol version.
			quint8 getProtocolVersion() const noexcept;

			/// Returns padding size.
			/// \return Padding size.
			quint8 getPaddingSize() const noexcept;

			/// Returns profile-specific marker.
			/// \return Profile-specific marker.
			quint8 getProfileMarker() const noexcept;

			/// Returns payload type.
			/// \return Payload type.
			quint8 getPayloadType() const noexcept;

			/// Returns sequence number.
			/// \return Sequence number.
			quint16 getSequenceNumber() const noexcept;

			/// Returns timestamp.
			/// \return Timestamp.
			quint32 getTimestamp() const noexcept;

			/// Returns Synchronization source ID (SSRC).
			/// \return Synchronization source ID (SSRC).
			quint32 getSSRC() const noexcept;

			/// Returns Contributing source ID (CSRC) array.
			/// \return Contributing source ID (CSRC) array.
			QVector<quint32> getCSRC() const noexcept;

			/// Returns header extension.
			/// \return Header extension.
			QByteArray getHeaderExtension() const noexcept;

			/// Returns payload data.
			/// \return Payload data.
			QByteArray getPayloadData() const noexcept;

		private:

			/// Protocol version.
			quint8 protocolVersion_ { 0 };

			/// Padding size.
			quint8 paddingSize_ { 0 };

			/// Profile-specific marker.
			quint8 profileMarker_ { 0 };

			/// Payload type.
			quint8 payloadType_ { 0 };

			/// Sequence number.
			quint16 sequenceNumber_ { 0 };

			/// Timestamp.
			quint32 timestamp_ { 0 };

			/// Synchronization source ID (SSRC).
			quint32 SSRC_ { 0 };

			/// Contributing source ID (CSRC) array.
			QVector<quint32> CSRC_;

			/// Header extension.
			QByteArray headerExtension_;

			/// Payload data.
			QByteArray payloadData_;
		};
	}
}

#endif
