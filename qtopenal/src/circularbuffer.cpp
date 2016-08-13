#include "include/circularbuffer.h"
#include <algorithm>

CircularBuffer::CircularBuffer(unsigned int capacity)
  : m_iBegIndex(0)
  , m_iEndIndex(0)
  , m_iSize(0)
  , m_iCapacity(capacity)
{
  m_pData_ = new char[capacity];
}

CircularBuffer::~CircularBuffer()
{
  delete [] m_pData_;
}

size_t CircularBuffer::Write(const char *data, unsigned int bytes)
{
  if (bytes == 0) return 0;

  unsigned int capacity = m_iCapacity;
  unsigned int bytes_to_write = std::min(bytes, capacity - m_iSize);

  // Write in a single step
  if (bytes_to_write <= capacity - m_iEndIndex)
  {
    memcpy(m_pData_ + m_iEndIndex, data, bytes_to_write);
    m_iEndIndex += bytes_to_write;
    if (m_iEndIndex == capacity) m_iEndIndex = 0;
  }
  // Write in two steps
  else
  {
    unsigned int size_1 = capacity - m_iEndIndex;
    memcpy(m_pData_ + m_iEndIndex, data, size_1);
    unsigned int size_2 = bytes_to_write - size_1;
    memcpy(m_pData_, data + size_1, size_2);
    m_iEndIndex = size_2;
  }

  m_iSize += bytes_to_write;
  return bytes_to_write;
}

unsigned int CircularBuffer::Read(char *data, unsigned int bytes)
{
  if (bytes == 0) return 0;

  unsigned int capacity = m_iCapacity;
  unsigned int bytes_to_read = std::min(bytes, m_iSize);

  // Read in a single step
  if (bytes_to_read <= capacity - m_iBegIndex)
  {
    memcpy(data, m_pData_ + m_iBegIndex, bytes_to_read);
    m_iBegIndex += bytes_to_read;
    if (m_iBegIndex == capacity) m_iBegIndex = 0;
  }
  // Read in two steps
  else
  {
    unsigned int size_1 = capacity - m_iBegIndex;
    memcpy(data, m_pData_ + m_iBegIndex, size_1);
    unsigned int size_2 = bytes_to_read - size_1;
    memcpy(data + size_1, m_pData_, size_2);
    m_iBegIndex = size_2;
  }

  m_iSize -= bytes_to_read;
  return bytes_to_read;
}
