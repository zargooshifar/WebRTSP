#pragma once

#include "Signalling/ServerSession.h"

#include "Config.h"


class ProxySession : public ServerSession
{
public:
    struct Cache {
        std::string list;
    };

    ProxySession(
        const Config*,
        Cache*,
        const std::function<std::unique_ptr<WebRTCPeer> (const std::string& uri)>& createPeer,
        const std::function<void (const rtsp::Request*)>& sendRequest,
        const std::function<void (const rtsp::Response*)>& sendResponse) noexcept;

protected:
    bool onOptionsRequest(
        std::unique_ptr<rtsp::Request>&) noexcept override;
    bool onListRequest(
        std::unique_ptr<rtsp::Request>&) noexcept override;

    bool onGetParameterResponse(
        const rtsp::Request&,
        const rtsp::Response&) noexcept override;
    bool onSetParameterResponse(
        const rtsp::Request&,
        const rtsp::Response&) noexcept override;

private:
    const Config *const _config;
    Cache *const _cache;

    rtsp::CSeq _authCSeq = 0;
    rtsp::CSeq _iceServerCSeq = 0;
};
