#pragma once

#include <cstdint>

union Endpoint
{
    uint64_t fullEndpoint;
    struct EndpointFields
    {
        uint32_t ip;
        uint16_t port;
        uint16_t reserved;
    } endpointFields;

    static_assert(sizeof(fullEndpoint) == sizeof(endpointFields), "Union fields does not match");
};