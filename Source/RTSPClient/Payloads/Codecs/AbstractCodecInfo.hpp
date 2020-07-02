/// \file AbstractCodecInfo.hpp
/// \brief Contains classes and functions declarations that provide abstract
/// codec information interface.
/// \bug No known bugs.

#ifndef ABSTRACTCODECINFO_HPP
#define ABSTRACTCODECINFO_HPP

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Enumeration that defines supported codec types.
		enum class CodecType {
			Audio	,	///< Audio codecs.
			Video	,	///< Video codecs.
		};

		/// Enumeration that defines supported codec formats.
		enum class CodecFormat {
			AAC		,	///< AAC audio codec.
			G711A	,	///< G.711 μ-law audio codec.
			G711U	,	///< G.711 A-law audio codec.
			G726	,	///< G.726 audio codec.
			PCM		,	///< PCM audio codec.
			H264	,	///< H.264 video codec.
			MJPEG	,	///< Motion JPEG video codec.
		};

		/// Class that defines abstract codec information interface.
		class AbstractCodecInfo {
		public:

			/// Constructor.
			/// \param[in]	codecType	Codec type.
			/// \param[in]	codecFormat	Codec format.
			explicit AbstractCodecInfo(CodecType codecType,
									   CodecFormat codecFormat) noexcept;

			/// Destructor.
			virtual ~AbstractCodecInfo() = 0;

		public:

			/// Returns codec type.
			/// \return Codec type.
			CodecType getCodecType() const noexcept;

			/// Returns codec format.
			/// \return Codec format.
			CodecFormat getCodecFormat() const noexcept;

		private:

			/// Codec type.
			const CodecType codecType_;

			/// Codec format.
			const CodecFormat codecFormat_;
		};
	}
}

#endif
