/// \file SDPParser.hpp
/// \brief Contains classes and functions declarations that provide SDP parser
/// implementation.
/// \bug No known bugs.

#ifndef SDPPARSER_HPP
#define SDPPARSER_HPP

#include "AbstractSDPParser.hpp"

#include <QHash>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that provides SDP parser implementation.
		class SDPParser final : public AbstractSDPParser {
		public:

			/// Default constructor.
			explicit SDPParser() noexcept;

			/// Destructor.
			~SDPParser() noexcept override;

		public:

			/// Parses SDP document to find media track information.
			/// \param[in]	sdpData	SDP document data.
			/// \return List of parsed SDP media tracks.
			QLinkedList<SDPMediaTrackInfo> parse(
				const QByteArray& sdpData) override;

		private:

			/// Parses SDP media line.
			/// \param[in]	line	SDP media line.
			void parseMediaLine(const QString& line);

			/// Parses SDP attribute line.
			/// \param[in]	line	SDP attribute line.
			void parseAttributesLine(const QString& line);

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
			/// \param[in]	codecName
			/// \param[in]	samplesFrequency
			/// \param[in]	channels
			/// \return
			QSharedPointer<AbstractCodecInfo> createCodecInfo(
				const QString& codecName,
				int samplesFrequency,
				int channels) const;

			///
			/// \param[in]	payloadType
			/// \return
			int getSamplesFrequencyFromPayloadType(
				int payloadType) const noexcept;

		private:

			/// Dictionary that stores payload format numbers with related
			/// media track information.
			QHash<int, SDPMediaTrackInfo> mediaTracksDictionary_;

			/// Currently processed media track.
			decltype(mediaTracksDictionary_)::iterator currentMediaTrack_;
		};
	}
}

#endif
