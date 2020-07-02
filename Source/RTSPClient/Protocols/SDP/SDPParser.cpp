/// \file SDPParser.cpp
/// \brief Contains classes and functions definitions that provide SDP parser
/// implementation.
/// \bug No known bugs.

#include "SDPParser.hpp"

#include "Payloads/Codecs/H264CodecInfo.hpp"
#include "Payloads/Codecs/MJPEGCodecInfo.hpp"

#include <QTextStream>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Default constructor.
		/// \details Initializes object fields.
		SDPParser::SDPParser() noexcept
			: currentMediaTrack_(mediaTracksDictionary_.end()) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		SDPParser::~SDPParser() noexcept = default;

		/// Parses SDP document to find media track information.
		/// \details
		/// \param[in]	sdpData	SDP document data.
		/// \return List of parsed SDP media tracks.
		QLinkedList<SDPMediaTrackInfo>
			SDPParser::parse(const QByteArray& sdpData) {

			if (sdpData.isEmpty()) return { };

			mediaTracksDictionary_.clear();
			currentMediaTrack_ = mediaTracksDictionary_.end();

			QTextStream stream(sdpData);

			while (!stream.atEnd()) {
				auto line = stream.readLine();
				if (line.isEmpty()) continue;

				if (line.startsWith('m'))
					parseMediaLine(line);
				else if (line.startsWith('a'))
					parseAttributesLine(line);
			}

			QLinkedList<SDPMediaTrackInfo> mediaTracks;

			for(const auto& mediaTrack : mediaTracksDictionary_.values())
				mediaTracks.append(mediaTrack);

			return mediaTracks;
		}

		///
		/// \details
		/// \param[in]	line
		void SDPParser::parseMediaLine(const QString& line) {
			auto tokens = line.split(' ', QString::SkipEmptyParts);

			if (tokens.size() < 4) {
				currentMediaTrack_ = mediaTracksDictionary_.end();
				return;
			}

			auto result = false;
			auto payloadType = tokens[3].toInt(&result);

			if (!result) {
				currentMediaTrack_ = mediaTracksDictionary_.end();
				return;
			}

			//auto codecInfo = createCodecInfo();
		}

		///
		/// \details
		/// \param[in]	line
		void SDPParser::parseAttributesLine(const QString& line) {
			auto equalsIndex = line.indexOf('=');
			if (equalsIndex == -1) return;

			auto colonIndex = line.indexOf(':', equalsIndex);
			if (colonIndex == -1) return;

			auto attributeLength = colonIndex - equalsIndex - 1;
			if (attributeLength <= 0 || colonIndex + 1 >= line.length()) return;

			auto attributeName =
				line.mid(equalsIndex + 1, attributeLength).trimmed().toUpper();

			auto attributeValue = line.mid(colonIndex + 1).trimmed();

			if (attributeName == "RTPMAP")
				parseRTPMAPAttribute(attributeValue);
			else if (attributeName == "CONTROL")
				parseCONTROLAttribute(attributeValue);
			else if (attributeName == "FMTP")
				parseFMTPAttribute(attributeValue);
		}

		/// Parses SDP RTPMAP attribute value.
		/// \param[in]	attributeValue	SDP attribute value.
		void parseRTPMAPAttribute(const QString& attributeValue);

		/// Parses SDP CONTROL attribute value.
		/// \param[in]	attributeValue	SDP attribute value.
		void parseCONTROLAttribute(const QString& attributeValue);

		/// Parses SDP FMTP attribute value.
		/// \param[in]	attributeValue	SDP attribute value.
		void parseFMTPAttribute(const QString& attributeValue);

		///
		/// \details
		/// \param[in]	codecName
		/// \param[in]	samplesFrequency
		/// \param[in]	channels
		/// \return
		QSharedPointer<AbstractCodecInfo> SDPParser::createCodecInfo(
			const QString& codecName,
			int samplesFrequency,
			int channels) const {

			if (codecName == "JPEG")
				return QSharedPointer<AbstractCodecInfo>(new MJPEGCodecInfo);

			return nullptr;
		}

		///
		/// \details
		/// \param[in]	payloadType
		/// \return
		int SDPParser::getSamplesFrequencyFromPayloadType(
			int payloadType) const noexcept {

			int samplesFrequency = 0;

			switch (payloadType) {
			case 0:
			case 2:
			case 3:
			case 4:
			case 5:
			case 7:
			case 8:
			case 9:
			case 12:
			case 15:
			case 18:
				samplesFrequency = 8000;
				break;
			case 6:
				samplesFrequency = 16000;
				break;
			case 10:
			case 11:
				samplesFrequency = 44100;
				break;
			case 16:
				samplesFrequency = 11025;
				break;
			case 17:
				samplesFrequency = 22050;
				break;
			case 14:
			case 25:
			case 26:
			case 28:
			case 31:
			case 32:
			case 33:
			case 34:
				samplesFrequency = 90000;
				break;
			default:
				samplesFrequency = 0;
				break;
			}

			return samplesFrequency;
		}
	}
}
