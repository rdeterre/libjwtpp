#include <cstdio>
#include <string>
#include <vector>

#include "libjwt/jwt.h"

class Jwt {
public:
  Jwt();

  ~Jwt();

  Jwt(const Jwt& other);

  Jwt(std::string token, std::vector<unsigned char> key);

  void operator=(const Jwt& other);

  std::string get_grant(const std::string grant);

  void add_grant(const std::string grant, const std::string value);

  void del_grant(const std::string grant);

  void add_grants_json(const std::string json);

  void set_alg(jwt_alg_t alg, std::vector<unsigned char> key);

  std::string dump(int pretty);

  std::string encode();

  jwt_t *token() const;

private:
  jwt_t* token_;
};
