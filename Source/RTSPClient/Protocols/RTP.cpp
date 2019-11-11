/// \file RTP.cpp
/// \brief Contains classes and functions definitions that provide
/// Real-time Transport Protocol (RTP) implementation.
/// \bug No known bugs.

#include "RTP.hpp"
#include "Utilities/ArrayUtils.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/*
		/// Assemblies an H.264 frame from RTP payload.
		/// \details Assemblies an H.264 frame from separate NAL units.
		/// \param[in]	packet		RTP packet.
		/// \param[in]	boundaries	Payload boundaries.
		/// \param[out]	frame		H.264 output frame.
		/// \retval true if the frame is assembled.
		/// \retval false if the frame is not assembled.
		bool assemblyFrame(const QByteArray& packet,
						   const QPair<int, int>& boundaries,
						   QByteArray& frame) {

			if (boundaries.first < 0	||
				boundaries.second <= 2	||
				packet.size() < (boundaries.first + boundaries.second))
				return false;

			auto result = false;

			const uint8_t sequence[] = { 0x00, 0x00, 0x00, 0x01 };

			uint8_t type = static_cast<uint8_t>(packet[boundaries.first]) &
						   static_cast<uint8_t>(0x1F);;

			if (type >= 1 && type <= 23)
				type = 1;

			if (type == 1) {
				frame.clear();

				frame.append(
					reinterpret_cast<const char*>(sequence),
					sizeof(sequence)
				);

				frame.append(
					packet.data() + boundaries.first,
					boundaries.second
				);

				result = true;
			}
			else if (type == 28) {
				uint8_t start =
					static_cast<uint8_t>(packet[boundaries.first + 1]) >>
					static_cast<uint8_t>(0x07);

				uint8_t end =
					static_cast<uint8_t>(packet[boundaries.first + 1]) &
					static_cast<uint8_t>(0x40);

				uint8_t nal =
					(static_cast<uint8_t>(packet[boundaries.first]) &
					 static_cast<uint8_t>(0xE0)) |
					(static_cast<uint8_t>(packet[boundaries.first + 1]) &
					 static_cast<uint8_t>(0x1F));

				if(start) {
					frame.clear();

					frame.append(
						reinterpret_cast<const char*>(sequence),
						sizeof(sequence)
					);

					frame.append(
						reinterpret_cast<const char*>(&nal),
						sizeof(nal)
					);
				}

				frame.append(
					packet.data() + boundaries.first + 2,
					boundaries.second - 2
				);

				if (end)
					result = true;
			}

			return result;
		}
		*/

		///
		/// \details
		/// \return
		RTPPacket RTP::parse(const QByteArray& data) {
			if (data.size() < 12) return { };

			auto version	= (static_cast<quint8>(data[0]) & 0xC0) >> 6;
			auto padding	= (static_cast<quint8>(data[0]) & 0x20) >> 5;
			auto extension	= (static_cast<quint8>(data[0]) & 0x10) >> 4;
			auto countCSRC	= (static_cast<quint8>(data[0]) & 0x0F) >> 0;
			auto marker		= (static_cast<quint8>(data[1]) & 0x80) >> 7;
			auto type		= (static_cast<quint8>(data[1]) & 0x7F) >> 0;
			auto number		= ArrayUtils::read<quint16>(data.data() + 2, true);
			auto timestamp	= ArrayUtils::read<quint32>(data.data() + 4, true);
			auto SSRC		= ArrayUtils::read<quint32>(data.data() + 8, true);

			quint8 paddingSize		= padding != 0 ? data.back() : 0;
			quint32 CSRC[15]		= {0};

			auto extensionOffset	= 12 + countCSRC * 4;
			auto extensionSize		= 0;

			if (countCSRC <= 15 && data.size() >= (12 + countCSRC * 4)) {
				for (auto i = 0; i < countCSRC; ++i)
					CSRC[i] = ArrayUtils::read<quint32>(
						data.data() + (12 + i * 4), true);
			}

			if (extension != 0 && data.size() >= (16 + countCSRC * 4)) {
				extensionSize = 4 + 4 * ArrayUtils::read<quint16>(
					data.data() + (14 + countCSRC * 4), true);
			}

			auto payloadOffset	= 12 + countCSRC * 4 + extensionSize;

			auto payloadSize	= payloadOffset + paddingSize < data.size()
								  ? data.size() - payloadOffset - paddingSize
								  : 0;

			RTPPacket packet;
			packet.version		= version;
			packet.padding		= paddingSize;
			packet.marker		= marker;
			packet.type			= type;
			packet.number		= number;
			packet.timestamp	= timestamp;
			packet.SSRC			= SSRC;

			packet.extension = QByteArray::fromRawData(
				data.data() + extensionOffset,
				extensionSize
			);

			packet.payload = QByteArray::fromRawData(
				data.data() + payloadOffset,
				payloadSize
			);

			packet.CSRC.reserve(countCSRC);
			std::copy(CSRC, CSRC + countCSRC, std::back_inserter(packet.CSRC));

			return packet;
		}
	}
}
