#include "Sha256Generator.h"
#include <Poco/HMACEngine.h>
#include <boost/program_options.hpp>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <iostream>

// This is an example


using namespace utility;              // Common utilities like string conversions
using namespace web;                  // Common features like URIs.
using namespace web::http;            // Common HTTP functionality
using namespace web::http::client;    // HTTP client features
using namespace concurrency::streams; // Asynchronous streams
namespace bp = boost::program_options;

const std::string API_ENDPOINT = "https://api.crypto.com/v2/";
const std::string API_KEY = "";
const std::string API_SECRECT = "";
const std::pair<std::string, std::string> HTTP_HEADER = { "Content-Type", "application/json" };

int
main(int argc, char* argv[])
{
  const auto p1 = std::chrono::system_clock::now();
  json::value postData;
  json::value jsonReturn;
  postData["api_key"] = json::value::string(API_KEY);
  postData["method"] = json::value::string("private/get-order-history");
  postData["nonce"] =
    json::value::number(std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count());
  postData["id"] = json::value::number(11);
  postData["params"] = json::value::object();

  std::string payload_str = postData["method"].as_string() + std::to_string(postData["id"].as_integer()) +
                            postData["api_key"].as_string() + "" +
                            std::to_string(postData["nonce"].as_number().to_uint64());
  std::cout << payload_str << std::endl;
  Poco::HMACEngine<SHA256Engine> hmac{ API_SECRECT };
  hmac.update(payload_str);
  postData["sig"] = json::value::string(Poco::DigestEngine::digestToHex(hmac.digest()));

  http_request request(methods::POST);
  request.headers().add(HTTP_HEADER.first, HTTP_HEADER.second);
  request.set_body(postData);

  http_client client(API_ENDPOINT + "private/get-order-history");
  client.request(request)
    .then([](const web::http::http_response& response) { return response.extract_json(); })
    .then([&jsonReturn](const pplx::task<web::json::value>& task) {
      try {
        jsonReturn = task.get();
      } catch (const web::http::http_exception& e) {
        std::cout << "error " << e.what() << std::endl;
      }
    })
    .wait();

  std::cout << jsonReturn.serialize() << std::endl;
  return 0;
}
