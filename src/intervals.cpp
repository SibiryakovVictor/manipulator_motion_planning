#include "intervals.h"


using namespace settings;


IntervalsAllDims RangeLinksMotion::m_ranges = realRangesMotion;

bool RangeLinksMotion::canBothDirections[ manip::links_groups ] { false };
