#ifndef FINISH_RSP_HPP
#define FINISH_RSP_HPP

#include <string>

namespace msg
{
  class FinishRsp
  {
  public:
    FinishRsp();
    static std::string name() { return "FinishRsp"; }

    bool parseFromJson(const std::string& msg);
    bool parseFromProto(const std::string& msg);
    bool parseFromXml(const std::string& msg);

    std::string toJsonString() const;
    std::string toProtoString() const;
    std::string toXMLString() const;
  private:
  };
} // namespace msg

#endif