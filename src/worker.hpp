#pragma once


#include "pir_server.hpp"
#include "distributed_pir.hpp"

class ClientSideServer : public PIRServer {

    std::uint32_t shard_id_;

// client side pir computations
PirReplyShard processQueryAtClient(PirQuery query, uint32_t client_id);

public:
// constructor for client side server
ClientSideServer(const seal::EncryptionParameters &seal_params, const PirParams &pir_params,
                 unique_ptr<vector<seal::Plaintext>>db, uint32_t shard_id);

// distributed pir functions client side
PirReplyShardBucket processQueryBucketAtClient(DistributedQueryContextBucket queries);

private:
    void expand_query_single_dim(vector<seal::Ciphertext> &expanded_query, std::uint64_t n_i,
                                 const PirQuerySingleDim& query, std::uint32_t client_id);

    void doPirMultiplication(uint64_t product, const vector<seal::Plaintext> *cur,
                             const vector<seal::Ciphertext> &expanded_query, uint64_t n_i,
                             vector<seal::Ciphertext> &intermediateCtxts, seal::Ciphertext &temp);

    void turn_intermediateCtexts_to_db_format( Database &intermediate_plain,
                                               const vector<seal::Ciphertext> &intermediateCtxts,
                                               uint64_t &product, Database *&cur);



};


