/// \file AbstractRTSPClient.hpp
/// \brief Contains classes and functions declarations that provide Real Time
/// Streaming Protocol (RTSP) abstract client interface.
/// \bug No known bugs.

#ifndef ABSTRACTRTSPCLIENT_HPP
#define ABSTRACTRTSPCLIENT_HPP

#include <QtCore>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Enumeration that defines RTSP status codes
		enum class RTSPStatusCode {
			Error								=	0	,
			Continue							=	100	,
			Ok									=	200	,
			Created								=	201	,
			LowOnStorageSpace					=	250	,
			MultipleChoices						=	300	,
			MovedPermanently					=	301	,
			Found								=	302	,
			SeeOther							=	303	,
			NotModified							=	304	,
			UseProxy							=	305	,
			BadRequest							=	400	,
			Unauthorized						=	401	,
			PaymentRequired						=	402	,
			Forbidden							=	403	,
			NotFound							=	404	,
			MethodNotAllowed					=	405	,
			NotAcceptable						=	406	,
			ProxyAuthenticationRequired			=	407	,
			RequestTimeOut						=	408	,
			Gone								=	410	,
			LengthRequired						=	411	,
			PreconditionFailed					=	412	,
			RequestMessageBodyTooLarge			=	413	,
			RequestUriTooLarge					=	414	,
			UnsupportedMediaType				=	415	,
			ParameterNotUnderstood				=	451	,
			Reserved							=	452	,
			NotEnoughBandwidth					=	453	,
			SessionNotFound						=	454	,
			MethodNotValidInThisState			=	455	,
			HeaderFieldNotValidForResource		=	456	,
			InvalidRange						=	457	,
			ParameterIsReadOnly					=	458	,
			AggregateOpperationNotAllowed		=	459	,
			OnlyAggregateOpperationAllowed		=	460	,
			UnsupportedTransport				=	461	,
			DestinationUnreachable				=	462	,
			DestinationProhibited				=	463	,
			DataTransportNotReadyYet			=	464	,
			NotificationReasonUnknown			=	465	,
			KeyManagementError					=	466	,
			ConnectionAuthorizationRequired		=	470	,
			ConnectionCredentialsNotAcception	=	471	,
			FaulireToEstablishSecureConnection	=	472	,
			InternalServerError					=	500	,
			NotImplemented						=	501	,
			BadGateway							=	502	,
			ServiceUnavailable					=	503	,
			GatewayTimeOut						=	504	,
			RtspVersionNotSupported				=	505	,
			OptionNotSupported					=	551
		};

		///
		class AbstractRTSPClient : public QObject {

			Q_OBJECT

		public:

			/// Destructor.
			~AbstractRTSPClient() override = 0;

		public:


		};
	}
}

#endif
