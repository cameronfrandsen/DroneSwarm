#ifndef FINISH_RSP_HPP
#define FINISH_RSP_HPP

#include <string>
#include <vector>

#include "Target.hpp"

namespace msg
{
  class FinishRsp
  {
  public:
    FinishRsp();
    FinishRsp(const std::vector<Target>& targets);
    static std::string name() { return "FinishRsp"; }

    std::vector<Target> targets() const { return m_targets; }

    void targets(std::vector<Target> targets) { m_targets = targets; }

    bool parseFromJson(const std::string& msg);
    bool parseFromProto(const std::string& msg);
    bool parseFromXml(const std::string& msg);

    std::string toJsonString() const;
    std::string toProtoString() const;
    std::string toXMLString() const;

  private:
    std::vector<Target> m_targets;
  };
} // namespace msg

#endif
