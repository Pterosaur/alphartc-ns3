#include "gym_connector.h"

#include "json.hpp"

using namespace webrtc;

constexpr double kPacingFactor = 2.5f;

GymConnector::GymConnector() :
    current_bandwidth_(0) {
}

std::list<std::string> GymConnector::Step(BandwidthType bandwidth, uint32_t duration) {
    SetBandwidth(bandwidth);
    Wait(duration);
    return ConsumeStates();
}

void GymConnector::Wait(std::uint32_t duration) const {

}

void GymConnector::SetBandwidth(BandwidthType bandwidth) {
    if (bandwidth == current_bandwidth_) {
        return;
    }
    {
        std::unique_lock<std::shared_timed_mutex> guard(mutex_bandiwidth_);
        current_bandwidth_ = bandwidth;
    }
}

webrtc::NetworkControlUpdate GymConnector::GetNetworkControlUpdate(const webrtc::Timestamp& at_time) const {
    BandwidthType current_bandwidth = {0};

    {
        std::shared_lock<std::shared_timed_mutex> guard(mutex_bandiwidth_);
        current_bandwidth = current_bandwidth_;
    }

    NetworkControlUpdate update;
    DataRate target_rate = DataRate::BitsPerSec(current_bandwidth);

    update.target_rate = TargetTransferRate();
    update.target_rate->network_estimate.at_time = at_time;
    update.target_rate->network_estimate.bandwidth = target_rate;
    update.target_rate->network_estimate.loss_rate_ratio = 0;
    update.target_rate->network_estimate.round_trip_time = webrtc::TimeDelta::Millis(0);
    update.target_rate->network_estimate.bwe_period = webrtc::TimeDelta::Seconds(3);
    update.target_rate->at_time = at_time;
    update.target_rate->target_rate = target_rate;

    update.pacer_config = PacerConfig();
    update.pacer_config->at_time = at_time;
    update.pacer_config->time_window = webrtc::TimeDelta::Seconds(1);
    update.pacer_config->data_window =  kPacingFactor * target_rate * update.pacer_config->time_window;
    update.pacer_config->pad_window = webrtc::DataRate::BitsPerSec(0) * update.pacer_config->time_window;

    return update;
}

void GymConnector::ProduceStates(
    int64_t arrival_time_ms,
    size_t payload_size,
    const webrtc::RTPHeader& header) {

    nlohmann::json j;
    j["arrival_time_ms"] = arrival_time_ms;
    j["payload_size"] = payload_size;
    j["send_time_ms"] = header.extension.absoluteSendTime;
    j["transport_sequence_number"] = header.extension.transportSequenceNumber;
    j["payload_type"] = header.payloadType;
    j["sequence_number"] = header.sequenceNumber;
    j["ssrc"] = header.ssrc;
    j["padding_length"] = header.paddingLength;
    j["header_length"] = header.headerLength;

    const std::string stats = j.dump();
    {
        std::unique_lock<std::mutex> guard(mutex_stats_);
        stats_.push_back(stats);
    }
}

std::list<std::string> GymConnector::ConsumeStates() {
    std::list<std::string> stats;
    {
        std::unique_lock<std::mutex> guard(mutex_stats_);
        std::swap(stats, stats_);
    }
    return stats;
}
