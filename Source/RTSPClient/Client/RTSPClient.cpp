/// \file RTSPClient.cpp
/// \brief Contains classes and functions definitions that provide Real Time
/// Streaming Protocol (RTSP) client implementation.
/// \bug No known bugs.

#include "RTSPClient.hpp"
#include "Protocols/RTSP.hpp"

#include <QUdpSocket>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Structure that provides private storage.
		/// \details Maintains private data.
		struct RTSPClient::RTSPClientPrivate final {

			/// Timer to send RTSP heartbeat requests.
			/// \details Timer to send heartbeat requests to resume RTP session.
			QBasicTimer timer_;

			/// Socket for receiving RTP data.
			/// \details Socket for receiving RTP data packets.
			QUdpSocket rtp_;

			/// Socket for receiving RTCP data.
			/// \details Socket for receiving RTCP service messages.
			QUdpSocket rtcp_;

			/// RTSP context.
			/// \details RTSP context for RTP session management.
			RTSP context_;
		};

		/// Default constructor.
		/// \details Initializes object fields.
		/// \param[in]	parent	Parent object.
		RTSPClient::RTSPClient(QObject* parent)
			: QObject(parent),
			  private_(new RTSPClientPrivate) {

		}

		/// Destructor.
		/// \details Cleans resources.
		RTSPClient::~RTSPClient() {
			close();
		}

		///
		/// \details Initializes the RTSP context and sends OPTIONS and
		/// DESCRIBE requests.
		/// \param[in]	url	RTSP connection URL.
		/// \retval true on success.
		/// \retval false on error.
		bool RTSPClient::open(const QUrl& url) {
			close();

			private_->context_.setUserAgent("RTSPClient");

			if (!url.isValid()										||
				!private_->context_.open(url.toEncoded())			||
				private_->context_.OPTIONS() != RTSPStatusCode::Ok	||
				private_->context_.DESCRIBE() != RTSPStatusCode::Ok) {
				close();
				return false;
			}

			return true;
		}

		///
		/// \details
		void RTSPClient::close() {
			reset();

			private_->context_.close();
		}

		/// Sets up the media stream.
		/// \details Sends SETUP request and set up RTP and RTCP sockets.
		/// \param[in]	path	Media stream path.
		/// \param[in]	ports	Ports for receiving RTP and RTCP data.
		/// \retval true on success.
		/// \retval false on error.
		bool RTSPClient::setup(const QUrl& path,
							   const QPair<quint16, quint16>& ports) {

			reset();

			if (!path.isValid()												||
				private_->context_.SETUP_UDP(path.toEncoded(), ports) !=
					RTSPStatusCode::Ok										||
				!private_->rtp_.bind(ports.first)							||
				!private_->rtcp_.bind(ports.second)) {
				reset();
				return false;
			}

			connect(
				&private_->rtp_,
				SIGNAL(readyRead()),
				SLOT(onRTPDatagram())
			);

			connect(
				&private_->rtcp_,
				SIGNAL(readyRead()),
				SLOT(onRTCPDatagram())
			);

			private_->timer_.start(30000, this);

			return true;
		}

		///
		/// \details Closes sockets and sends TEARDOWN request.
		/// \retval true on success.
		/// \retval false on error.
		bool RTSPClient::reset() {
			private_->timer_.stop();

			private_->rtp_.disconnect();
			private_->rtp_.close();

			private_->rtcp_.disconnect();
			private_->rtcp_.close();

			return private_->context_.TEARDOWN() == RTSPStatusCode::Ok;
		}

		/// Starts playback of the media stream.
		/// \details Sends PLAY request.
		/// \retval true on success.
		/// \retval false on error.
		bool RTSPClient::play() {
			return private_->context_.PLAY() == RTSPStatusCode::Ok;
		}

		/// Pauses playback of the media stream.
		/// \details Sends PAUSE request
		/// \retval true on success.
		/// \retval false on error.
		bool RTSPClient::pause() {
			return private_->context_.PAUSE() == RTSPStatusCode::Ok;
		}

		///
		/// \details Checks if the RTSP context is open.
		/// \retval
		/// \retval
		bool RTSPClient::isOpen() const {
			return private_->context_.isOpen();
		}

		/// Handles timer events.
		/// \details Performs OPTIONS heartbeat request.
		/// \param[in]	event	Timer event.
		void RTSPClient::timerEvent(QTimerEvent* event) {
			if (event && event->timerId() == private_->timer_.timerId()) {
				private_->context_.OPTIONS();
			}
			else QObject::timerEvent(event);
		}

		/// Performs an action when receiving RTP data.
		/// \details Performs RTP packet processing and frame assembly.
		void RTSPClient::onRTPDatagram() {
			while (private_->rtp_.hasPendingDatagrams()) {
				QByteArray data(
					private_->rtp_.pendingDatagramSize(),
					Qt::Uninitialized
				);

				if (private_->rtp_.readDatagram(data.data(), data.size()) !=
					data.size()) continue;

				emit onData(data);
			}
		}

		/// Performs an action when receiving RTCP data.
		/// \details Performs processing of RTCP packets.
		void RTSPClient::onRTCPDatagram() {

		}
	}
}
