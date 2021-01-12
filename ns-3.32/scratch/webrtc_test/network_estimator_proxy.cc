#include "network_estimator_proxy.h"

#include <iostream>

namespace webrtc {

constexpr static BandwidthRate rate_bps = 1000000; // 1Mbps

NetworkStateEstimatorProxy::NetworkStateEstimatorProxy(BandwidthRate data_rate) {
  estimate_.link_capacity = DataRate::BitsPerSec(data_rate);
  estimate_.link_capacity_lower = DataRate::BitsPerSec(data_rate);
  estimate_.link_capacity_upper = DataRate::BitsPerSec(data_rate);
}

absl::optional<NetworkStateEstimate> NetworkStateEstimatorProxy::GetCurrentEstimate() {
  return estimate_;
}

void NetworkStateEstimatorProxy::OnTransportPacketsFeedback(const TransportPacketsFeedback& feedback) {
}

void NetworkStateEstimatorProxy::OnReceivedPacket(const PacketResult& packet_result) {
}

void NetworkStateEstimatorProxy::OnRouteChange(const NetworkRouteChange& route_change) {
}


std::unique_ptr<NetworkStateEstimator> NetworkStateEstimatorProxyFactory::Create(
      const WebRtcKeyValueConfig* key_value_config) {
  return std::make_unique<NetworkStateEstimatorProxy>(rate_bps);
}

}  // namespace webrtc