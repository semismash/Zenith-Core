"""Generate codes.hpp from protocol.inc.

Run with no arguments to use the defaults below (paths are relative to THIS
script's location, not to where you run it from):

    python3 gen_codes.py

Or override either path:

    python3 gen_codes.py [--input PATH] [--output PATH]

Turns:   .equ TB_NET_SYN,     0xAA   # comment
Into:    inline constexpr uint8_t TB_NET_SYN = 0xAA;   // comment

Other '#' comment lines become '//' comments (section headers). Blank lines are kept.
"""
import os
import sys
import re
import argparse
from pathlib import Path

# ---- defaults (relative to this script's folder) ----
SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_INPUT = SCRIPT_DIR / "../../firmware/protocol.inc"
DEFAULT_OUTPUT = SCRIPT_DIR / "../src/headers/codes.hpp"
# -----------------------------------------------------

EQU = re.compile(r"^\s*\.equ\s+([A-Za-z_]\w*)\s*,\s*(\S+)\s*(?:#\s*(.*))?$")


def main() -> int:
    ap = argparse.ArgumentParser(description="Generate codes.hpp from protocol.inc")
    ap.add_argument("--input", "-i", type=Path, default=DEFAULT_INPUT,
                    help=f"path to protocol.inc (default: {DEFAULT_INPUT})")
    ap.add_argument("--output", "-o", type=Path, default=DEFAULT_OUTPUT,
                    help=f"path to write codes.hpp (default: {DEFAULT_OUTPUT})")
    args = ap.parse_args()

    src = Path(os.path.abspath(args.input))
    dst = Path(os.path.abspath(args.output))

    if not src.is_file():
        print(f"error: input file not found: {src}", file=sys.stderr)
        return 1

    out = [
        "// AUTO-GENERATED from protocol.inc by gen_codes.py. DO NOT EDIT.",
        "#pragma once",
        "#include <cstdint>",
        "",
        "namespace bios_protocol {",
        "",
    ]
    seen = {}

    with open(src, encoding="utf-8") as f:
        for lineno, raw in enumerate(f, 1):
            line = raw.rstrip("\r\n")
            stripped = line.strip()

            if not stripped:
                out.append("")
                continue

            if stripped.startswith("#"):
                out.append("// " + stripped.lstrip("#").strip())
                continue

            m = EQU.match(line)
            if not m:
                print(f"{src.name}:{lineno}: skipped unrecognized line: {stripped}", file=sys.stderr)
                continue

            name, value, comment = m.group(1), m.group(2), m.group(3)
            try:
                num = int(value, 0)  # handles 0x.., 0b.., decimal
            except ValueError:
                print(f"{src.name}:{lineno}: non-numeric value '{value}' for {name}", file=sys.stderr)
                return 1

            if name in seen:
                print(f"{src.name}:{lineno}: duplicate name {name} (first on line {seen[name]})", file=sys.stderr)
                return 1
            seen[name] = lineno

            ctype = "uint8_t" if 0 <= num <= 0xFF else "uint32_t"
            width = 2 if ctype == "uint8_t" else 8
            indent = "    " if line.startswith((" ", "\t")) else ""
            text = f"{indent}inline constexpr {ctype} {name} = 0x{num:0{width}X};"
            if comment:
                text += f"  // {comment.strip()}"
            out.append(text)

    out += ["", "} // namespace bios_protocol", ""]

    dst.parent.mkdir(parents=True, exist_ok=True)
    with open(dst, "w", encoding="utf-8", newline="\n") as f:
        f.write("\n".join(out))

    if not dst.is_file():
        print(f"error: write reported success but {dst} does not exist", file=sys.stderr)
        return 1
    print(f"wrote {dst} ({dst.stat().st_size} bytes, {len(seen)} constants)")
    return 0


if __name__ == "__main__":
    sys.exit(main())