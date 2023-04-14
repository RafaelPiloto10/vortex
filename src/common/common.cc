#include "common.h"
#include <stdexcept>

void deserialize_header(const nlohmann::json &j, Context::Message &msg);
void deserialize_init_body(const nlohmann::json &j, Context::Message &msg);
void deserialize_init_ok_body(const nlohmann::json &j, Context::Message &msg);
void deserialize_echo_body(const nlohmann::json &j, Context::Message &msg);
void deserialize_echo_ok_body(const nlohmann::json &j, Context::Message &msg);

void Context::to_json(nlohmann::json &j, const Context::Message &msg) {
  switch (msg.type) {
  case NONE:
    // We should never be sending a NONE message
    throw std::invalid_argument("tried to serialize NONE");
    break;
  case INIT:
    // We should never be sending an INIT message
	j["src"] = msg.src;
	j["dest"] = msg.dest;
	j["body"] = {
		{"type", MessageTypeToStr[msg.type]},
		{"msg_id", std::get<Body::InitBody>(msg.body).msg_id},
		{"node_id", std::get<Body::InitBody>(msg.body).node_id},
		{"node_ids", std::get<Body::InitBody>(msg.body).node_ids},
	};
    break;
  case INIT_OK:
    // TODO:
    break;
  case ECHO:
    // We should never be sending an ECHO message
    throw std::invalid_argument(
        "tried to serialize ECHO when not expecting to");
    break;
  case ECHO_OK:
    // TODO:
    break;
  }
}

void Context::from_json(const nlohmann::json &j, Context::Message &msg) {
  deserialize_header(j, msg);
  if (msg.type == MessageType::NONE) {
    return;
  }

  // parse the body
  switch (msg.type) {
  case NONE:
    // We should never be parsing INIT_OK
    throw std::invalid_argument("tried to deserialize NONE type");
    break;
  case INIT:
	deserialize_init_body(j.at("body"), msg);
    break;
  case INIT_OK:
    // We should never be parsing INIT_OK
    throw std::invalid_argument(
        "tried to deserialize INIT_OK when not expecting to");
    break;
  case ECHO:
    break;
  case ECHO_OK:
    // We should never be parsing ECHO_OK
    throw std::invalid_argument(
        "tried to deserialize ECHO_OK when not expecting to");
    break;
  }
}

void deserialize_header(const nlohmann::json &j, Context::Message &msg) {
  j.at("src").get_to(msg.src);
  j.at("dest").get_to(msg.dest);
  std::string type_ = j.at("body").at("type").get<std::string>();
  if (!MessageTypeFromStr.contains(type_)) {
    msg.type = MessageType::NONE;
  } else {
    MessageType type = MessageTypeFromStr[type_];
    msg.type = type;
  }
}


void deserialize_init_body(const nlohmann::json &j, Context::Message &msg) {
  msg.body = Body::InitBody();
  j.at("msg_id").get_to(std::get<Body::InitBody>(msg.body).msg_id);
  j.at("node_id").get_to(std::get<Body::InitBody>(msg.body).node_id);
  j.at("node_ids").get_to(std::get<Body::InitBody>(msg.body).node_ids);
}

void deserialize_init_ok_body(const nlohmann::json &j, Context::Message &msg) {
}

void deserialize_echo_body(const nlohmann::json &j, Context::Message &msg) {
}

void deserialize_echo_ok_body(const nlohmann::json &j, Context::Message &msg) {
}
