#pragma once

#include "Network/Channel.h"
#include <string>
#include <vector>

void senderGetLatency(osuCrypto::Channel& chl);
void recverGetLatency(osuCrypto::Channel& chl);

std::vector<std::string> split(const std::string& str, const std::string& delim);