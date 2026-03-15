/*
 * SPDX-FileCopyrightText: Copyright (c) 2020, 2021, 2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-FileCopyrightText: Copyright (c) Microsoft Corporation. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stddef.h> // NOLINT(*-deprecated-headers)
#include <stdint.h> // NOLINT(*-deprecated-headers)
#include <string>

#include <GDeflateConfig.h>
#include "Utils.h"

namespace GDeflate
{

#pragma pack(push, 1)

struct TileStream
{
    static constexpr uint32_t kMaxTiles = (1 << 16) - 1;

    uint8_t id;
    uint8_t magic;

    uint16_t numTiles;

    uint32_t tileSizeIdx : 2;
    uint32_t lastTileSize : 18;
    uint32_t reserved1 : 12;

    explicit TileStream(size_t uncompressedSize, uint8_t inTileSizeIdx = 1)
            : id(0)
            , magic(0)
            , numTiles(0)
            , tileSizeIdx(inTileSizeIdx)
            , lastTileSize(0)
            , reserved1(0)
    {
        SetCodecId(kGDeflateId);
        SetUncompressedSize(uncompressedSize);
    }

    [[nodiscard]] bool IsValid() const
    {
        return id == (magic ^ 0xff);
    }

    [[nodiscard]] size_t GetTileSize() const
    {
        return 1 << (15 + tileSizeIdx);
    }

    [[nodiscard]] size_t GetUncompressedSize() const
    {
        const size_t tileSize = GetTileSize();
        return numTiles * tileSize - (lastTileSize == 0 ? 0 : tileSize - lastTileSize);
    }

    void SetCodecId(uint8_t inId)
    {
        id = inId;
        magic = inId ^ 0xff;
    }

    void SetUncompressedSize(size_t size)
    {
        const size_t tileSize = GetTileSize();
        numTiles = static_cast<uint16_t>(size / tileSize);
        lastTileSize = static_cast<uint32_t>(size - numTiles * tileSize);

        numTiles += lastTileSize != 0 ? 1 : 0;
    }
};

static_assert(sizeof(TileStream) == 8, "Tile stream header size overrun!");

#pragma pack(pop)

} // namespace GDeflate
