/// \file G711UCodecInfo.cpp
/// \brief Contains classes and functions definitions that provide G.711 μ-law
/// audio codec information interface.
/// \bug No known bugs.

#include "G711UCodecInfo.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Constructor.
		/// \details Initializes object fields.
		G711UCodecInfo::G711UCodecInfo() noexcept
			: AbstractG711CodecInfo(CodecFormat::G711U) {
		}

		/// Constructor.
		/// \details Initializes object fields.
		/// \param[in]	samplingRate	Sampling rate.
		/// \param[in]	channelsNumber	Number of channels.
		G711UCodecInfo::G711UCodecInfo(int samplingRate,
									   int channelsNumber) noexcept
			: AbstractG711CodecInfo(CodecFormat::G711U,
									samplingRate,
									channelsNumber) {
		}

		/// Destructor.
		/// \details Defaulted default destructor.
		G711UCodecInfo::~G711UCodecInfo() noexcept = default;
	}
}
