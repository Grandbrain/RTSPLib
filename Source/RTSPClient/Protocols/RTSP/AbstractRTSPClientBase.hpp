/// \file AbstractRTSPClientBase.hpp
/// \brief Contains classes and functions declarations that provide Real Time
/// Streaming Protocol (RTSP) abstract base client implementation.
/// \bug No known bugs.

#ifndef ABSTRACTRTSPCLIENTBASE_HPP
#define ABSTRACTRTSPCLIENTBASE_HPP

#include "AbstractRTSPClient.hpp"

#include <curl.h>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that provides Real Time Streaming Protocol (RTSP) base client
		/// implementation.
		class RTSPClientBase {
		private:

			///
			using callback_t = size_t(*)(char*, size_t, size_t, void*);

		public:

			/// Default constructor.
			explicit RTSPClientBase();

			/// Destructor.
			virtual ~RTSPClientBase();

			/// Move constructor.
			/// \param[in]	object	Object to move.
			RTSPClientBase(RTSPClientBase&& object) = default;

			/// Move assignment operator,
			/// \param[in]	object	Object to move.
			/// \return This object.
			RTSPClientBase& operator=(RTSPClientBase&& object) = default;

		public:

			///
			/// \param[in]	url	RTSP connection URL.
			/// \retval true on success.
			/// \retval false on error.
			bool open(const QByteArray& url);

			///
			void close();

			///
			/// \retval
			/// \retval
			bool isOpen() const;

			///
			/// \return
			QByteArray getSDP() const;

			///
			/// \return
			QByteArray getUrl() const;

			///
			/// \return
			QByteArray getSession() const;

			///
			/// \return
			QByteArray getUserAgent() const;

			///
			/// \param[in]	agent
			void setUserAgent(const QByteArray& userAgent);

			///
			/// \return
			QPair<qint64, qint64> getTimeouts() const;

			///
			/// \param[in]	timeouts
			void setTimeouts(const QPair<qint64, qint64>& timeouts);

			///
			/// \return
			QPair<QByteArray, QByteArray> getCredentials() const;

			///
			/// \param[in]	credentials
			void setCredentials(
				const QPair<QByteArray, QByteArray>& credentials
			);

			/// Sends OPTIONS request.
			/// \return RTSP status code.
			RTSPStatusCode OPTIONS();

			/// Sends DESCRIBE request.
			/// \return RTSP status code.
			RTSPStatusCode DESCRIBE();

			/// Sends SETUP request.
			/// \param[in]	path		Media track path.
			/// \param[in]	channels	Channels for RTP and RTCP data.
			/// \return RTSP status code.
			RTSPStatusCode SETUP(const QByteArray& path,
								 const QPair<quint16, quint16>& channels);

			/// Sends PLAY request.
			/// \return RTSP status code.
			RTSPStatusCode PLAY();

			/// Sends PAUSE request.
			/// \return RTSP status code.
			RTSPStatusCode PAUSE();

			/// Sends GET_PARAMETER request.
			/// \return RTSP status code.
			RTSPStatusCode GET_PARAMETER();

			/// Sends TEARDOWN request.
			/// \return RTSP status code.
			RTSPStatusCode TEARDOWN();

			///
			/// \return
			RTSPStatusCode RECEIVE();

		private:

			///
			/// \param[in]	url
			/// \retval true on success.
			/// \retval false on error.
			bool contextOpen(const QByteArray& url);

			///
			void contextClose();

			///
			/// \retval
			/// \retval
			bool contextIsOpen() const;

			///
			/// \param[in]	request
			/// \retval
			/// \retval
			bool contextIsSupported(qint64 request) const;

			///
			/// \param[in]	option
			/// \param[in]	callback
			/// \param[in]	data
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetCallback(CURLoption option,
									callback_t callback,
									void* data);

			///
			/// \param[in]	stream
			/// \param[in]	transport
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetUrl(const QByteArray& track = { },
							   const QByteArray& transport = { });

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetHeader();

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetSession();

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetTimeouts();

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetCredentials();

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextSetMiscellaneous();

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextResetConnection();

			///
			/// \retval true on success.
			/// \retval false on error.
			bool contextResetSequence();

			///
			void contextReset();

			///
			/// \param[in]	request
			/// \retval true on success.
			/// \retval false on error.
			bool contextPerform(qint64 request);

		private:

			///
			/// \param[in]	url
			/// \return
			static QByteArray trimUrl(const QByteArray& url);

			///
			/// \param[in]	status
			/// \return
			static RTSPStatusCode validateStatus(RTSPStatusCode status);

			/// Performs an action when receiving RTSP header data.
			/// \param[in]	data	Data pointer.
			/// \param[in]	n		Number of buffers.
			/// \param[in]	size	Data size.
			/// \param[in]	user	User-defined data.
			/// \return Actual read size.
			static size_t callbackHeaderAll(char* data,
											size_t n,
											size_t size,
											void* user);

			/// Performs an action when receiving RTSP OPTIONS header data.
			/// \param[in]	data	Data pointer.
			/// \param[in]	n		Number of buffers.
			/// \param[in]	size	Data size.
			/// \param[in]	user	User-defined data.
			/// \return Actual read size.
			static size_t callbackHeaderOPTIONS(char* data,
												size_t n,
												size_t size,
												void* user);

			/// Performs an action when receiving SDP data.
			/// \param[in]	data	Data pointer.
			/// \param[in]	n		Number of buffers.
			/// \param[in]	size	Data size.
			/// \param[in]	user	User-defined data.
			/// \return Actual read size.
			static size_t callbackBodyDESCRIBE(char* data,
											   size_t n,
											   size_t size,
											   void* user);

			/// Performs an action when receiving RTSP interleaved data.
			/// \param[in]	data	Data pointer.
			/// \param[in]	n		Number of buffers.
			/// \param[in]	size	Data size.
			/// \param[in]	user	User-defined data.
			/// \return Actual read size.
			static size_t callbackDataInterleaved(char* data,
												  size_t n,
												  size_t size,
												  void* user);

		private:

			///
			struct RTSPClientBasePrivate final {

				/// Local libcurl context.
				CURL* localContext_ { nullptr };

				/// RTSP status code.
				RTSPStatusCode statusCode_ { RTSPStatusCode::Error };

				/// RTSP connection URL.
				QByteArray connectionUrl_ { };

				/// RTSP user agent.
				QByteArray userAgent_ { };

				/// Current RTSP session.
				QByteArray currentSession_ { };

				/// SDP data.
				QByteArray sdpData_ { };

				/// Supported RTSP requests.
				QVector<qint64> supportedRequests_ { };

				/// Operation timeouts.
				QPair<qint64, qint64> operationTimeouts_ { 0, 0 };

				/// User credentials.
				QPair<QByteArray, QByteArray> userCredentials_ { };

			} private_;
		};
	}
}

#endif
