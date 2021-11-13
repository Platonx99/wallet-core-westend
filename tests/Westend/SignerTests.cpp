// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Polkadot/Signer.h"
#include "Polkadot/Extrinsic.h"
#include "SS58Address.h"
#include "HexCoding.h"
#include "PrivateKey.h"
#include "PublicKey.h"
#include "proto/Polkadot.pb.h"
#include "uint256.h"
#include <iostream>
#include <fstream>
#include <string>
#include <TrustWalletCore/TWSS58AddressType.h>
#include <gtest/gtest.h>

namespace TW::Polkadot {
    extern PrivateKey privateKey;
    extern PublicKey toPublicKey;
    auto genesisHashWND = parse_hex("e143f23803ac50e8f6f8e62695d1ce9e4e1d68aa36c1cd2cfd15340213f3423e");


TEST(PolkadotSigner, SignTransferWND) {

    auto blockHash = parse_hex("be7df163a6a24c3a48454da350bba58102aaa9a86f64adc7baff020571e80754");
    auto toAddress = SS58Address(toPublicKey, TWSS58AddressTypeWestend);

    auto input = Proto::SigningInput();
    input.set_block_hash(blockHash.data(), blockHash.size());
    input.set_genesis_hash(genesisHashWND.data(), genesisHashWND.size());
    input.set_nonce(0);
    input.set_spec_version(2019);
    input.set_private_key(privateKey.bytes.data(), privateKey.bytes.size());
    input.set_network(Proto::Network::WESTEND);
    input.set_transaction_version(2);

    auto balanceCall = input.mutable_balance_call();
    auto &transfer = *balanceCall->mutable_transfer();
    auto value = store(uint256_t(12345));
    transfer.set_to_address(toAddress.string());
    transfer.set_value(value.data(), value.size());

    auto extrinsic = Extrinsic(input);
    auto preimage = extrinsic.encodePayload();
    auto output = Signer::sign(input);


  std::string s;
//   char hexString[4*sizeof(int)+1];
  // returns decimal value of hex
  //sprintf(hexString,"%i", 
  s= hex(preimage).c_str();
  //s = hexString;
  myfile.open ("/tmp/example.txt");
  myfile << "Test:\n" << s << "\n" << hex(output.encoded()).c_str();
  myfile.close();
  
ASSERT_EQ(hex(preimage), "04008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48e5c0000000e307000002000000e143f23803ac50e8f6f8e62695d1ce9e4e1d68aa36c1cd2cfd15340213f3423ebe7df163a6a24c3a48454da350bba58102aaa9a86f64adc7baff020571e80754");
ASSERT_EQ(hex(output.encoded()), "25028488dc3417d5058ec4b4503e0c12ea1a0a89be200fe98922423d4334014fa6b0ee00c35d5b0586ea8de454a1bcdd65c7ce8f82c4e4530c5c2b6fd68a9b46b8632ffbcb4cd27e8f1f92539d3238662a94683bef87bf9f26feaccd8583805591e1170400000004008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48e5c0");
}

} // namespace
