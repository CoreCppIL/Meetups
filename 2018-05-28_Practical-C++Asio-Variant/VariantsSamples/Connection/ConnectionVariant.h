#pragma once

#include "ConnectionUtil.h"
#include "overload.h"
#include <chrono>
#include <optional>
#include <string>
#include <variant>

namespace variant {

struct Connection {
  struct Disconnected {};
  struct Connecting {};
  struct Connected {
    ConnectionId m_id;
    std::chrono::system_clock::time_point m_connectedTime;
    std::optional<std::chrono::milliseconds> m_lastPingTime;
  };
  struct ConnectionInterrupted {
    std::chrono::system_clock::time_point m_disconnectedTime;
    Timer m_reconnectTimer;
  };

  using State =
      std::variant<Disconnected, Connecting, Connected, ConnectionInterrupted>;

  State m_state;

  std::string m_serverAddress;

  void disconnect() {
    m_state = Disconnected();
    // if state was interrupted then ~Timer() would be called
  }

  void ifConstexprInterrupt() {
    m_state = std::visit(
        [this](const auto &state) -> State {
          // Needed to properly compare the types
          using T = std::decay_t<decltype(state)>;
          if constexpr (std::is_same_v<T, Connected>) {
            const auto now = std::chrono::system_clock::now();
            notifyInterrupted(now);
            return ConnectionInterrupted{now, 5000};
          } else if constexpr (std::is_same_v<T, ConnectionInterrupted>) {
            return state;
          } else {
            return Disconnected{};
          }
        },
        m_state);
  }

  void lambdaInterrupt() {
    m_state = std::visit(
        overload(
            [this](const Connected &) -> State {
              const auto now = std::chrono::system_clock::now();
              notifyInterrupted(now);
              return ConnectionInterrupted{now, 5000};
            },
            [](const ConnectionInterrupted &s) -> State { return s; },
            [](const auto & /*default*/) -> State { return Disconnected{}; }),
        m_state);
  }

  struct InterruptedEvent {
    InterruptedEvent(Connection &c) : m_c{c} {}
    template <typename T> State operator()(const T &) { return Disconnected(); }
    State operator()(const Connected &) {
      const auto now = std::chrono::system_clock::now();
      m_c.notifyInterrupted(now);
      return ConnectionInterrupted{now, 5000};
    }
    State operator()(const ConnectionInterrupted &s) { return s; }

  private:
    Connection &m_c;
  };

  void templateInterrupt() { m_state = std::visit(InterruptedEvent{*this}, m_state); }

  void functionObjectInterrupt() {
    struct InterruptedEvent {
      InterruptedEvent(Connection &c) : m_c{c} {}
      State operator()(const Disconnected &) { return Disconnected(); }
      State operator()(const Connecting &) { return Disconnected(); }
      State operator()(const Connected &) {
        const auto now = std::chrono::system_clock::now();
        m_c.notifyInterrupted(now);
        return ConnectionInterrupted{now, 5000};
      }
      State operator()(const ConnectionInterrupted &s) { return s; }

    private:
      Connection &m_c;
    };
    m_state = std::visit(InterruptedEvent{*this}, m_state);
  }

  void interrupt() {
    functionObjectInterrupt();
    templateInterrupt();
    lambdaInterrupt();
    ifConstexprInterrupt();
  }

  void notifyInterrupted(std::chrono::system_clock::time_point) {}
};

} // namespace variant
