/*
 * PixelCoordinate.cc 
 * guvision_utils 
 *
 * Created by Callum McColl on 19/06/2020.
 * Copyright © 2020 Callum McColl. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgement:
 *
 *        This product includes software developed by Callum McColl.
 *
 * 4. Neither the name of the author nor the names of contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or
 * modify it under the above terms or under the terms of the GNU
 * General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "PixelCoordinate.hpp"

GU::PixelCoordinate::PixelCoordinate(): gu_pixel_coordinate() {}

GU::PixelCoordinate::PixelCoordinate(pixels_t t_x, pixels_t t_y, pixels_u t_resWidth, pixels_u t_resHeight): gu_pixel_coordinate { t_x, t_y, t_resWidth, t_resHeight } {} 

GU::PixelCoordinate::PixelCoordinate(const PixelCoordinate& other): gu_pixel_coordinate { other.x(), other.y(), other.resWidth(), other.resHeight() } {}

#if __cplusplus >= 199711L
GU::PixelCoordinate::PixelCoordinate(PixelCoordinate&& other)
{
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
    other.set_x(0);
    other.set_y(0);
    other.set_resWidth(0);
    other.set_resHeight(0);
}
#endif

GU::PixelCoordinate::~PixelCoordinate() {}

GU::PixelCoordinate& GU::PixelCoordinate::operator=(const PixelCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
    return *this;
}

#if __cplusplus >= 199711L
GU::PixelCoordinate& GU::PixelCoordinate::operator=(PixelCoordinate&& other)
{
    if (&other == this) {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
    other.set_x(0);
    other.set_y(0);
    other.set_resWidth(0);
    other.set_resHeight(0);
    return *this;
}
#endif

pixels_t GU::PixelCoordinate::x() const
{
    return gu_pixel_coordinate::x;
}

void GU::PixelCoordinate::set_x(const pixels_t newValue)
{
    gu_pixel_coordinate::x = newValue;
}

pixels_t GU::PixelCoordinate::y() const
{
    return gu_pixel_coordinate::y;
}

void GU::PixelCoordinate::set_y(const pixels_t newValue)
{
    gu_pixel_coordinate::y = newValue;
}

pixels_u GU::PixelCoordinate::resWidth() const
{
    return gu_pixel_coordinate::res_width;
}

void GU::PixelCoordinate::set_resWidth(const pixels_u newValue)
{
    gu_pixel_coordinate::res_width = newValue;
}

pixels_u GU::PixelCoordinate::resHeight() const
{
    return gu_pixel_coordinate::res_height;
}

void GU::PixelCoordinate::set_resHeight(const pixels_u newValue)
{
    gu_pixel_coordinate::res_height = newValue;
}

bool GU::PixelCoordinate::operator==(const PixelCoordinate &other) const
{
    return gu_pixel_coordinate_equals(*this, other);
}

bool GU::PixelCoordinate::operator!=(const PixelCoordinate &other) const
{
    return !(*this == other);
}
