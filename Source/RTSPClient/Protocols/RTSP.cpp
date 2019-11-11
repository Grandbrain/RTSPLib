/// \file RTSP.cpp
/// \brief Contains classes and functions definitions that provide Real Time
/// Streaming Protocol (RTSP) implementation.
/// \bug No known bugs.

#include "RTSP.hpp"

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Global libcurl context.
		/// \details Maintains global libcurl context.
		static class RTSPGlobalContext final {
		public:

			/// Default constructor.
			/// \details Initializes global libcurl context.
			RTSPGlobalContext() :
				initialized_(curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK) { }

			/// Destructor.
			/// \details Destroys global libcurl context.
			~RTSPGlobalContext() { curl_global_cleanup(); }

		public:

			///
			/// \details
			/// \retval
			/// \retval
			bool isInitialized() const { return initialized_; }

		private:

			///
			/// \details
			bool initialized_ = false;

		} globalContext_;

		/// Default constructor.
		/// \details Initializes object fields.
		RTSP::RTSP() : private_ { } {

		}

		/// Destructor.
		/// \details Cleans resources.
		RTSP::~RTSP() {
			close();
		}

		///
		/// \details
		/// \param[in]	url	RTSP connection URL.
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::open(const QByteArray& url) {
			return isOpen() || contextOpen(url);
		}

		///
		/// \details
		void RTSP::close() {
			contextClose();
		}

		///
		/// \details
		/// \retval
		/// \retval
		bool RTSP::isOpen() const {
			return contextIsOpen();
		}

		///
		/// \details
		/// \return
		QByteArray RTSP::getSDP() const {
			return private_.sdpData_;
		}

		///
		/// \details
		/// \return
		QByteArray RTSP::getUrl() const {
			return private_.connectionUrl_;
		}

		///
		/// \details
		/// \return
		QByteArray RTSP::getSession() const {
			return private_.currentSession_;
		}

		///
		/// \details
		/// \return
		QByteArray RTSP::getUserAgent() const {
			return private_.userAgent_;
		}

		///
		/// \details
		/// \param[in]	agent
		/// \retval true on success.
		/// \retval false on error.
		void RTSP::setUserAgent(const QByteArray& userAgent) {
			private_.userAgent_ = userAgent;
		}

		///
		/// \details
		/// \return
		QPair<qint64, qint64> RTSP::getTimeouts() const {
			return private_.operationTimeouts_;
		}

		///
		/// \details
		/// \param[in]	timeouts
		void RTSP::setTimeouts(const QPair<qint64, qint64>& timeouts) {
			private_.operationTimeouts_ = timeouts;
		}

		///
		/// \details
		/// \return
		QPair<QByteArray, QByteArray> RTSP::getCredentials() const {
			return private_.userCredentials_;
		}

		///
		/// \details
		/// \param[in]	credentials
		void RTSP::setCredentials(
			const QPair<QByteArray, QByteArray>& credentials) {
			private_.userCredentials_ = credentials;
		}

		/// Sends OPTIONS request.
		/// \details Sends OPTIONS request through the local context.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::OPTIONS() {
			auto request { CURL_RTSPREQ_OPTIONS };

			if (!contextIsOpen() ||
				!contextIsSupported(request))
				return RTSPStatusCode::Error;

			if (!contextSetUrl()			||
				!contextSetHeader()			||
				!contextSetSession()		||
				!contextSetTimeouts()		||
				!contextSetCredentials()	||
				!contextSetMiscellaneous()	||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
								   private_.supportedRequests_.isEmpty()
								   ? callbackHeaderOPTIONS
								   : callbackHeaderAll,
								   &private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_ = RTSPStatusCode::Error;

			contextReset();

			return status;
		}

		/// Sends DESCRIBE request.
		/// \details Sends DESCRIBE request through the local context.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::DESCRIBE() {
			auto request { CURL_RTSPREQ_DESCRIBE };

			if (!contextIsOpen() ||
				!contextIsSupported(request))
				return RTSPStatusCode::Error;

			if (!contextSetUrl()			||
				!contextSetHeader()			||
				!contextSetSession()		||
				!contextSetTimeouts()		||
				!contextSetCredentials()	||
				!contextSetMiscellaneous()	||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
									callbackHeaderAll,
									&private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			if (private_.sdpData_.isEmpty()) {
				if (!contextSetCallback(CURLOPT_WRITEFUNCTION,
										callbackBodyDESCRIBE,
										&private_)) {
					contextReset();
					return RTSPStatusCode::Error;
				}
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_ = RTSPStatusCode::Error;

			contextReset();

			return status;
		}

		/// Sends SETUP request.
		/// \details Sends SETUP request through the local context.
		/// \param[in]	path	Media track path.
		/// \param[in]	ports	Client ports that receive RTP and RTCP data.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::SETUP_UDP(const QByteArray& path,
									   const QPair<quint16, quint16>& ports) {

			auto request { CURL_RTSPREQ_SETUP };

			if (!contextIsOpen() ||
				!contextIsSupported(request))
				return RTSPStatusCode::Error;

			auto track = private_.connectionUrl_ + '/' + trimUrl(path);

			auto transport =
				QByteArray("RTP/AVP/UDP;unicast;client_port=") +
				QByteArray::number(ports.first) +
				QByteArray("-") +
				QByteArray::number(ports.second);

			if (!contextSetUrl(track, transport)	||
				!contextSetHeader()					||
				!contextSetSession()				||
				!contextSetTimeouts()				||
				!contextSetCredentials()			||
				!contextSetMiscellaneous()			||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
									callbackHeaderAll,
									&private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_ = RTSPStatusCode::Error;

			contextReset();

			return status;
		}

		/// Sends PLAY request.
		/// \details Sends PLAY request through the local context.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::PLAY() {
			auto request { CURL_RTSPREQ_PLAY };

			if (!contextIsOpen()					||
				!contextIsSupported(request)		||
				private_.currentSession_.isEmpty())
				return RTSPStatusCode::Error;

			if (!contextSetUrl()			||
				!contextSetHeader()			||
				!contextSetSession()		||
				!contextSetTimeouts()		||
				!contextSetCredentials()	||
				!contextSetMiscellaneous()	||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
									callbackHeaderAll,
									&private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_ = RTSPStatusCode::Error;

			contextReset();

			return status;
		}

		/// Sends PAUSE request.
		/// \details Sends PAUSE request through the local context.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::PAUSE() {
			auto request { CURL_RTSPREQ_PAUSE };

			if (!contextIsOpen()					||
				!contextIsSupported(request)		||
				private_.currentSession_.isEmpty())
				return RTSPStatusCode::Error;

			if (!contextSetUrl()			||
				!contextSetHeader()			||
				!contextSetSession()		||
				!contextSetTimeouts()		||
				!contextSetCredentials()	||
				!contextSetMiscellaneous()	||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
									callbackHeaderAll,
									&private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_ = RTSPStatusCode::Error;

			contextReset();

			return status;
		}

		/// Sends GET_PARAMETER request.
		/// \details Sends GET_PARAMETER request through the local context.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::GET_PARAMETER() {
			auto request { CURL_RTSPREQ_GET_PARAMETER };

			if (!contextIsOpen()					||
				!contextIsSupported(request)		||
				private_.currentSession_.isEmpty())
				return RTSPStatusCode::Error;

			if (!contextSetUrl()			||
				!contextSetHeader()			||
				!contextSetSession()		||
				!contextSetTimeouts()		||
				!contextSetCredentials()	||
				!contextSetMiscellaneous()	||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
									callbackHeaderAll,
									&private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_ = RTSPStatusCode::Error;

			contextReset();

			return status;
		}

		/// Sends TEARDOWN request.
		/// \details Sends TEARDOWN request through the local context.
		/// \return RTSP status code.
		RTSPStatusCode RTSP::TEARDOWN() {
			auto request { CURL_RTSPREQ_TEARDOWN };

			if (!contextIsOpen()					||
				!contextIsSupported(request)		||
				private_.currentSession_.isEmpty())
				return RTSPStatusCode::Error;

			if (!contextSetUrl()			||
				!contextSetHeader()			||
				!contextSetSession()		||
				!contextSetTimeouts()		||
				!contextSetCredentials()	||
				!contextSetMiscellaneous()	||
				!contextResetConnection()	||
				!contextSetCallback(CURLOPT_HEADERFUNCTION,
									callbackHeaderAll,
									&private_)) {
				contextReset();
				return RTSPStatusCode::Error;
			}

			auto status = contextPerform(request)
						  ? private_.statusCode_
						  : RTSPStatusCode::Error;

			private_.statusCode_		= RTSPStatusCode::Error;
			private_.currentSession_	= { };

			contextResetSequence();
			contextReset();

			return status;
		}

		///
		/// \details
		/// \param[in]	url
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextOpen(const QByteArray& url) {
			if (!globalContext_.isInitialized() || url.isEmpty())
				return false;

			private_.localContext_ = curl_easy_init();
			if (!private_.localContext_) return false;

			private_.connectionUrl_ = trimUrl(url);

			return true;
		}

		///
		/// \details
		void RTSP::contextClose() {
			private_.statusCode_		= RTSPStatusCode::Error;
			private_.connectionUrl_		= { };
			private_.userAgent_			= { };
			private_.currentSession_	= { };
			private_.sdpData_			= { };
			private_.supportedRequests_	= { };
			private_.operationTimeouts_ = { 0, 0 };
			private_.userCredentials_	= { };

			if (private_.localContext_) {
				curl_easy_cleanup(private_.localContext_);
				private_.localContext_ = nullptr;
			}
		}

		///
		/// \details
		/// \retval
		/// \retval
		bool RTSP::contextIsOpen() const {
			return private_.localContext_ &&
				   !private_.connectionUrl_.isEmpty();
		}

		///
		/// \details
		/// \param[in]	request
		/// \retval
		/// \retval
		bool RTSP::contextIsSupported(qint64 request) const {
			return request == CURL_RTSPREQ_OPTIONS ||
				   private_.supportedRequests_.contains(request);
		}

		///
		/// \details
		/// \param[in]	option
		/// \param[in]	callback
		/// \param[in]	data
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetCallback(CURLoption option,
									  callback_t callback,
									  void* data) {

			CURLoption dataOption;

			switch (option) {
			case CURLOPT_HEADERFUNCTION:
				dataOption = CURLOPT_HEADERDATA;
				break;
			case CURLOPT_WRITEFUNCTION:
				dataOption = CURLOPT_WRITEDATA;
				break;
			default: return false;
			}

			return curl_easy_setopt(private_.localContext_,
									option,
									callback) == CURLE_OK &&

				   curl_easy_setopt(private_.localContext_,
									dataOption,
									data) == CURLE_OK;
		}

		///
		/// \details
		/// \param[in]	stream
		/// \param[in]	transport
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetUrl(const QByteArray& track,
								 const QByteArray& transport) {

			return curl_easy_setopt(private_.localContext_,
									CURLOPT_URL,
									private_.connectionUrl_
										.constData()) == CURLE_OK &&

				   curl_easy_setopt(private_.localContext_,
									CURLOPT_RTSP_STREAM_URI,
									track.isEmpty()
									? private_.connectionUrl_.constData()
									: track.constData()) == CURLE_OK &&

				   (transport.isEmpty()
					? true
					: curl_easy_setopt(private_.localContext_,
									   CURLOPT_RTSP_TRANSPORT,
									   transport.constData()) == CURLE_OK);
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetHeader() {
			return private_.userAgent_.isEmpty() ||
				   curl_easy_setopt(private_.localContext_,
									CURLOPT_USERAGENT,
									private_.userAgent_
										.constData()) == CURLE_OK;
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetSession() {
			return private_.currentSession_.isEmpty() ||
				   curl_easy_setopt(private_.localContext_,
									CURLOPT_RTSP_SESSION_ID,
									private_.currentSession_
										.constData()) == CURLE_OK;
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetTimeouts() {
			return curl_easy_setopt(private_.localContext_,
									CURLOPT_CONNECTTIMEOUT_MS,
									private_.operationTimeouts_.first >= 0
									? private_.operationTimeouts_.first
									: 0) == CURLE_OK						&&

				   curl_easy_setopt(private_.localContext_,
									CURLOPT_TIMEOUT_MS,
									private_.operationTimeouts_.second >= 0
									? private_.operationTimeouts_.second
									: 0) == CURLE_OK;
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetCredentials() {
			return (private_.userCredentials_.second.isEmpty())				||

				   (!private_.userCredentials_.first.isEmpty()			&&

					curl_easy_setopt(private_.localContext_,
									 CURLOPT_HTTPAUTH,
									 CURLAUTH_ANY) == CURLE_OK		&&

					curl_easy_setopt(private_.localContext_,
									 CURLOPT_USERNAME,
									 private_.userCredentials_.first
										.constData()) == CURLE_OK	&&

					curl_easy_setopt(private_.localContext_,
									 CURLOPT_PASSWORD,
									 private_.userCredentials_.second
										.constData()) == CURLE_OK);
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextSetMiscellaneous() {
#ifdef QT_DEBUG

			curl_easy_setopt(private_.localContext_,
							 CURLOPT_VERBOSE,
							 1L);

#endif

			return curl_easy_setopt(private_.localContext_,
									CURLOPT_NOSIGNAL,
									1L) == CURLE_OK;
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextResetConnection() {
			return curl_easy_setopt(private_.localContext_,
									CURLOPT_FORBID_REUSE,
									1L) == CURLE_OK;
		}

		///
		/// \details
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextResetSequence() {
			return curl_easy_setopt(private_.localContext_,
									CURLOPT_RTSP_CLIENT_CSEQ,
									1L) == CURLE_OK;
		}

		///
		/// \details
		void RTSP::contextReset() {
			curl_easy_reset(private_.localContext_);
		}

		///
		/// \details
		/// \param[in]	request
		/// \retval true on success.
		/// \retval false on error.
		bool RTSP::contextPerform(qint64 request) {
			if (curl_easy_setopt(private_.localContext_,
								 CURLOPT_RTSP_REQUEST,
								 request) != CURLE_OK	||

				curl_easy_perform(private_.localContext_) != CURLE_OK)
				return false;

			if (private_.currentSession_.isEmpty()) {
				char* session = nullptr;

				curl_easy_getinfo(private_.localContext_,
								  CURLINFO_RTSP_SESSION_ID,
								  &session);

				private_.currentSession_ = QByteArray(session);
			}

			return true;
		}

		///
		/// \details
		/// \param[in]	url
		/// \return
		QByteArray RTSP::trimUrl(const QByteArray& url) {
			int begin = 0, end = 0;

			for (auto it = url.cbegin(); it != url.cend(); ++it) {
				if (*it == '/') ++begin;
				else break;
			}

			for (auto it = url.crbegin(); it != url.crend(); ++it) {
				if (*it == '/') ++end;
				else break;
			}

			return url.mid(begin, url.size() - begin - end);
		}

		///
		/// \details
		/// \param[in]	code
		/// \return
		RTSPStatusCode RTSP::validateStatus(RTSPStatusCode statusCode) {
			switch (statusCode) {
			case RTSPStatusCode::Error:
			case RTSPStatusCode::Continue:
			case RTSPStatusCode::Ok:
			case RTSPStatusCode::Created:
			case RTSPStatusCode::LowOnStorageSpace:
			case RTSPStatusCode::MultipleChoices:
			case RTSPStatusCode::MovedPermanently:
			case RTSPStatusCode::Found:
			case RTSPStatusCode::SeeOther:
			case RTSPStatusCode::NotModified:
			case RTSPStatusCode::UseProxy:
			case RTSPStatusCode::BadRequest:
			case RTSPStatusCode::Unauthorized:
			case RTSPStatusCode::PaymentRequired:
			case RTSPStatusCode::Forbidden:
			case RTSPStatusCode::NotFound:
			case RTSPStatusCode::MethodNotAllowed:
			case RTSPStatusCode::NotAcceptable:
			case RTSPStatusCode::ProxyAuthenticationRequired:
			case RTSPStatusCode::RequestTimeOut:
			case RTSPStatusCode::Gone:
			case RTSPStatusCode::LengthRequired:
			case RTSPStatusCode::PreconditionFailed:
			case RTSPStatusCode::RequestMessageBodyTooLarge:
			case RTSPStatusCode::RequestUriTooLarge:
			case RTSPStatusCode::UnsupportedMediaType:
			case RTSPStatusCode::ParameterNotUnderstood:
			case RTSPStatusCode::Reserved:
			case RTSPStatusCode::NotEnoughBandwidth:
			case RTSPStatusCode::SessionNotFound:
			case RTSPStatusCode::MethodNotValidInThisState:
			case RTSPStatusCode::HeaderFieldNotValidForResource:
			case RTSPStatusCode::InvalidRange:
			case RTSPStatusCode::ParameterIsReadOnly:
			case RTSPStatusCode::AggregateOpperationNotAllowed:
			case RTSPStatusCode::OnlyAggregateOpperationAllowed:
			case RTSPStatusCode::UnsupportedTransport:
			case RTSPStatusCode::DestinationUnreachable:
			case RTSPStatusCode::DestinationProhibited:
			case RTSPStatusCode::DataTransportNotReadyYet:
			case RTSPStatusCode::NotificationReasonUnknown:
			case RTSPStatusCode::KeyManagementError:
			case RTSPStatusCode::ConnectionAuthorizationRequired:
			case RTSPStatusCode::ConnectionCredentialsNotAcception:
			case RTSPStatusCode::FaulireToEstablishSecureConnection:
			case RTSPStatusCode::InternalServerError:
			case RTSPStatusCode::NotImplemented:
			case RTSPStatusCode::BadGateway:
			case RTSPStatusCode::ServiceUnavailable:
			case RTSPStatusCode::GatewayTimeOut:
			case RTSPStatusCode::RtspVersionNotSupported:
			case RTSPStatusCode::OptionNotSupported:
				return statusCode;
			default:
				return RTSPStatusCode::Error;
			}
		}

		/// Performs an action when receiving RTSP header data.
		/// \details
		/// \param[in]	data	Data pointer.
		/// \param[in]	n		Number of buffers.
		/// \param[in]	size	Data size.
		/// \param[in]	user	User-defined data.
		/// \return Actual read size.
		size_t RTSP::callbackHeaderAll(char* data,
									   size_t n,
									   size_t size,
									   void* user) {

			auto read = n * size;
			auto object = static_cast<RTSPPrivate*>(user);

			if (data && (read > 0) && object) {
				auto header = QByteArray::fromRawData(data, read);
				auto lines = header.split('\n');

				auto line = std::find_if(lines.cbegin(),
										 lines.cend(),
										 [&](const QByteArray& a) {
					return a.startsWith("RTSP/");
				});

				if (line != lines.end()) {
					auto tokens = line->split(' ');
					auto token = tokens.size() >= 3 ? tokens[1] : "";

					object->statusCode_ = validateStatus(
						static_cast<RTSPStatusCode>(token.toInt()));
				}
			}

			return read;
		}

		/// Performs an action when receiving RTSP OPTIONS header data.
		/// \details
		/// \param[in]	data	Data pointer.
		/// \param[in]	n		Number of buffers.
		/// \param[in]	size	Data size.
		/// \param[in]	user	User-defined data.
		/// \return Actual read size.
		size_t RTSP::callbackHeaderOPTIONS(char* data,
										   size_t n,
										   size_t size,
										   void* user) {

			auto read = n * size;
			auto object = static_cast<RTSPPrivate*>(user);

			if (data && (read > 0) && object) {
				auto header = QByteArray::fromRawData(data, read);
				auto token = QByteArray("Public:");
				auto lines = header.split('\n');

				auto line = std::find_if(lines.cbegin(),
										 lines.cend(),
										 [&](const QByteArray& a) {
					return a.startsWith(token);
				});

				if (line != lines.end()) {
					auto options = line->mid(token.size()).split(',');
					object->supportedRequests_.clear();

					static const QMap<QString, qint64> map {
						{ "OPTIONS",		CURL_RTSPREQ_OPTIONS		},
						{ "DESCRIBE",		CURL_RTSPREQ_DESCRIBE		},
						{ "ANNOUNCE",		CURL_RTSPREQ_ANNOUNCE		},
						{ "SETUP",			CURL_RTSPREQ_SETUP			},
						{ "PLAY",			CURL_RTSPREQ_PLAY			},
						{ "PAUSE",			CURL_RTSPREQ_PAUSE			},
						{ "TEARDOWN",		CURL_RTSPREQ_TEARDOWN		},
						{ "GET_PARAMETER",	CURL_RTSPREQ_GET_PARAMETER	},
						{ "SET_PARAMETER",	CURL_RTSPREQ_SET_PARAMETER	},
						{ "RECORD",			CURL_RTSPREQ_RECORD			}
					};

					for (const auto& option : options) {
						auto iterator = map.find(option.trimmed());
						if (iterator != map.cend())
							object->supportedRequests_.append(iterator.value());
					}
				}
			}

			return callbackHeaderAll(data, n, size, user);
		}

		/// Performs an action when receiving SDP data.
		/// \details
		/// \param[in]	data	Data pointer.
		/// \param[in]	n		Number of buffers.
		/// \param[in]	size	Data size.
		/// \param[in]	user	User-defined data.
		/// \return Actual read size.
		size_t RTSP::callbackBodyDESCRIBE(char* data,
										  size_t n,
										  size_t size,
										  void* user) {

			auto read = n * size;
			auto object = static_cast<RTSPPrivate*>(user);

			if (data && (read > 0) && object) {
				object->sdpData_ = QByteArray(data, read);
			}

			return read;
		}
	}
}
