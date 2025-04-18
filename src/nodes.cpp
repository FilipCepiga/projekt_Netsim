//
// Created by Filip Cepiga on 12/12/2023.
//


#include "nodes.hpp"

Ramp::Ramp(const Ramp &ramp) {
    id_ = ramp.get_id();
    di_ = ramp.get_delivery_interval();
    receiver_preferences_ = ramp.receiver_preferences_;
}

Ramp& Ramp::operator=(const Ramp &ramp) noexcept {
    id_ = ramp.get_id();
    di_ = ramp.get_delivery_interval();
    receiver_preferences_ = ramp.receiver_preferences_;
    return *this;
}

Worker::Worker(const Worker &worker) {
    id_ = worker.get_id();
    pd_ = worker.get_processing_duration();
    receiver_preferences_ = worker.receiver_preferences_;
    q_ = std::make_unique<PackageQueue>(worker.get_queue()->get_queue_type());
    st_ = worker.get_package_processing_start_time();
}

Worker& Worker::operator=(const Worker &worker) noexcept {
    id_ = worker.get_id();
    pd_ = worker.get_processing_duration();
    receiver_preferences_ = worker.receiver_preferences_;
    q_ = std::make_unique<PackageQueue>(worker.get_queue()->get_queue_type());
    st_ = worker.get_package_processing_start_time();
    return *this;
}

Storehouse::Storehouse(const Storehouse &storehouse) {
    id_ = storehouse.get_id();
    d_ = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
}

Storehouse& Storehouse::operator=(const Storehouse &storehouse) noexcept {
    id_ = storehouse.get_id();
    d_ = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    return *this;
}

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    if(preferences_.empty()){
        preferences_.emplace(r, 1);
    }
    else{
        preferences_.emplace(r, 0);
        std::size_t prefSize = preferences_.size();
        for(auto& i : preferences_){
            i.second = (1.0/double(prefSize));
        }
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    preferences_.erase(r);
    if(!preferences_.empty()) {
        std::size_t prefSize = preferences_.size();
        for (auto &i: preferences_) {
            i.second = (1.0 / double(prefSize));
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    IPackageReceiver* receiver;
    double probability = probability_();
    double distribution = 0.0;
    for(auto& i : preferences_){
        distribution += i.second;
        if (probability < distribution){
            receiver = i.first;
            break;
        }
    }
    return receiver;
}

void PackageSender::push_package(Package&& package) {
    if (!buffer_.has_value()) {
        buffer_.emplace(std::move(package));
    }
}

void PackageSender::send_package() {
    if (buffer_.has_value()) {
        receiver_preferences_.choose_receiver()->receive_package(std::move(*buffer_));
        buffer_.reset();
    }
}

void Ramp::deliver_goods(Time t) {
    if(di_ == 1){
        Package package = Package();
        push_package(std::move(package));
    }
    else if(t % di_ == 1){
        Package package = Package();
        push_package(std::move(package));
    }
}

void Worker::do_work(Time t) {
    if(!processing_buffer_.has_value() && !q_->empty()){
        processing_buffer_.emplace(q_->pop());
        st_ = t;
    }
    if(t - st_ + 1 == pd_ && processing_buffer_.has_value()){
        push_package(std::move(*processing_buffer_));
        processing_buffer_.reset();
    }
}

void Worker::receive_package(Package&& p) {
    q_->push(std::move(p));
}

void Storehouse::receive_package(Package&& p) {
    d_->push(std::move(p));
}