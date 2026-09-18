#!/usr/bin/env python3
"""Encode a PlantUML file to the PlantUML server URL (custom base64 of zlib deflate).

Usage: python3 scripts/encode_plantuml.py path/to/file.puml
Prints PNG and SVG URLs to stdout.
"""
import sys
import zlib

ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_"

def encode6bit(b: int) -> str:
    return ALPHABET[b & 0x3F]

def append3bytes(b1: int, b2: int, b3: int) -> str:
    c1 = b1 >> 2
    c2 = ((b1 & 0x3) << 4) | (b2 >> 4)
    c3 = ((b2 & 0xF) << 2) | (b3 >> 6)
    c4 = b3 & 0x3F
    return encode6bit(c1) + encode6bit(c2) + encode6bit(c3) + encode6bit(c4)

def custom_base64(data: bytes) -> str:
    res = []
    i = 0
    n = len(data)
    while i < n:
        b1 = data[i]
        b2 = data[i+1] if i+1 < n else 0
        b3 = data[i+2] if i+2 < n else 0
        res.append(append3bytes(b1, b2, b3))
        i += 3
    return ''.join(res)

def plantuml_encode(text: str) -> str:
    compressed = zlib.compress(text.encode('utf-8'))
    # strip zlib header (2 bytes) and checksum (4 bytes)
    raw = compressed[2:-4]
    return custom_base64(raw)

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 scripts/encode_plantuml.py path/to/file.puml")
        sys.exit(1)
    path = sys.argv[1]
    with open(path, 'r', encoding='utf-8') as f:
        text = f.read()
    code = plantuml_encode(text)
    print("PNG URL:")
    print("https://www.plantuml.com/plantuml/png/" + code)
    print("SVG URL:")
    print("https://www.plantuml.com/plantuml/svg/" + code)

if __name__ == '__main__':
    main()