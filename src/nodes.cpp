//
// Created by Filip Cepiga on 12/12/2023.
//
/*#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    double num_of_receivers_begin = double(preferences_.size());
    if (num_of_receivers_begin == 0) {
        preferences_[r] = 1.0;
    } else {
        for (auto &rec: preferences_) {
            rec.second = 1 / (num_of_receivers_begin + 1);
        }
        preferences_[r] = 1 / (num_of_receivers_begin + 1);
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    double num_of_receivers_begin = double(preferences_.size());
    if (num_of_receivers_begin > 1) {
        for (auto &rec: preferences_) {
            if (rec.first != r) {
                rec.second = 1 / (num_of_receivers_begin - 1);
            }
        }
    }
    preferences_.erase(r);
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    auto prob = pg_();
    if (prob >= 0 && prob <= 1) {
        double distribution = 0.0;
        for (auto &rec: preferences_) {
            distribution = distribution + rec.second;
            if (distribution < 0 || distribution > 1) {
                return nullptr;
            }
            if (prob <= distribution) {
                return rec.first;
            }
        }
        return nullptr;
    }
    return nullptr;
}

void PackageSender::send_package() {
    IPackageReceiver *receiver;
    if (bufor_) {
        receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(*bufor_));
        bufor_.reset();
    }
}

void Worker::do_work(Time t) {
    if (!bufor_ && !q_->empty()) {
        bufor_.emplace(q_->pop());
        t_ = t;
    } else {
        if (t - t_ + 1 == pd_) {
            push_package(Package(bufor_.value().get_id()));
            bufor_.reset();
            if (!q_->empty()) {
                bufor_.emplace(q_->pop());
            }
        }
    }
}

void Worker::receive_package(Package &&p) {
    q_->push(std::move(p));
}

void Storehouse::receive_package(Package &&p) {
    d_->push(std::move(p));
}

void Ramp::deliver_goods(Time t) {
    if (!bufor_) {
        push_package(Package());
        bufor_.emplace(id_);
        t_ = t;
    } else {
        if (t - di_ == t_) {
            push_package(Package());
        }
    }
}
*/

#include "nodes.hpp"

Ramp::Ramp(const Ramp &ramp) {
    id_ = ramp.get_id();
    di_ = ramp.get_delivery_interval();
    receiver_preferences_ = ramp.receiver_preferences_;
}

Ramp& Ramp::operator=(const Ramp &ramp) noexcept{
    id_ = ramp.get_id();
    di_ = ramp.get_delivery_interval();
    receiver_preferences_ = ramp.receiver_preferences_;
    return *this;
}

Worker::Worker(const Worker &worker){
    id_ = worker.get_id();
    pd_ = worker.get_processing_duration();
    receiver_preferences_ = worker.receiver_preferences_;
    q_ = std::make_unique<PackageQueue>(worker.get_queue()->get_queue_type());
}

Worker& Worker::operator=(const Worker &worker) noexcept {
    id_ = worker.get_id();
    pd_ = worker.get_processing_duration();
    receiver_preferences_ = worker.receiver_preferences_;
    q_ = std::make_unique<PackageQueue>(worker.get_queue()->get_queue_type());
    return *this;
}

void ReceiverPreferences::add_receiver(IPackageReceiver *r){
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

void ReceiverPreferences::remove_receiver(IPackageReceiver *r){
    preferences_.erase(r);
    if(!preferences_.empty()) {
        std::size_t prefSize = preferences_.size();
        for (auto &i: preferences_) {
            i.second = (1.0 / double(prefSize));
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver(){
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

void PackageSender::push_package(Package&& package){
    if (!buffer_.has_value()) {
        buffer_.emplace(std::move(package));
    }
}

void PackageSender::send_package(){
    if (buffer_.has_value()) {
        receiver_preferences_.choose_receiver()->receive_package(std::move(*buffer_));
        buffer_.reset();
    }
}

void Ramp::deliver_goods(Time t){
    if (t % di_ == 1){
        Package package = Package();
        push_package(std::move(package));
    }
}

void Worker::do_work(Time t){
    if(!buffer_.has_value()){
        buffer_.emplace(q_->pop());
        st_ = t;
    }
    else if(t - st_ + 1 == pd_){
        push_package(std::move(*buffer_));
        buffer_.reset();
    }
}

void Worker::receive_package(Package&& p){
    q_->push(std::move(p));
}

void Storehouse::receive_package(Package&& p){
    d_->push(std::move(p));
}
