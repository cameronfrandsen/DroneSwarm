#ifndef READY_RSP_HPP
#define READY_RSP_HPP

#include <string>
#include <vector>

#include "Target.hpp"

namespace msg
{
  class ReadyRsp
  {
  public:
    ReadyRsp();
    ReadyRsp(int gameId, const std::vector<Target>& targets);
    static std::string name() { return "ReadyRsp"; }

    int gameId() const { return m_gameId; }
    std::vector<Target> targets() const { return m_targets; }

    void gameId(const int& gameId) { m_gameId = gameId; }
    void targets(const std::vector<Target>& targets) { m_targets = targets; }

    bool parseFromJson(const std::string& msg);
    bool parseFromProto(const std::string& msg);
    bool parseFromXml(const std::string& msg);

    std::string toJsonString() const;
    std::string toProtoString() const;
    std::string toXMLString() const;

  private:
    int m_gameId;
    std::vector<Target> m_targets;
  };
} // namespace msg

#endif
