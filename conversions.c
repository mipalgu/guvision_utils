/*
 * conversions.c 
 * guvision_utils 
 *
 * Created by Callum McColl on 18/06/2020.
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

#include "conversions.h"

#include <guunits/guunits.h>


gu_percent_coordinate px_coord_to_pct_coord(const gu_pixel_coordinate coord)
{
    const pixels_t maxX = px_u_to_px_t(coord.res_width) - 1;
    const pixels_t maxY = px_u_to_px_t(coord.res_height) - 1;
    const float x = px_t_to_f(2 * coord.x - (maxX % 2)) / px_t_to_f(maxX);
    const float y = px_t_to_f(2 * coord.y - (maxY % 2)) / px_t_to_f(maxY);
    const gu_percent_coordinate newCoord = { f_to_pct_f(x), f_to_pct_f(y) };
    return newCoord;
}


gu_pixel_coordinate pct_coord_to_px_coord(gu_percent_coordinate coord, pixels_u res_width, pixels_u res_height)
{
    const pixels_t maxX = px_u_to_px_t(res_width) - 1;
    const pixels_t maxY = px_u_to_px_t(res_height) - 1;
    const float pixelsX = (pct_f_to_f(coord.x) * px_t_to_f(maxX) + px_t_to_f(maxX % 2)) / 2.0f;
    const float pixelsY = (pct_f_to_f(coord.y) * px_t_to_f(maxY) + px_t_to_f(maxY % 2)) / 2.0f;
    const gu_pixel_coordinate newCoord = { f_to_px_t(pixelsX), f_to_px_t(pixelsY), res_width, res_height };
    return newCoord;
}
