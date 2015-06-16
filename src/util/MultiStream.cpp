////////////////////////////////////////////////////////////
//
// MiraiProject
// Copyright (C) 2014-2015 CORTIER Benoît (benoit.cortier@gmail.com), BOULMIER Jérôme (jerome.boulmier@outlook.fr)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <MiraiProject/util/MultiStream.hpp>

mp::MultiStream::MultiStream(std::vector<std::streambuf*> bufs)
    : m_bufs(bufs)
    , m_buffer(128)
{
    for (auto buf : m_bufs)
        assert(buf);

    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());
}

mp::MultiStream::~MultiStream()
{
    sync();
}

void mp::MultiStream::imbue(const std::locale& loc)
{
    for (auto buf : m_bufs)
        buf->pubimbue(loc);
}

int mp::MultiStream::overflow(int c)
{
    int character = sync() ? EOF : 0;
    sputc(static_cast<char>(c));
    return character;
}

int mp::MultiStream::sync()
{
    int answer;

    for (auto buf : m_bufs)
    {
        buf->sputn(pbase(), pptr() - pbase());
    }

    setp(m_buffer.data(), m_buffer.data() + m_buffer.size());

    answer = m_bufs[0]->pubsync();
    for (int i = 1; i < m_bufs.size(); ++i)
    {
        answer |= m_bufs[i]->pubsync();
    }
    return answer;

}
