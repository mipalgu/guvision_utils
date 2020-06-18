//
//  GUGeometryTests.cpp
//  gugridparticlefilter
//
//  Created by Callum McColl on 29/5/18.
//  Copyright © 2018 Vlad Estivill-Castro. All rights reserved.
//

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
#include <guunits/CartesianEdge.h>
#include <guunits/CartesianCoordinate.h>
#include "../pixel_to_rr_coord.h"

#include <gu_util.h>

namespace CGTEST {
    
    class GUGeometryTests: public ::testing::Test {
    protected:
        
        virtual void SetUp() {
        }
        
        virtual void TearDown() {
        }

    };

}  // namespace

#pragma clang diagnostic pop
