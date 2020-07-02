/// \file RTP.cpp
/// \brief Contains classes and functions definitions that provide
/// Real-time Transport Protocol (RTP) implementation.
/// \bug No known bugs.

#include "RTPPacket.hpp"

#include <QDataStream>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		namespace {

			/// Minimum RTP header size.
			/// \details RTP header size without any CSRC, header extension
			/// and payload.
			constexpr int MINIMUM_RTP_HEADER_SIZE { 12 };

			/// RTP protocol version.
			/// \details Current supported RTP protocol version.
			constexpr quint8 RTP_PROTOCOL_VERSION { 2 };
		}

		/// Parses raw RTP data.
		/// \details Parses raw RTP data based on RFC 3550.
		/// \return RTP packet.
		RTPPacket RTPPacket::parse(const QByteArray& data) {
			if (data.size() < MINIMUM_RTP_HEADER_SIZE) return { };

			QDataStream stream(data);

			quint8 byte0, byte1;
			stream >> byte0 >> byte1;

			quint8	protocolVersion	= byte0 >> 6 & 0x03;
			quint8	paddingBit		= byte0 >> 5 & 0x01;
			quint8	extensionBit	= byte0 >> 4 & 0x01;
			quint8	numberCSRC		= byte0 >> 0 & 0x0F;
			quint8	markerBit		= byte1 >> 7 & 0x01;
			quint8	payloadType		= byte1 >> 0 & 0x7F;
			quint8	paddingSize		= paddingBit == 0 ? 0 : data.back();
			quint16	sequenceNumber;
			quint32 timestamp;
			quint32 SSRC;

			QVector<quint32>	CSRC;
			QByteArray			headerExtension;

			stream >> sequenceNumber >> timestamp >> SSRC;

			if (numberCSRC > 0) {
				CSRC.resize(numberCSRC);

				for (auto& e : CSRC) {
					if (stream.atEnd() || stream.status() != QDataStream::Ok)
						return { };

					stream >> e;

					if (stream.status() != QDataStream::Ok)
						return { };
				}
			}

			if (extensionBit != 0) {
				quint16 extensionDataSize;
				stream >> extensionDataSize >> extensionDataSize;

				if (stream.status() != QDataStream::Ok)
					return { };

				auto headerExtensionOffset =
					MINIMUM_RTP_HEADER_SIZE + CSRC.size() * 4;

				auto headerExtensionSize = extensionDataSize * 4 + 4;

				if ((data.size() - headerExtensionOffset - paddingSize) <
					headerExtensionSize)
					return { };

				headerExtension = QByteArray(
					data.data() + headerExtensionOffset,
					headerExtensionSize
				);
			}

			auto payloadDataOffset =
				MINIMUM_RTP_HEADER_SIZE + CSRC.size() * 4 +
				headerExtension.size();

			auto payloadDataSize =
				data.size() - payloadDataOffset - paddingSize;

			RTPPacket packet;
			packet.protocolVersion_	= protocolVersion;
			packet.paddingSize_		= paddingSize;
			packet.profileMarker_	= markerBit;
			packet.payloadType_		= payloadType;
			packet.sequenceNumber_	= sequenceNumber;
			packet.timestamp_		= timestamp;
			packet.SSRC_			= SSRC;
			packet.CSRC_			= std::move(CSRC);
			packet.headerExtension_	= std::move(headerExtension);
			packet.payloadData_		= QByteArray(data.data() +
												 payloadDataOffset,
												 payloadDataSize);

			return packet;
		}

		/// Indicates whether the packet is valid.
		/// \details Checks if the RTP protocol version is parsed correctly.
		/// \retval true if the packet is valid.
		/// \retval false if the packet is not valid.
		bool RTPPacket::isValid() const noexcept {
			return getProtocolVersion() == RTP_PROTOCOL_VERSION;
		}

		/// Returns protocol version.
		/// \details Returns the value of the RTP protocol version.
		/// \return Protocol version.
		quint8 RTPPacket::getProtocolVersion() const noexcept {
			return protocolVersion_;
		}

		/// Returns padding size.
		/// \details Returns the number of padding bytes of the RTP packet.
		/// \return Padding size.
		quint8 RTPPacket::getPaddingSize() const noexcept {
			return paddingSize_;
		}

		/// Returns profile-specific marker.
		/// \details Returns the profile-specific marker of the RTP packet.
		/// \return Profile-specific marker.
		quint8 RTPPacket::getProfileMarker() const noexcept {
			return profileMarker_;
		}

		/// Returns payload type.
		/// \details Returns the value of the RTP payload type.
		/// \return Payload type.
		quint8 RTPPacket::getPayloadType() const noexcept {
			return payloadType_;
		}

		/// Returns sequence number.
		/// \details Returns the sequence number of the RTP packet.
		/// \return Sequence number.
		quint16 RTPPacket::getSequenceNumber() const noexcept {
			return sequenceNumber_;
		}

		/// Returns timestamp.
		/// \details Returns the timestamp of the RTP packet.
		/// \return Timestamp.
		quint32 RTPPacket::getTimestamp() const noexcept {
			return timestamp_;
		}

		/// Returns Synchronization source ID (SSRC).
		/// \details Returns the SSRC value of the RTP stream.
		/// \return Synchronization source ID (SSRC).
		quint32 RTPPacket::getSSRC() const noexcept {
			return SSRC_;
		}

		/// Returns Contributing source ID (CSRC) array.
		/// \details Returns the CSRC values of the RTP stream.
		/// \return Contributing source ID (CSRC) array.
		QVector<quint32> RTPPacket::getCSRC() const noexcept {
			return CSRC_;
		}

		/// Returns header extension.
		/// \details Returns the header extension of the RTP packet.
		/// \return Header extension.
		QByteArray RTPPacket::getHeaderExtension() const noexcept {
			return headerExtension_;
		}

		/// Returns payload data.
		/// \details Returns the payload data of the RTP packet.
		/// \return Payload data.
		QByteArray RTPPacket::getPayloadData() const noexcept {
			return payloadData_;
		}
	}
}
