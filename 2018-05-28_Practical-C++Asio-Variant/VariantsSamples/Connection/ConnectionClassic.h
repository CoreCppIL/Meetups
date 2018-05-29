#pragma once

#include "ConnectionUtil.h"
#include <chrono>
#include <optional>
#include <string>
#include <variant>

namespace classic {

struct Connection {
  enum class State {
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    CONNECTION_INTERRUPTED
  };

  void disconnect() { 
    // maybe need to kill timer?
    m_state = State::DISCONNECTED; 
  }

  void interrupt() {
    switch (m_state) {
    case State::DISCONNECTED:
    case State::CONNECTING:
      m_state = State::DISCONNECTED;
      break;
    case State::CONNECTED:
      m_disconnectedTime = std::chrono::system_clock::now();
      notifyInterrupted(m_disconnectedTime);
      m_reconnectTimer = Timer{5000};
      m_state = State::CONNECTION_INTERRUPTED;
      break;
    case State::CONNECTION_INTERRUPTED:
      break;
    }
  }

  void notifyInterrupted(std::chrono::system_clock::time_point) {}

  std::string m_serverAddress;
  ConnectionId m_id;
  std::chrono::system_clock::time_point m_connectedTime;
  std::optional<std::chrono::milliseconds> m_lastPingTime;
  std::chrono::system_clock::time_point m_disconnectedTime;
  Timer m_reconnectTimer;

  State m_state = State::DISCONNECTED;
};

} // namespace classic
