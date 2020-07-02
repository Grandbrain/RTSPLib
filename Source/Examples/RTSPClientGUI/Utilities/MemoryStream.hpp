/// \file MemoryStream.hpp
/// \brief Contains declarations of utilities for processing data in memory.
/// \bug No known bugs.

#ifndef MEMORYSTREAM_HPP
#define MEMORYSTREAM_HPP

#include <QBuffer>
#include <QFloat16>

/// A namespace that contains utilities for data streams.
namespace Utilities::Streams {

	/// A class that provides a memory stream implementation for
	/// reading/writing the data.
	class MemoryStream {

		Q_DISABLE_COPY(MemoryStream)

	public:

		/// An enumeration that describes the byte order used for
		/// reading/writing the data.
		enum class ByteOrder {
			BigEndian	,	///< Most significant byte first.
			LittleEndian,	///< Least significant byte first.
		};

		/// An enumeration that describes the current status of the stream.
		enum class Status {
			Ok			,	///< The stream is operating normally.
			ReadPastEnd	,	///< The stream has read past the end of the data.
			WriteFailed	,	///< The stream cannot write to the underlying device.
		};

	public:

		/// Default constructor.
		explicit MemoryStream();

		///
		/// \param[in]	device
		explicit MemoryStream(QIODevice* device);

		///
		/// \param[in]	array
		/// \param[in]	mode
		explicit MemoryStream(QByteArray* array, QIODevice::OpenMode mode);

		///
		/// \param[in]	array
		explicit MemoryStream(const QByteArray& array);

		///
		virtual ~MemoryStream();

	public:

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(qint8& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(quint8& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(qint16& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(quint16& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(qint32& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(quint32& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(qint64& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(quint64& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(qfloat16& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(bool& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(float& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(double& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(char16_t& item);

		///
		/// \param[out]	item
		/// \return
		MemoryStream& operator>>(char32_t& item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(qint8 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(quint8 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(qint16 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(quint16 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(qint32 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(quint32 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(qint64 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(quint64 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(qfloat16 item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(bool item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(float item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(double item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(char16_t item);

		///
		/// \param[in]	item
		/// \return
		MemoryStream& operator<<(char32_t item);

	public:

		///
		/// \param[in,out]	buffer
		/// \param[in]		bufferSize
		/// \return
		int readRawData(char* buffer, int length);

		///
		/// \param[in]	buffer
		/// \param[in]	bufferSize
		/// \return
		int writeRawData(const char* buffer, int length);

		///
		/// \param[in]	length
		/// \return
		int skipRawData(int length);

		///
		/// \return
		QIODevice* device() const;

		///
		/// \param[in]	device
		void setDevice(QIODevice* device);

		///
		/// \return
		qint64 bytesAvailable() const;

		///
		/// \return
		qint64 position() const;

		///
		/// \param[in]	position
		/// \retval
		/// \retval
		bool seek(qint64 position);

		///
		/// \retval
		/// \retval
		bool atEnd() const;

		///
		/// \return
		Status status() const;

		///
		/// \param[in]	status
		void setStatus(Status status);

		///
		void resetStatus();

		///
		/// \return
		ByteOrder byteOrder() const;

		///
		/// \param[in]	byteOrder
		void setByteOrder(ByteOrder byteOrder);

	private:

		///
		bool swapBytes_;

		///
		bool ownDevice_;

		///
		Status status_;

		///
		ByteOrder byteOrder_;

		///
		QIODevice* device_;
	};
}

#endif
