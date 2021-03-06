#ifndef DRONE_CONTROLLER_HPP
#define DRONE_CONTROLLER_HPP

#include <condition_variable>

#include <boost/optional.hpp>
#include <boost/signals2/connection.hpp>

#include "DroneControllerState.hpp"
#include "DroneMessagesLib/Message.hpp"
#include "DroneMessagesLib/Message_t.hpp"
#include "MonitorLoggerLib/MonitorLogger.hpp"
#include "UDPLib/UDPCommunicator.hpp"
#include "UDPLib/UDPCommunicatorReliable.hpp"

namespace drone
{
  class DroneController
  {
  public:
    DroneController(logger::MonitorLogger& logger,
                    unsigned short dronePort = 8889,
                    unsigned short droneStatusPort = 8890,
                    const std::string& ipAddress = std::string("127.0.0.1"),
                    int startingY = 0);

    ~DroneController();

    boost::optional<std::string> sendMessage(
      const messages::Message_t& message,
      boost::posix_time::time_duration timeout =
        boost::posix_time::seconds(10));

    size_t getBattery();
    double getX();
    double getY();
    double getZ();
    size_t getSpeed();
    size_t getTime();
    double getTimeOfFlight();
    bool getIsRunning();
    void waitForStatusMsg();
    bool isFlying();
    void stopRunning();

    boost::signals2::scoped_connection registerForMid(
      std::function<void(int)> callback);

  private:
    logger::MonitorLogger& m_logger;
    std::shared_ptr<DroneControllerState> m_pState;
    std::atomic<bool> m_running;
    udp::UDPCommunicatorReliable m_controlCommunicator;
    boost::asio::ip::udp::endpoint m_controlEndpoint;
    udp::UDPCommunicator m_statusCommunicator;
    boost::signals2::scoped_connection m_connection;
    std::condition_variable m_cvStatus;
    boost::signals2::signal<void(int)> m_midSignal;
    boost::signals2::scoped_connection m_midConnection;
    std::vector<int> m_mids;
    std::mutex m_statusMutex;
    std::thread m_statusThread;
  };
} // namespace drone

#endif
