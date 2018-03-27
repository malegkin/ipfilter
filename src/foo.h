#pragma once

#include "stdafx.h"

tuple<uint32_t, string> s2IpHash(const string& in);

uint8_t oct(uint32_t iph, uint8_t index );

string h2str(uint32_t iph);
