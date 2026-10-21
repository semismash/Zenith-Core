"""Generate messages_embed.hpp from messages.toml.

Run with no arguments to use the defaults below (paths are relative to THIS
script's location, not to where you run it from):

    python3 embed_messages.py

Or override either path:

    python3 embed_messages.py [--input PATH] [--output PATH]

The whole TOML file goes into one raw string literal, so the CLI carries its
messages inside the binary (no runtime path to find). The TOML itself is
parsed (and checked) by the CLI at startup with toml++.
"""
import os
import sys
import argparse
from pathlib import Path

# ---- defaults (relative to this script's folder) ----
SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_INPUT = SCRIPT_DIR / "../src/shell/messages.toml"
DEFAULT_OUTPUT = SCRIPT_DIR / "../src/headers/messages_embed.hpp"
# -----------------------------------------------------


def pick_delimiter(text: str) -> str:
    # raw string delimiter that doesn't appear in the text (max 16 chars by the standard)
    base = "zmsg"
    n = 0
    while f"){base}{n}\"" in text:
        n += 1
    return f"{base}{n}"


def main() -> int:
    ap = argparse.ArgumentParser(description="Generate messages_embed.hpp from messages.toml")
    ap.add_argument("--input", "-i", type=Path, default=DEFAULT_INPUT,
                    help=f"path to messages.toml (default: {DEFAULT_INPUT})")
    ap.add_argument("--output", "-o", type=Path, default=DEFAULT_OUTPUT,
                    help=f"path to write messages_embed.hpp (default: {DEFAULT_OUTPUT})")
    args = ap.parse_args()

    src = Path(os.path.abspath(args.input))
    dst = Path(os.path.abspath(args.output))

    if not src.is_file():
        print(f"error: input file not found: {src}", file=sys.stderr)
        return 1

    with open(src, encoding="utf-8") as f:
        text = f.read().replace("\r\n", "\n")

    if "\0" in text:
        print(f"error: {src.name} contains a NUL byte", file=sys.stderr)
        return 1

    delim = pick_delimiter(text)
    out = [
        "// AUTO-GENERATED from messages.toml by embed_messages.py. DO NOT EDIT.",
        "#pragma once",
        "#include <string_view>",
        "",
        "namespace messages_embed {",
        "",
        f"inline constexpr std::string_view messages_toml = R\"{delim}(" + text + f"){delim}\";",
        "",
        "} // namespace messages_embed",
        "",
    ]

    dst.parent.mkdir(parents=True, exist_ok=True)
    with open(dst, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(out))

    if not dst.is_file():
        print(f"error: write reported success but {dst} does not exist", file=sys.stderr)
        return 1
    print(f"wrote {dst} ({dst.stat().st_size} bytes, {text.count(chr(10))} lines of TOML)")
    return 0


if __name__ == "__main__":
    sys.exit(main())