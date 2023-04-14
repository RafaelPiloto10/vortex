#include "nlohmann/json.hpp"
#include <string>
#include <variant>
#include <vector>

enum MessageType {
  NONE,
  INIT,
  INIT_OK,
  ECHO,
  ECHO_OK

};

static std::vector<std::string> MessageTypeToStr = {"none", "init", "init_ok", "echo", "echo_ok"};
static std::map<std::string, MessageType> MessageTypeFromStr = {
    {"init", MessageType::INIT}, {"init_ok", MessageType::INIT_OK}, {"echo_ok", MessageType::ECHO_OK}, {"echo", MessageType::ECHO}};

namespace Body {
struct InitBody {
  int64_t msg_id;
  std::string node_id;
  std::vector<std::string> node_ids;
};

struct InitOkBody {
	int64_t msg_id;
	int64_t in_reply_to;
};

struct EchoBody {
  int64_t msg_id;
  std::string node_id;
  std::vector<std::string> node_ids;
};
} // namespace Body

namespace Context {
struct Message {
  MessageType type;
  std::string src;
  std::string dest;
  std::variant<Body::InitBody, Body::EchoBody> body;
};

void to_json(nlohmann::json &j, const Message &msg);
void from_json(const nlohmann::json &j, Message &msg);
} // namespace Context
