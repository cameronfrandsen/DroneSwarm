
#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "DroneManagerLib/DroneManager.hpp"
#include "LoggerLib/Logger.hpp"
#include "RegistryLib/Registry.hpp"
#include "UDPLib/Response.hpp"
#include "UDPLib/UDPCommunicatorReliable.hpp"

namespace
{
  void runTest(udp::UDPCommunicatorReliable& com,
               const messages::Message& m,
               const boost::asio::ip::udp::endpoint& end,
               std::function<bool(const std::string& msg)> validator)
  {
    com.sendMessage(
      m.toString(), end, boost::posix_time::seconds(10), validator, 3);
  }

  void runPretest(std::string ip)
  {
    udp::UDPCommunicatorReliable com;
    boost::asio::ip::udp::endpoint end(
      boost::asio::ip::address::from_string(ip), 8889);
    auto isOkay = [](const std::string& msg) { return msg == "ok"; };
    runTest(com, messages::CommandMessage(), end, isOkay);
    runTest(com, messages::BackMessage(50), end, isOkay);
    runTest(com, messages::BatteryMessage(), end, [](const std::string& msg) {
      return msg == "95";
    });
    runTest(com, messages::ClockwiseMessage(53), end, isOkay);
    runTest(com, messages::CounterClockwiseMessage(54), end, isOkay);
    runTest(com, messages::DownMessage(55), end, isOkay);
    runTest(com, messages::FlipMessage("f"), end, isOkay);
    runTest(com, messages::ForwardMessage(56), end, isOkay);
    runTest(com, messages::GoMessage(57, 58, 59, 60), end, isOkay);
    runTest(com, messages::LeftMessage(61), end, isOkay);
    runTest(com, messages::MDirectionMessage(1), end, isOkay);
    runTest(com, messages::MoffMessage(), end, isOkay);
    runTest(com, messages::MonMessage(), end, isOkay);
    runTest(com, messages::RightMessage(62), end, isOkay);
    runTest(com, messages::SpeedMessage(), end, [](const std::string& msg) {
      return msg == "10";
    });
    runTest(com, messages::TakeoffMessage(), end, isOkay);
    runTest(com, messages::TimeMessage(), end, [](const std::string& msg) {
      return msg == "15";
    });
    runTest(com, messages::UpMessage(63), end, isOkay);
    runTest(com, messages::LandMessage(), end, isOkay);
  }
}

int main(int argc, char* argv[])
{
  std::string ip;
  std::string sPort;
  std::string mPort;
  unsigned short dPort;
  unsigned short statusPort;
  int startingY(0);
  try
  {
    // clang-format off
    boost::program_options::options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("ip,i", boost::program_options::value<std::string>()->required(),
        "IP Address for Drone")
      ("config,c", boost::program_options::value<std::string>()->required())
      ("groundstation,g", boost::program_options::value<std::string>(), 
        "Port for the ground station")
      ("monitorport,m", boost::program_options::value<std::string>(),
        "Port for the monitor")
      ("droneport,d", boost::program_options::value<unsigned short>(),
        "Port for the drone control")
      ("dronestatusport,s", boost::program_options::value<unsigned short>(),
          "Port for drone status")
      ("y,y", boost::program_options::value<int>(),
        "Starting y position")("pretest,p", "Run pretest");
    // clang-format on

    boost::program_options::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help"))
    {
      std::cout << desc << '\n';
      return 0;
    }

    notify(vm);

    ip = vm["ip"].as<std::string>();

    if (vm.count("pretest"))
    {
      runPretest(ip);
      return 0;
    }

    sPort = vm["groundstation"].as<std::string>();
    if (sPort.empty())
    {
      std::cout << "Must specify server port" << std::endl;
      return 1;
    }
    mPort = vm["monitorport"].as<std::string>();
    if (mPort.empty())
    {
      std::cout << "Must specify monitor port" << std::endl;
      return 1;
    }
    dPort = vm["droneport"].as<unsigned short>();
    if (dPort == 0)
    {
      std::cout << "Must specify drone port" << std::endl;
      return 1;
    }
    statusPort = vm["dronestatusport"].as<unsigned short>();
    if (statusPort == 0)
    {
      std::cout << "Must specify drone port for status" << std::endl;
      return 1;
    }
    if (vm.count("y")) startingY = vm["y"].as<int>();

    auto config = vm["config"].as<std::string>();
    if (!boost::filesystem::exists(config))
      throw std::runtime_error("Cannot access config");
    GlobalRegistry::setRegistry(boost::filesystem::path(config));
  }
  catch (const boost::program_options::error& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }

  try
  {
    drone::DroneManager manager(ip, dPort, statusPort, sPort, mPort, startingY);
  }
  catch (const std::runtime_error& error)
  {
    logger::logError("DroneManagerMain", error.what());
    return 1;
  }

  return 0;
}
