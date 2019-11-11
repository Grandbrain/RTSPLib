/// \file VideoDecoder.hpp
/// \brief Contains classes and functions declarations that provide H.264
/// decoder implementation.
/// \bug No known bugs.

#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <QPixmap>
#include <QScopedPointer>

///
class VideoDecoder : public QObject {

	Q_OBJECT

public:

	///
	/// \param[in]	width
	/// \param[in]	height
	/// \param[in]	parent
	explicit VideoDecoder(QObject* parent = nullptr);

	///
	~VideoDecoder() override;

public:

	///
	/// \retval
	/// \retval
	bool initialize();

	///
	void destroy();

public slots:

	///
	/// \param[in]	data
	void decode(const QByteArray& data);

signals:

private:

	///
	class VideoDecoderPrivate;

	///
	QScopedPointer<VideoDecoderPrivate> private_;
};

#endif
