//sha256.cpp
#ifndef MY_SHA256
#define MY_SHA256
#include "sha256.h"
std::string mysha256(std::string src){
  byte buffer[CryptoPP::SHA256::DIGESTSIZE];
  CryptoPP::SHA256 hash;
  hash.CalculateDigest(buffer,(byte*) src.c_str(), src.size());
  CryptoPP::HexEncoder encoder;
  std::string output;
  encoder.Attach(new CryptoPP::StringSink(output));
  encoder.Put(buffer,sizeof(buffer));
  encoder.MessageEnd();
  return output;
}

#endif
