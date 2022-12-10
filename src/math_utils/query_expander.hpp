#pragma once

#include <seal/seal.h>
#include <vector>
#include "concurrency/concurrency.h"

namespace math_utils {
    /***
     * Represents a query in a specific dimension. (unlike sealPIR where each query contains multiple dimensions).
     */
    typedef std::vector<seal::Ciphertext> Query;

    /***
     * expand_query takes a part of multi-dimensional query and expand one part of.
     */
    class QueryExpander {
        QueryExpander(const seal::EncryptionParameters parameters, std::shared_ptr<concurrency::threadpool> sharedPtr);

        std::shared_ptr<concurrency::threadpool> pool;
    public:
        static std::shared_ptr<QueryExpander> Create(const seal::EncryptionParameters enc_params);

        static std::shared_ptr<QueryExpander>
        Create(const seal::EncryptionParameters enc_params, std::shared_ptr<concurrency::threadpool> &pool);

        std::vector<seal::Ciphertext>
        expand_query(std::vector<seal::Ciphertext> query_i, uint64_t n_i, seal::GaloisKeys &galkey) const;

        std::unique_ptr<concurrency::promise<std::vector<seal::Ciphertext>>>
        async_expand(std::vector<seal::Ciphertext> query_i, uint64_t n_i, seal::GaloisKeys &galkey);

        std::vector<seal::Ciphertext> __expand_query(const seal::Ciphertext &encrypted,
                                                     uint32_t m, seal::GaloisKeys &galkey) const;

    private:


        explicit QueryExpander(const seal::EncryptionParameters enc_params);

        seal::EncryptionParameters enc_params_;
        std::shared_ptr<seal::Evaluator> evaluator_;

        void
        multiply_power_of_X(const seal::Ciphertext &encrypted, seal::Ciphertext &destination, uint32_t index) const;
    };
}