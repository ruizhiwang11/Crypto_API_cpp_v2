//
// Created by ruizhi on 7/1/22.
//

#ifndef CRYPTO_EXCHANGE_API_WRAPPER_SHA256GENERATOR_H
#define CRYPTO_EXCHANGE_API_WRAPPER_SHA256GENERATOR_H
#include <Poco/Crypto/DigestEngine.h>

class SHA256Engine : public Poco::Crypto::DigestEngine
{
public:
  enum
  {
    BLOCK_SIZE = 64,
    DIGEST_SIZE = 32
  };

  SHA256Engine()
    : DigestEngine("SHA256")
  {}
};
#endif // CRYPTO_EXCHANGE_API_WRAPPER_SHA256GENERATOR_H
