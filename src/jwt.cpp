#include "jwt.hpp"

#include <stdexcept>

Jwt::Jwt() {
  if (jwt_new(&token_))
    throw std::runtime_error("Error allocating jwt_t");
}

Jwt::~Jwt() { jwt_free(token_); }

Jwt::Jwt(const Jwt &other) {
  token_ = jwt_dup(other.token());
  if (!token_)
    throw std::runtime_error("Cannot duplicate token");
}

jwt_t *Jwt::token() const { return token_; }

void Jwt::operator=(const Jwt &other) {
  jwt_t *newtoken = jwt_dup(other.token());
  if (!newtoken)
    throw std::runtime_error("Cannot duplicate token");
  jwt_t *oldtoken = token_;
  token_ = newtoken;
  jwt_free(oldtoken);
}

Jwt::Jwt(std::string token, std::vector<unsigned char> key) {
  if (jwt_decode(&token_, token.c_str(), &key[0], key.size()))
    throw std::runtime_error("Cannot decode token");
}

std::string Jwt::get_grant(const std::string grant) {
  return jwt_get_grant(token_, grant.c_str());
}

void Jwt::add_grant(const std::string grant, const std::string value) {
  if (jwt_add_grant(token_, grant.c_str(), value.c_str()))
    throw std::runtime_error("Cannot add grant");
}

void Jwt::del_grant(const std::string grant) {
  if (jwt_del_grant(token_, grant.c_str()))
    throw std::runtime_error("Cannot delete grant");
}

void Jwt::add_grants_json(const std::string json) {
  if (jwt_add_grants_json(token_, json.c_str()))
    throw std::runtime_error("Cannot add grants");
}

std::string Jwt::dump(int pretty) { return jwt_dump_str(token_, pretty); }

std::string Jwt::encode() { return jwt_encode_str(token_); }

void Jwt::set_alg(jwt_alg_t alg, std::vector<unsigned char> key) {
  if (jwt_set_alg(token_, alg, key.size() ? &key[0] : nullptr, key.size()))
    throw std::runtime_error("Cannot set algorithm");
}
