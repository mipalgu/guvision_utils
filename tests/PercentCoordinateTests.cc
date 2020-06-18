/*
 * PercentCoordinateTests.cc 
 * tests 
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wfloat-equal"

#include <gtest/gtest.h>

#include <gu_util.h>
#include "../PercentCoordinate.hpp"

namespace CGTEST {
    
    class PercentCoordinateCPPTests: public ::testing::Test {
    protected:
        
        virtual void SetUp() {
        }
        
        virtual void TearDown() {
        }

    };

    TEST_F(PercentCoordinateCPPTests, RO5)
    {
        GU::PercentCoordinate coord = GU::PercentCoordinate(-1.0f, -1.0f);
        GU::PercentCoordinate coord2 = GU::PercentCoordinate(coord);
        ASSERT_EQ(coord, coord2);
        GU::PercentCoordinate coord3 = coord2;
        ASSERT_EQ(coord, coord3);
        coord.set_x(0.0f);
        ASSERT_NE(coord, coord3);
        ASSERT_EQ(coord2, coord3);
#if __cplusplus >= 199711L
        GU::PercentCoordinate coord4 = std::move(coord2);
        ASSERT_NE(coord4, coord2);
        ASSERT_EQ(coord4, coord3);
        ASSERT_EQ(coord2.x(), 0.0f);
        ASSERT_EQ(coord2.y(), 0.0f);
        GU::PercentCoordinate coord5;
        coord5 = std::move(coord4);
        ASSERT_NE(coord5, coord2);
        ASSERT_EQ(coord5, coord3);
        ASSERT_EQ(coord4.x(), 0.0f);
        ASSERT_EQ(coord4.y(), 0.0f);
#endif
    }

    TEST_F(PercentCoordinateCPPTests, GettersSetters) {
        GU::PercentCoordinate coord = GU::PercentCoordinate(-1.0f, -1.0f);
        ASSERT_EQ(coord.x(), -1.0f);
        coord.set_x(1.0f);
        ASSERT_EQ(coord.x(), 1.0f);
        ASSERT_EQ(coord.y(), -1.0f);
        coord.set_y(1.0f);
        ASSERT_EQ(coord.y(), 1.0f);
    }

    TEST_F(PercentCoordinateCPPTests, Equality) {
        const GU::PercentCoordinate topLeftEdge = GU::PercentCoordinate(-1.0f, 1.0f);
        const GU::PercentCoordinate topRightEdge = GU::PercentCoordinate(1.0f, 1.0f);
        const GU::PercentCoordinate bottomLeftEdge = GU::PercentCoordinate(-1.0f, -1.0f);
        const GU::PercentCoordinate bottomRightEdge = GU::PercentCoordinate(1.0f, -1.0f);
        const GU::PercentCoordinate middle = GU::PercentCoordinate(0.0f, 0.0f);
        ASSERT_TRUE(topLeftEdge == topLeftEdge);
        ASSERT_TRUE(topRightEdge == topRightEdge);
        ASSERT_TRUE(bottomLeftEdge == bottomLeftEdge);
        ASSERT_TRUE(bottomRightEdge == bottomRightEdge);
        ASSERT_TRUE(middle == middle);
        ASSERT_FALSE(topLeftEdge == topRightEdge);
        ASSERT_FALSE(topRightEdge == bottomLeftEdge);
        ASSERT_FALSE(bottomLeftEdge == bottomRightEdge);
        ASSERT_FALSE(bottomRightEdge == middle);
    }

}  // namespace

#pragma clang diagnostic pop
