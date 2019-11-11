/// \file VideoDecoder.cpp
/// \brief Contains classes and functions definitions that provide H.264
/// \brief decoder implementation.
/// \bug No known bugs.

#include "H.264Decoder.hpp"

extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libavdevice/avdevice.h>
	#include <libswscale/swscale.h>
}

///
/// \details
class VideoDecoder::VideoDecoderPrivate final {
public:

	///
	/// \details
	VideoDecoderPrivate()
		: context_(nullptr) {

	}

	///
	/// \details
	virtual ~VideoDecoderPrivate() {
		destroy();
	}

public:

	///
	/// \details
	/// \retval
	/// \retval
	bool initialize() {
		av_register_all();

		auto codec = avcodec_find_decoder(AV_CODEC_ID_H264);
		if (!codec) return false;

		context_ = avcodec_alloc_context3(codec);
		if (!context_) return false;

		if (codec->capabilities & AV_CODEC_CAP_TRUNCATED)
			context_->flags |= AV_CODEC_FLAG_TRUNCATED;

		context_->flags2 |= AV_CODEC_FLAG2_CHUNKS;

		if (avcodec_open2(context_, codec, nullptr) < 0) {
			destroy();
			return false;
		}

		return true;
	}

	///
	/// \details
	void destroy() {
		avcodec_free_context(&context_);
		context_ = nullptr;
	}

	///
	/// \details
	/// \param[in]	data
	/// \retval
	/// \retval
	bool decode(const QByteArray& data) {
		if (!context_) return false;

		auto packet = av_packet_alloc();
		if (!packet) return false;

		auto result = av_new_packet(packet, data.size());
		if (result != 0) {
			av_packet_free(&packet);
			return false;
		}
		else memcpy(packet->data, data.data(), data.size());

		auto frame = av_frame_alloc();
		if (!frame) {
			av_frame_free(&frame);
			av_packet_free(&packet);
			return false;
		}

		int got = 0;
		result = avcodec_decode_video2(context_, frame, &got, packet);
		if (result <= 0 || got <= 0) {
			av_frame_free(&frame);
			av_packet_free(&packet);
			return false;
		}

		auto picture = av_frame_alloc();
		if (!picture) {
			av_frame_free(&frame);
			av_packet_free(&packet);
			return false;
		}

		AVPixelFormat format;
		switch (context_->pix_fmt) {
		case AV_PIX_FMT_YUVJ420P:
			format = AV_PIX_FMT_YUV420P;
			break;
		case AV_PIX_FMT_YUVJ422P:
			format = AV_PIX_FMT_YUV422P;
			break;
		case AV_PIX_FMT_YUVJ444P:
			format = AV_PIX_FMT_YUV444P;
			break;
		case AV_PIX_FMT_YUVJ440P:
			format = AV_PIX_FMT_YUV440P;
			break;
		default:
			format = context_->pix_fmt;
			break;
		}

		auto swsContext = sws_getContext(context_->width,
										 context_->height,
										 format,
										 context_->width,
										 context_->height,
										 AV_PIX_FMT_RGB24,
										 SWS_BICUBIC,
										 nullptr,
										 nullptr,
										 nullptr);
		if (!swsContext) {
			av_frame_free(&picture);
			av_frame_free(&frame);
			av_packet_free(&packet);
			return false;
		}

		avpicture_alloc(reinterpret_cast<AVPicture*>(picture),
						AV_PIX_FMT_RGB24,
						context_->width,
						context_->height);

		sws_scale(swsContext,
				  frame->data,
				  frame->linesize,
				  0,
				  context_->height,
				  picture->data,
				  picture->linesize);

		avpicture_free(reinterpret_cast<AVPicture*>(picture));
		sws_freeContext(swsContext);
		av_frame_free(&picture);
		av_frame_free(&frame);
		av_packet_free(&packet);

		return true;
	}

private:

	///
	/// \details
	AVCodecContext* context_;
};

///
/// \details
/// \param[in]	width
/// \param[in]	height
/// \param[in]	parent
VideoDecoder::VideoDecoder(QObject* parent)
	: QObject(parent),
	  private_(new VideoDecoderPrivate()) {

}

///
/// \details
VideoDecoder::~VideoDecoder() {
	destroy();
}

///
/// \details
/// \retval
/// \retval
bool VideoDecoder::initialize() {
	return private_->initialize();
}

///
/// \details
void VideoDecoder::destroy() {
	private_->destroy();
}

///
/// \details
/// \param[in]	data
void VideoDecoder::decode(const QByteArray& data) {

}
