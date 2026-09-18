#!/usr/bin/env sh
set -euo pipefail

PORT=9090
SRC=example.txt
OUT1=recr
OUT2=recr1

# 清理旧文件
rm -f "$OUT1" "$OUT2"

# 启动服务器（后台）
./server "$PORT" "$SRC" &
SERVER_PID=$!
sleep 1

# 启动两个客户端并等待完成
./client "$PORT" "$OUT1" &
./client "$PORT" "$OUT2" &

wait

# 关闭服务器
kill "$SERVER_PID" 2>/dev/null || true

# 校验文件是否一致
if diff "$SRC" "$OUT1" >/dev/null && diff "$SRC" "$OUT2" >/dev/null; then
  echo "OK: both clients received the file correctly."
else
  echo "FAIL: received files differ from source."
  exit 1
fi
