#pragma once

#include <memory>
#include <limits>
#include <cinttypes>

#include "api/transport/network_control.h"
#include "api/transport/network_types.h"
#include "api/units/data_rate.h"
#include "absl/types/optional.h"

using BandwidthRate = std::uint32_t;

namespace webrtc {

// This class is for rate control, you can add your model
// to control the WebRTC sending bitrate.
class NetworkStateEstimatorProxy : public NetworkStateEstimator {
 public:
  NetworkStateEstimatorProxy(BandwidthRate data_rate);
  // Gets the current best estimate according to the estimator.
  absl::optional<NetworkStateEstimate> GetCurrentEstimate() override;
  // Called with per packet feedback regarding receive time.
  // Used when the NetworkStateEstimator runs in the sending endpoint.
  void OnTransportPacketsFeedback(const TransportPacketsFeedback& feedback) override;
  // Called with per packet feedback regarding receive time.
  // Used when the NetworkStateEstimator runs in the receiving endpoint.
  void OnReceivedPacket(const PacketResult& packet_result) override;
  // Called when the receiving or sending endpoint changes address.
  void OnRouteChange(const NetworkRouteChange& route_change) override;
  ~NetworkStateEstimatorProxy() override {}

 private:
  NetworkStateEstimate estimate_;
};

class NetworkStateEstimatorProxyFactory : public NetworkStateEstimatorFactory {
 public:
  std::unique_ptr<NetworkStateEstimator> Create(
      const WebRtcKeyValueConfig* key_value_config) override;
  ~NetworkStateEstimatorProxyFactory() override {}
};

} // namespace webrtc