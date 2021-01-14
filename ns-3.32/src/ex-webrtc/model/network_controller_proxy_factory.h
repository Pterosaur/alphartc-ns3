#pragma once

#include "network_controller_proxy.h"

#include "api/transport/network_control.h"

class NetworkControllerProxyFactory : public webrtc::NetworkControllerFactoryInterface {
public:
  // Used to create a new network controller, requires an observer to be
  // provided to handle callbacks.
  std::unique_ptr<webrtc::NetworkControllerInterface> Create(
      webrtc::NetworkControllerConfig config) override {
    return std::make_unique<NetworkControllerProxy>();
  }
  // Returns the interval by which the network controller expects
  // OnProcessInterval calls.
  virtual webrtc::TimeDelta GetProcessInterval() const override {
    const int64_t kUpdateIntervalMs = 25;
    return webrtc::TimeDelta::Millis(kUpdateIntervalMs);
  }
};
