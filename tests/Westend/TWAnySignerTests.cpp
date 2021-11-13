// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "HexCoding.h"
#include "proto/Polkadot.pb.h"
#include "uint256.h"
#include "../interface/TWTestUtilities.h"
#include <TrustWalletCore/TWAnySigner.h>

#include <gtest/gtest.h>

using namespace TW;
using namespace TW::Polkadot;

TEST(TWAnySignerWestend, Sign) {
      auto key = parse_hex("0x22026a4eb35535936cbfa22824dca0c95653a4741a948039e0cebb764b06172c");
      auto genesisHash = parse_hex("0xe143f23803ac50e8f6f8e62695d1ce9e4e1d68aa36c1cd2cfd15340213f3423e");

    Proto::SigningInput input;
    input.set_block_hash(genesisHash.data(), genesisHash.size());
    input.set_genesis_hash(genesisHash.data(), genesisHash.size());
    input.set_nonce(1);
    input.set_spec_version(2019);
    input.set_private_key(key.data(), key.size());
    input.set_network(Proto::Network::WESTEND);
    input.set_transaction_version(2);

    auto balanceCall = input.mutable_balance_call();
    auto &transfer = *balanceCall->mutable_transfer();
    auto value = store(uint256_t(10000000000));
    transfer.set_to_address("5DbTZm853DT2HJzqPthEkbGRQWrmBHDQBDABj89FKkXbwKQ2");
    transfer.set_value(value.data(), value.size());

    Proto::SigningOutput output;
    ANY_SIGN(input, TWCoinTypeWestend);

    ASSERT_EQ(hex(output.encoded()), "35028443b0bb4379456744eca0b8b433cc016edd5ae1b38b876cd2f7d45dd96c7d2200001d9bf12df4325f3e40d9eb2971c995bee25c5c3a161f98dbcd59ccc1748800e6f150612ab790f768e70b40cdd68edc346b4ac155e365562e3a3beaee04bda007000400040043b0bb4379456744eca0b8b433cc016edd5ae1b38b876cd2f7d45dd96c7d22000700e40b5402");
}
