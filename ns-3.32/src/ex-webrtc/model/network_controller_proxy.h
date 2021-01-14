#pragma once

#include "api/transport/network_control.h"

#include <iostream>

#define PRINT_ENTRY
// #define PRINT_ENTRY std::cout<<__func__<<std::endl;

class NetworkControllerProxy : public webrtc::NetworkControllerInterface
{
public:
  NetworkControllerProxy() : target_data_(webrtc::DataRate::KilobitsPerSec(1)) {
  }

  // Called when network availabilty changes.
  webrtc::NetworkControlUpdate OnNetworkAvailability(webrtc::NetworkAvailability msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.at_time);
  }

  // Called when the receiving or sending endpoint changes address.
  webrtc::NetworkControlUpdate OnNetworkRouteChange(webrtc::NetworkRouteChange msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.at_time);
  }

  // Called periodically with a periodicy as specified by
  // NetworkControllerFactoryInterface::GetProcessInterval.
  webrtc::NetworkControlUpdate OnProcessInterval(webrtc::ProcessInterval msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.at_time);
  }

  // Called when remotely calculated bitrate is received.
  webrtc::NetworkControlUpdate OnRemoteBitrateReport(webrtc::RemoteBitrateReport msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.receive_time);
  }

  // Called round trip time has been calculated by protocol specific mechanisms.
  webrtc::NetworkControlUpdate OnRoundTripTimeUpdate(webrtc::RoundTripTimeUpdate msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.receive_time);
  }

  // Called when a packet is sent on the network.
  webrtc::NetworkControlUpdate OnSentPacket(webrtc::SentPacket sent_packet) override {
    PRINT_ENTRY;
    return GetUpdate(sent_packet.send_time);
  }

  // Called when a packet is received from the remote client.
  webrtc::NetworkControlUpdate OnReceivedPacket(webrtc::ReceivedPacket received_packet) override {
    PRINT_ENTRY;
    return GetUpdate(received_packet.receive_time);
  }

  // Called when the stream specific configuration has been updated.
  webrtc::NetworkControlUpdate OnStreamsConfig(webrtc::StreamsConfig msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.at_time);
  }

  // Called when target transfer rate constraints has been changed.
  webrtc::NetworkControlUpdate OnTargetRateConstraints(webrtc::TargetRateConstraints constraints) override {
    PRINT_ENTRY;
    return GetUpdate(constraints.at_time);
  }

  // Called when a protocol specific calculation of packet loss has been made.
  webrtc::NetworkControlUpdate OnTransportLossReport(webrtc::TransportLossReport msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.receive_time);
  }

  // Called with per packet feedback regarding receive time.
  webrtc::NetworkControlUpdate OnTransportPacketsFeedback(webrtc::TransportPacketsFeedback report) override {
    PRINT_ENTRY;
    return GetUpdate(report.feedback_time);
  }
  // Called with network state estimate updates.
  webrtc::NetworkControlUpdate OnNetworkStateEstimate(webrtc::NetworkStateEstimate msg) override {
    PRINT_ENTRY;
    return GetUpdate(msg.update_time);
  }

private:
  webrtc::NetworkControlUpdate GetUpdate(webrtc::Timestamp at_time) const {
    webrtc::NetworkControlUpdate update;

    update.target_rate = webrtc::TargetTransferRate();
    update.target_rate->network_estimate.at_time = at_time;
    update.target_rate->network_estimate.bandwidth = target_data_;
    update.target_rate->network_estimate.loss_rate_ratio = 0;
    update.target_rate->network_estimate.round_trip_time = webrtc::TimeDelta::Millis(0);
    update.target_rate->network_estimate.bwe_period = webrtc::TimeDelta::Seconds(3);
    update.target_rate->at_time = at_time;
    update.target_rate->target_rate = target_data_;

    update.pacer_config = webrtc::PacerConfig();
    update.pacer_config->at_time = at_time;
    update.pacer_config->time_window = webrtc::TimeDelta::Seconds(1);
    update.pacer_config->data_window = target_data_ * update.pacer_config->time_window;
    update.pacer_config->pad_window = webrtc::DataRate::BitsPerSec(0) * update.pacer_config->time_window;

    return update;
  }

  webrtc::DataRate target_data_;
};
