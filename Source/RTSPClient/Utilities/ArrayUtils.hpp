/// \file ArrayUtils.hpp
/// \brief Contains declarations of various helper classes and functions for
/// working with byte arrays.
/// \bug No known bugs.

#ifndef ARRAYUTILS_HPP
#define ARRAYUTILS_HPP

#include <QtCore>

/// Contains classes and functions that implement Real Time Streaming Protocol
/// (RTSP) library.
namespace RTSPLib {

	/// Contains classes and functions that implement Real Time Streaming
	/// Protocol (RTSP) client library.
	namespace RTSPClient {

		/// Class that provides helper functions for easy reading and writing
		/// to a byte array.
		class ArrayUtils {

			/// Default onstructor.
			ArrayUtils() = delete;

			/// Copy constructor.
			/// \param[in]	object	Object to copy.
			ArrayUtils(const ArrayUtils& object) = delete;

			/// Copy assignment operator.
			/// \param[in]	object	Object to copy.
			/// \return This object.
			ArrayUtils& operator=(const ArrayUtils& object) = delete;

		public:

			/// Writes an item to a byte array.
			/// \tparam		T		Item type.
			/// \param[in]	item	Item to be written.
			/// \param[out]	array	Byte array.
			/// \param[in]	convert	Specifies whether to convert item to
			///						network byte order.
			template <typename T>
			static inline void write(T item,
									 QByteArray& array,
									 bool convert = false) {

				auto copy = convert ? qToBigEndian<T>(item) : item;

				array.append(
					reinterpret_cast<const char*>(&copy),
					sizeof(copy)
				);
			}

			/// Writes an item to a byte array.
			/// \tparam		T		Item type.
			/// \param[in]	item	Item to be written.
			/// \param[in]	index	Index.
			/// \param[out]	array	Byte array.
			/// \param[in]	convert	Specifies whether to convert item to
			///						network byte order.
			template <typename T>
			static inline void write(T item,
									 size_t index,
									 QByteArray& array,
									 bool convert = false) {

				auto copy = convert ? qToBigEndian<T>(item) : item;

				array.replace(
					index,
					sizeof(copy),
					reinterpret_cast<const char*>(&copy),
					sizeof(copy)
				);
			}

			/// Writes a string to a byte array.
			/// \param[in]	string	String to be written.
			/// \param[in]	bytes	Number of bytes to write.
			/// \param[out]	array	Byte array.
			static inline void write(const QString& string,
									 size_t bytes,
									 QByteArray& array) {

				auto data = string.toUtf8();
				auto size = static_cast<size_t>(data.size());
				size = size > bytes ? bytes : size;

				array.append(data.constData(), size);
				array.append(bytes - size, '\0');
			}

			/// Writes raw data to a byte array.
			/// \param[in]	data	Data pointer.
			/// \param[in]	size	Data size.
			/// \param[out]	array	Byte array.
			static inline void write(const char* data,
									 size_t size,
									 QByteArray& array) {

				array.append(data, size);
			}

			/// Reads an item from raw data.
			/// \tparam		T		Item type.
			/// \param[in]	data	Data pointer.
			/// \param[in]	convert	Specifies whether to convert data from
			///						network byte order.
			template <typename T>
			static inline T read(const char* data,
								 bool convert = false) {

				T copy = *reinterpret_cast<const T*>(data);
				return convert ? qFromBigEndian<T>(copy) : copy;
			}

			/// Reads a string from raw data.
			/// \param[in]	data	Data pointer.
			/// \param[in]	bytes	Number of bytes to read.
			static inline QString read(const char* data,
									   size_t bytes) {

				QString copy;

				for (size_t i = 0; i < bytes; ++i) {
					if (*data != '\0') copy += *data++;
					else break;
				}

				return copy;
			}
		};
	}
}

#endif
