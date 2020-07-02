/// \file G711ACodecInfo.cpp
/// \brief Contains classes and functions definitions that provide G.711 A-law
/// audio codec information interface.
/// \bug No known bugs.

#include "G711ACodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		G711ACodecInfo::G711ACodecInfo() noexcept
			: AbstractG711CodecInfo(CodecFormat::G711A) {
		}

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	samplingRate	Sampling rate.
		/// \param[in]	channelsNumber	Number of channels.
		G711ACodecInfo::G711ACodecInfo(int samplingRate,
									   int channelsNumber) noexcept
			: AbstractG711CodecInfo(CodecFormat::G711A,
									samplingRate,
									channelsNumber) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		G711ACodecInfo::~G711ACodecInfo() noexcept = default;
	}
}
