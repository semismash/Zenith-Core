#pragma once

// visitor helper for std::visit (same one as the old assembler)
template <typename... Ts>
struct overload : Ts... { using Ts::operator()...; };