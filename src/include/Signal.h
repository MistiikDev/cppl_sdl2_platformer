#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>
#include <map>
#include <functional>

template <typename... Args>

class SIGNAL {
    public:
        using T_Callback = std::function<void(Args...)>;

        SIGNAL(const std::string& signalName = "") : SignalName(signalName) {};

        const std::string SignalName;

        void Invoke(Args... args) const {
            for (const auto& [id, callback] : Subscribers) {
                if (callback) {
                    callback(args...);
                };
            }
        }

        void Subscribe(std::string& subscriberID, T_Callback callback) {
            Subscribers[subscriberID] = callback;
        }

        void Unsubscribe(std::string& subscriberID) {
            Subscribers.erase(subscriberID);
        }

    private: 
        std::map<std::string, T_Callback> Subscribers;
};

#endif