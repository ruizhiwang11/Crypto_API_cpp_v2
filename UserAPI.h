//
// Created by ruizhi on 7/1/22.
//

#ifndef CRYPTO_EXCHANGE_API_WRAPPER_USERAPI_H
#define CRYPTO_EXCHANGE_API_WRAPPER_USERAPI_H

class UserAPI
{
public:
  UserAPI(const std::string& apiKey, const std::string& secretKey);

private:
  const std::string m_apiKey;
  const std::string m_secretKey;
};

#endif // CRYPTO_EXCHANGE_API_WRAPPER_USERAPI_H
