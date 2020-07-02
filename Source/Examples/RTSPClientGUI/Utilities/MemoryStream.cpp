/// \file MemoryStream.cpp
/// \brief Contains definitions of utilities for processing data in memory.
/// \bug No known bugs.

#include "MemoryStream.hpp"

#include <QtEndian>

/// A namespace that contains utilities for data streams.
namespace Utilities::Streams {

	/// Constructs a memory stream.
	/// \details Constructs a memory stream that has no I/O device.
	MemoryStream::MemoryStream()
		: swapBytes_(QSysInfo::ByteOrder != QSysInfo::BigEndian),
		  ownDevice_(false),
		  status_(Status::Ok),
		  byteOrder_(ByteOrder::BigEndian),
		  device_(nullptr) {

	}

	/// Constructs a memory stream.
	/// \details Constructs a memory stream that uses the I/O device \a device.
	/// \param[in]	device	I/O device.
	MemoryStream::MemoryStream(QIODevice* device)
		: swapBytes_(QSysInfo::ByteOrder != QSysInfo::BigEndian),
		  ownDevice_(false),
		  status_(Status::Ok),
		  byteOrder_(ByteOrder::BigEndian),
		  device_(device) {

	}

	/// Constructs a memory stream.
	/// \details Constructs a memory stream that operates on a byte
	/// array \a array. The \a mode describes how the device is to be used.
	/// \param[in]	array	Byte array.
	/// \param[in]	mode	I/O mode.
	MemoryStream::MemoryStream(QByteArray* array, QIODevice::OpenMode mode)
		: swapBytes_(QSysInfo::ByteOrder != QSysInfo::BigEndian),
		  ownDevice_(true),
		  status_(Status::Ok),
		  byteOrder_(ByteOrder::BigEndian),
		  device_(new QBuffer(array)) {

		device_->open(mode);
	}

	/// Constructs a memory stream.
	/// \details Constructs a read-only memory stream that operates on
	/// a byte array \a array.
	/// \param[in]	array	Byte array.
	MemoryStream::MemoryStream(const QByteArray& array)
		: swapBytes_(QSysInfo::ByteOrder != QSysInfo::BigEndian),
		  ownDevice_(true),
		  status_(Status::Ok),
		  byteOrder_(ByteOrder::BigEndian),
		  device_(new QBuffer) {

		static_cast<QBuffer*>(device_)->setData(array);
		static_cast<QBuffer*>(device_)->open(QIODevice::ReadOnly);
	}

	/// Destroys the memory stream.
	/// \details The destructor will not affect the current I/O device, unless
	/// it is an internal device processing an array passed in the constructor,
	/// in which case the internal I/O device is destroyed.
	MemoryStream::~MemoryStream() {
		if (ownDevice_)
			delete device_;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(qint8& item) {
		constexpr auto size = sizeof (item);

		if (readRawData(reinterpret_cast<char*>(&item), size) != size)
			item = 0;

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(quint8& item) {
		return *this >> reinterpret_cast<qint8&>(item);
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(qint16& item) {
		constexpr auto size = sizeof (item);

		if (readRawData(reinterpret_cast<char*>(&item), size) != size)
			item = 0;
		else if (swapBytes_)
			item = qbswap(item);

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(quint16& item) {
		return *this >> reinterpret_cast<qint16&>(item);
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(qint32& item) {
		constexpr auto size = sizeof (item);

		if (readRawData(reinterpret_cast<char*>(&item), size) != size)
			item = 0;
		else if (swapBytes_)
			item = qbswap(item);

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(quint32& item) {
		return *this >> reinterpret_cast<qint32&>(item);
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(qint64& item) {
		constexpr auto size = sizeof (item);

		if (readRawData(reinterpret_cast<char*>(&item), size) != size)
			item = 0;
		else if (swapBytes_)
			item = qbswap(item);

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(quint64& item) {
		return *this >> reinterpret_cast<qint64&>(item);
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(qfloat16& item) {
		return *this >> reinterpret_cast<qint16&>(item);
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(bool& item) {
		qint8 value;
		*this >> value;
		item = !!value;

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(float& item) {
		constexpr auto size = sizeof (item);

		if (readRawData(reinterpret_cast<char*>(&item), size) != size)
			item = 0.0f;
		else if (swapBytes_)
			item = qbswap(item);

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(double& item) {
		constexpr auto size = sizeof (item);

		if (readRawData(reinterpret_cast<char*>(&item), size) != size)
			item = 0.0;
		else if (swapBytes_)
			item = qbswap(item);

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(char16_t& item) {
		quint16 value;
		*this >> value;
		item = static_cast<char16_t>(value);

		return *this;
	}

	///
	/// \details
	/// \param[out]	item
	/// \return
	MemoryStream& MemoryStream::operator>>(char32_t& item) {
		quint32 value;
		*this >> value;
		item = static_cast<char32_t>(value);

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(qint8 item) {
		writeRawData(reinterpret_cast<char*>(&item), sizeof (item));

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(quint8 item) {
		return *this << static_cast<qint8>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(qint16 item) {
		if (swapBytes_) item = qbswap(item);

		writeRawData(reinterpret_cast<char*>(&item), sizeof (item));

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(quint16 item) {
		return *this << static_cast<qint16>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(qint32 item) {
		if (swapBytes_) item = qbswap(item);

		writeRawData(reinterpret_cast<char*>(&item), sizeof (item));

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(quint32 item) {
		return *this << static_cast<qint32>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(qint64 item) {
		if (swapBytes_) item = qbswap(item);

		writeRawData(reinterpret_cast<char*>(&item), sizeof (item));

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(quint64 item) {
		return *this << static_cast<qint64>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(qfloat16 item) {
		return *this << reinterpret_cast<qint16&>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(bool item) {
		return *this << static_cast<qint8>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(float item) {
		if (swapBytes_) item = qbswap(item);

		writeRawData(reinterpret_cast<char*>(&item), sizeof (item));

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(double item) {
		if (swapBytes_) item = qbswap(item);

		writeRawData(reinterpret_cast<char*>(&item), sizeof (item));

		return *this;
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(char16_t item) {
		return *this << static_cast<qint16>(item);
	}

	///
	/// \details
	/// \param[in]	item
	/// \return
	MemoryStream& MemoryStream::operator<<(char32_t item) {
		return *this << static_cast<qint32>(item);
	}

	///
	/// \details
	/// \param[in]	buffer
	/// \param[in]	bufferSize
	/// \return
	int MemoryStream::readRawData(char* buffer, int length) {
		if (!device_) return -1;

		const int result = device_->read(buffer, length);

		if (result != length)
			setStatus(Status::ReadPastEnd);

		return result;
	}

	///
	/// \details
	/// \param[in]	buffer
	/// \param[in]	bufferSize
	/// \return
	int MemoryStream::writeRawData(const char* buffer, int length) {
		if (!device_ || status_ != Status::Ok) return -1;

		const int result = device_->write(buffer, length);

		if (result != length)
			setStatus(Status::WriteFailed);

		return result;
	}

	///
	/// \details
	/// \param[in]	length
	/// \return
	int MemoryStream::skipRawData(int length) {
		if (!device_) return -1;

		const int result = device_->skip(length);

		if (result != length)
			setStatus(Status::ReadPastEnd);

		return result;
	}

	///
	/// \details
	/// \return I/O device.
	QIODevice* MemoryStream::device() const {
		return device_;
	}

	/// Sets the I/O device.
	/// \details Sets the I/O device to \a device, which can be \c nullptr
	/// to unset to current I/O device.
	/// \param[in]	device
	void MemoryStream::setDevice(QIODevice* device) {
		if (ownDevice_) {
			delete device_;
			ownDevice_ = false;
		}

		device_ = device;
	}

	///
	/// \details
	/// \return
	qint64 MemoryStream::bytesAvailable() const {
		return device_ ? device_->bytesAvailable() : 0;
	}

	///
	/// \details
	/// \return
	qint64 MemoryStream::position() const {
		return device_ ? device_->pos() : 0;
	}

	///
	/// \details
	/// \param[in]	position
	/// \retval
	/// \retval
	bool MemoryStream::seek(qint64 position) {
		return device_ ? device_->seek(position) : false;
	}

	/// Indicates whether the I/O device has reached the end position.
	/// \details Indicates whether the I/O device has reached the end position
	/// (end of the stream or file) or if there is no I/O device set.
	/// \retval \c true if the I/O device has reached the end position.
	/// \retval \c false if the I/O device has not reached the end position.
	bool MemoryStream::atEnd() const {
		return device_ ? device_->atEnd() : true;
	}

	/// Returns the status of the stream.
	/// \detailsReturns the current status of the stream.
	/// \return Status of the stream.
	MemoryStream::Status MemoryStream::status() const {
		return status_;
	}

	/// Sets the status of the stream to the \a status given.
	/// \details Subsequent calls are ignored until resetStatus() is called.
	/// \param[in]	status	Stream status.
	void MemoryStream::setStatus(Status status) {
		if (status_ == Status::Ok)
			status_ = status;
	}

	/// Resets the status of the stream.
	/// \details Resets the status of the stream to the default value.
	void MemoryStream::resetStatus() {
		status_ = Status::Ok;
	}

	/// Returns the current byte order setting.
	/// \details Returns the current byte order setting of either
	/// big-endian or little-endian.
	/// \return Current byte order.
	MemoryStream::ByteOrder MemoryStream::byteOrder() const {
		return byteOrder_;
	}

	/// Sets the byte order setting to \a byteOrder.
	/// \details Sets the byte order setting of either big-endian or
	/// little-endian.
	/// \param[in]	byteOrder	Byte order.
	void MemoryStream::setByteOrder(ByteOrder byteOrder) {
		byteOrder_ = byteOrder;

		if (QSysInfo::ByteOrder == QSysInfo::BigEndian)
			swapBytes_ = byteOrder_ != ByteOrder::BigEndian;
		else
			swapBytes_ = byteOrder_ != ByteOrder::LittleEndian;
	}
}
