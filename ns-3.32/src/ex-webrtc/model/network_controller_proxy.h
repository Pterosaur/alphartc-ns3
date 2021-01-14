#pragma once

#include "api/transport/network_control.h"

class NetworkControllerProxy : public webrtc::NetworkControllerInterface
{
public:
  // Called when network availabilty changes.
  webrtc::NetworkControlUpdate OnNetworkAvailability(webrtc::NetworkAvailability) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called when the receiving or sending endpoint changes address.
  webrtc::NetworkControlUpdate OnNetworkRouteChange(webrtc::NetworkRouteChange msg) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called periodically with a periodicy as specified by
  // NetworkControllerFactoryInterface::GetProcessInterval.
  webrtc::NetworkControlUpdate OnProcessInterval(webrtc::ProcessInterval msg) override {
    return GetUpdate(msg.at_time);
  }

  // Called when remotely calculated bitrate is received.
  webrtc::NetworkControlUpdate OnRemoteBitrateReport(webrtc::RemoteBitrateReport) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called round trip time has been calculated by protocol specific mechanisms.
  webrtc::NetworkControlUpdate OnRoundTripTimeUpdate(webrtc::RoundTripTimeUpdate) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called when a packet is sent on the network.
  webrtc::NetworkControlUpdate OnSentPacket(webrtc::SentPacket sent_packet) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called when a packet is received from the remote client.
  webrtc::NetworkControlUpdate OnReceivedPacket(webrtc::ReceivedPacket) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called when the stream specific configuration has been updated.
  webrtc::NetworkControlUpdate OnStreamsConfig(webrtc::StreamsConfig) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called when target transfer rate constraints has been changed.
  webrtc::NetworkControlUpdate OnTargetRateConstraints(webrtc::TargetRateConstraints) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called when a protocol specific calculation of packet loss has been made.
  webrtc::NetworkControlUpdate OnTransportLossReport(webrtc::TransportLossReport) override {
    return webrtc::NetworkControlUpdate();
  }

  // Called with per packet feedback regarding receive time.
  webrtc::NetworkControlUpdate OnTransportPacketsFeedback(webrtc::TransportPacketsFeedback) override {
    return webrtc::NetworkControlUpdate();
  }
  // Called with network state estimate updates.
  webrtc::NetworkControlUpdate OnNetworkStateEstimate(webrtc::NetworkStateEstimate) override {
    return webrtc::NetworkControlUpdate();
  }

private:
  webrtc::NetworkControlUpdate GetUpdate(webrtc::Timestamp at_time) const {
    webrtc::NetworkControlUpdate update;
    webrtc::TargetTransferRate target_rate_msg;
    target_rate_msg.at_time = at_time;
    target_rate_msg.target_rate = webrtc::DataRate::KilobitsPerSec(6000);
    update.target_rate = target_rate_msg;
    return update;
  }
};
