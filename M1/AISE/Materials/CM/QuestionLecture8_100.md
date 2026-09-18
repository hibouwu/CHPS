
# 100 Questions de révision - Lecture 8 : Réseaux et Communication Distribuée / 100 道复习题 - 第八讲：网络与分布式通信

## I. Introduction & OSI / 概论与 OSI 模型 (1-20)

1. **Pourquoi a-t-on besoin de plusieurs machines en HPC (High Performance Computing) ? / 为什么 HPC 需要多台机器？**
    * Car un calcul peut être trop gros (mémoire) ou trop long pour une seule machine. (因为单台机器无法满足计算所需的内存或时间。)
2. **Quelle est la différence fondamentale entre mémoire partagée et distribuée concernant la communication ? / 共享内存和分布式内存在通信方面的根本区别是什么？**
    * Partagée = implicite (accès mémoire) ; Distribuée = explicite (envoi/réception de messages via le réseau). (共享=隐式（内存访问）；分布式=显式（通过网络收发消息）。)
3. **Combien de couches compte le modèle OSI théorique ? / 理论 OSI 模型有多少层？**
    * 7 couches. (7 层。)
4. **Quelle est la Couche 1 et son rôle ? / 第一层是什么及其作用？**
    * Physique (Physical) : Transmission des bits bruts sur un média (câble, ondes). (物理层：在介质（电缆、波）上传输原始比特。)
5. **Quelle est la Couche 2 et son rôle ? / 第二层是什么及其作用？**
    * Liaison de données (Data Link) : Transfert fiable entre deux nœuds directement connectés (LAN). (数据链路层：在直连节点（LAN）间可靠传输。)
6. **Quelle est l'adresse utilisée au niveau de la couche 2 ? / 第二层使用什么地址？**
    * Adresse MAC (Media Access Control). (MAC 地址。)
7. **Quelle est la Couche 3 et son rôle ? / 第三层是什么及其作用？**
    * Réseau (Network) : Acheminement (routage) des paquets à travers plusieurs réseaux jusqu'à destination. (网络层：跨越多个网络将数据包路由到目的地。)
8. **Quelle est l'adresse utilisée au niveau de la couche 3 ? / 第三层使用什么地址？**
    * Adresse IP (Internet Protocol). (IP 地址。)
9. **Quelle est la Couche 4 et son rôle ? / 第四层是什么及其作用？**
    * Transport : Communication de bout en bout entre applications (fiabilité, flux). (传输层：应用端到端的通信（可靠性、流控制）。)
10. **Quelles sont les couches 5, 6, 7 (modèle OSI) souvent regroupées en "Application" dans TCP/IP ? / OSI 模型中常在 TCP/IP 中归为“应用层”的是哪三层？**
    * Session, Présentation, Application. (会话、表示、应用。)
11. **Que fait la couche Présentation (6) ? / 表示层 (6) 做什么？**
    * Encodage, compression, chiffrement (ex: TLS). (编码、压缩、加密。)
12. **Que contient l'adresse MAC généralement ? / MAC 地址通常包含什么？**
    * Identifiant constructeur (OUI) + Identifiant unique de la carte. (厂商标识 + 网卡唯一标识。)
13. **Comment voir son adresse MAC sous Linux ? / Linux 下如何查看 MAC 地址？**
    * `ip a`, `ifconfig` ou `ip link`.
14. **Une adresse MAC est-elle routable sur Internet ? / MAC 地址可以在互联网上路由吗？**
    * Non, elle est locale au segment réseau (LAN). (不，它局限于本地网段。)
15. **Quel équipement connecte différents réseaux (Couche 3) ? / 哪个设备连接不同的网络（第三层）？**
    * Un Routeur (Router). (路由器。)
16. **Quel équipement connecte des machines dans un même réseau local (Couche 2) ? / 哪个设备连接同一局域网内的机器（第二层）？**
    * Un Commutateur (Switch). (交换机。)
17. **Qu'est-ce que l'encapsulation ? / 什么是封装？**
    * Chaque couche ajoute son en-tête aux données de la couche supérieure (Poupées russes). (每层给上层数据加上自己的头部（俄罗斯套娃）。)
18. **Qu'est-ce qu'une "Trame" (Frame) ? / 什么是“帧” (Frame)？**
    * Unité de données de la couche 2 (Liaison). (第二层（链路）的数据单元。)
19. **Qu'est-ce qu'un "Paquet" (Packet) ? / 什么是“包” (Packet)？**
    * Unité de données de la couche 3 (Réseau/IP). (第三层（网络/IP）的数据单元。)
20. **Qu'est-ce qu'un "Segment" (TCP) ou "Datagramme" (UDP) ? / 什么是“段” (TCP) 或“数据报” (UDP)？**
    * Unité de données de la couche 4 (Transport). (第四层（传输）的数据单元。)

## II. Réseau IP et Transport (TCP/UDP) / IP 网络与传输 (TCP/UDP) (21-50)

1. **Quelle est la taille d'une adresse IPv4 ? / IPv4 地址多大？**
    * 32 bits (4 octets, ex: 192.168.1.1).
2. **Pourquoi IPv4 est-il "épuisé" ? / 为什么 IPv4 “耗尽”了？**
    * Il y a plus d'appareils que d'adresses uniques possibles ($2^{32} \approx 4$ milliards). (设备数量超过了可能的唯一地址数。)
3. **Quelle est la solution à long terme pour remplacer IPv4 ? / 取代 IPv4 的长期方案是什么？**
    * IPv6 (128 bits).
4. **Qu'est-ce que le NAT ? / 什么是 NAT？**
    * Network Address Translation. Permet à plusieurs machines privées de partager une seule IP publique. (网络地址转换。允许多台私有机器共享一个公网 IP。)
5. **Où se fait généralement le NAT ? / NAT 通常在哪里进行？**
    * Sur le routeur/box internet (Gateway). (在路由器/网关上。)
6. **Quel est le rôle du TTL (Time To Live) dans un paquet IP ? / IP 包中 TTL 的作用是什么？**
    * Éviter qu'un paquet boucle infiniment (décrémenté à chaque routeur). (防止包无限循环（每经过一个路由器减 1）。)
7. **Quelle commande permet de tester la connectivité (Echo ICMP) ? / 哪个命令测试连通性（Echo ICMP）？**
    * `ping`.
8. **Quels sont les deux principaux protocoles de la couche Transport ? / 传输层的两个主要协议是什么？**
    * TCP (Transmission Control Protocol) et UDP (User Datagram Protocol).
9. **TCP est-il connecté ou non-connecté ? / TCP 是面向连接还是无连接的？**
    * Connecté (Circuit virtuel). (面向连接（虚电路）。)
10. **UDP est-il fiable ? / UDP 可靠吗？**
    * Non (Best effort). Pas de garantie d'ordre ou de livraison. (不可靠（尽力而为）。无顺序或交付保证。)
11. **Citez une caractéristique clé de TCP absente d'UDP. / 列举 TCP 有而 UDP 没有的一个关键特性。**
    * Rétransmission en cas de perte, contrôle de congestion, ordre garanti. (丢包重传，拥塞控制，顺序保证。)
12. **Quand utiliser UDP plutôt que TCP ? / 何时优先使用 UDP 而非 TCP？**
    * Temps réel (Streaming, VoIP, Jeux FPS) ou requêtes simples (DNS). (实时（流媒体，VoIP，FPS 游戏）或简单请求（DNS）。)
13. **Comment TCP ouvre-t-il une connexion ? / TCP 如何打开连接？**
    * Handshake en 3 temps (SYN, SYN-ACK, ACK). (三次握手。)
14. **Comment TCP ferme-t-il une connexion ? / TCP 如何关闭连接？**
    * Échange de FIN / ACK (dans les deux sens). (交换 FIN / ACK。)
15. **Qu'est-ce qu'un Port (numéro de port) ? / 什么是端口号？**
    * Un identifiant (16 bits) pour distinguer l'application/service destinataire sur une machine. (区分机器上接收应用/服务的标识符（16 位）。)
16. **Quel est le port standard pour le Web (HTTP) ? / Web (HTTP) 的标准端口是多少？**
    * 80.
17. **Quel est le port standard pour le Web sécurisé (HTTPS) ? / 安全 Web (HTTPS) 的标准端口是多少？**
    * 443.
18. **Quel est le port standard pour SSH ? / SSH 的标准端口是多少？**
    * 22.
19. **Qu'est-ce qu'un port "éphémère" ? / 什么是“临时”端口？**
    * Un port choisi dynamiquement par le client pour la réponse du serveur (souvent > 1024). (客户端动态选择用于接收服务器响应的端口。)
20. **Que permet de faire le contrôle de flux (Flow Control) de TCP ? / TCP 的流量控制有什么用？**
    * Éviter de submerger le récepteur (Fenêtre glissante). (避免淹没接收方（滑动窗口）。)
21. **Que permet de faire le contrôle de congestion de TCP ? / TCP 的拥塞控制有什么用？**
    * Éviter de saturer le réseau (Ralentir si perte de paquets). (避免网络饱和（丢包时减速）。)

## III. Application, DNS et Web / 应用、DNS 与 Web (51-70)

1. **Que signifie DNS ? / DNS 是什么意思？**
    * Domain Name System. (域名系统。)
2. **Quel est le rôle du DNS ? / DNS 的作用是什么？**
    * Traduire les noms de domaine (ex: `google.com`) en adresses IP. (将域名翻译为 IP 地址。)
3. **Le DNS utilise-t-il TCP ou UDP ? / DNS 使用 TCP 还是 UDP？**
    * Principalement UDP (port 53), parfois TCP pour les grosses réponses. (主要是 UDP（端口 53），大数据响应时用 TCP。)
4. **Qu'est-ce que HTTP ? / 什么是 HTTP？**
    * HyperText Transfer Protocol. (超文本传输协议。)
5. **Une requête HTTP classique (GET) utilise quel protocole de transport ? / 经典 HTTP 请求 (GET) 使用哪个传输协议？**
    * TCP.
6. **Que rajoute HTTPS par rapport à HTTP ? / HTTPS 相比 HTTP 增加了什么？**
    * Une couche de chiffrement (TLS/SSL) : Couche Présentation/Session. (加密层 (TLS/SSL)：表示/会话层。)
7. **Dans une trame HTTPS, peut-on voir l'URL demandée avec Wireshark ? / 在 HTTPS 帧中，用 Wireshark 能看到请求的 URL 吗？**
    * Non, elle est chiffrée (seule l'IP destination et le port sont visibles, parfois le SNI). (不能，它是加密的（只有目标 IP 和端口可见，有时可见 SNI）。)
8. **Qu'est-ce qu'un code retour 200 (HTTP) ? / HTTP 返回码 200 是什么？**
    * OK (Succès).
9. **Qu'est-ce qu'un code retour 404 ? / 返回码 404 是什么？**
    * Not Found (Ressource non trouvée). (未找到资源。)
10. **Quel outil permet de capturer et analyser les paquets réseau ? / 哪个工具可以捕获和分析网络数据包？**
    * Wireshark (ou tcpdump).
11. **Qu'est-ce que le handshake TLS ? / 什么是 TLS 握手？**
    * Échange de certificats et clés pour établir une connexion sécurisée avant d'envoyer des données HTTP. (发送 HTTP 数据前交换证书和密钥以建立安全连接。)
12. **Le chiffrement TLS est-il symétrique ou asymétrique ? / TLS 加密是对称还是非对称的？**
    * Hybride : Asymétrique pour l'échange de clés (Handshake), Symétrique pour les données (plus rapide). (混合：握手用非对称，数据用对称（更快）。)
13. **Qui garantit l'identité d'un serveur HTTPS ? / 谁保证 HTTPS 服务器的身份？**
    * Une Autorité de Certification (CA) via un Certificat Numérique. (认证机构 (CA) 通过数字证书。)
14. **Qu'est-ce qu'une requête GET ? / 什么是 GET 请求？**
    * Une méthode HTTP pour demander une ressource au serveur. (向服务器请求资源的 HTTP 方法。)
15. **Qu'est-ce que ICMP ? / 什么是 ICMP？**
    * Internet Control Message Protocol (Signale les erreurs, utilisé par ping). (互联网控制消息协议（报错，ping 使用）。)
16. **Le ping utilise-t-il un port ? / ping 使用端口吗？**
    * Non (il est au-dessus de IP, à côté de TCP/UDP). (不，它在 IP 之上，与 TCP/UDP 平级。)
17. **Que signifie "localhost" ? / "localhost" 是什么意思？**
    * La machine elle-même (Boucle locale). (本机（本地回环）。)
18. **Quelle est l'IP standard de localhost ? / localhost 的标准 IP 是多少？**
    * 127.0.0.1 (IPv4) ou ::1 (IPv6).
19. **Si un serveur écoute sur 127.0.0.1, est-il accessible depuis l'extérieur ? / 如果服务器监听 127.0.0.1，外部能访问吗？**
    * Non, seulement depuis la machine elle-même. (不能，只能从本机访问。)

## IV. Sockets & Programmation Système / Socket 与系统编程 (71-100)

1. **Qu'est-ce qu'un Socket (Abstraction) ? / 什么是 Socket（抽象）？**
    * Un point de terminaison d'un flux de communication réseau. (网络通信流的端点。)
2. **En C (Unix), comment est représenté un socket ? / 在 C (Unix) 中，Socket 如何表示？**
    * Par un descripteur de fichier (int). (文件描述符。)
3. **Quelle fonction crée un socket ? / 哪个函数创建 socket？**
    * `socket(domain, type, protocol)`.
4. **Pour TCP, quel `type` utilise-t-on dans `socket()` ? / 对于 TCP，`socket()` 中使用什么 `type`？**
    * `SOCK_STREAM`.
5. **Pour UDP, quel `type` utilise-t-on ? / 对于 UDP，使用什么 `type`？**
    * `SOCK_DGRAM`.
6. **Quelle est la séquence d'appels côté Serveur TCP ? / TCP 服务器端的调用序列是什么？**
    * `socket` -> `bind` -> `listen` -> `accept`.
7. **Quelle est la séquence d'appels côté Client TCP ? / TCP 客户端的调用序列是什么？**
    * `socket` -> `connect`.
8. **Que fait `bind()` ? / `bind()` 做什么？**
    * Associe le socket à une IP et un Port local. (将 socket 绑定到本地 IP 和端口。)
9. **Que fait `listen()` ? / `listen()` 做什么？**
    * Met le socket en mode passif (attente de connexions) et définit la file d'attente. (使 socket 进入被动模式（等待连接）并定义队列。)
10. **Que retourne `accept()` ? / `accept()` 返回什么？**
    * Un *nouveau* descripteur de fichier dédié à la connexion entrante. (一个专用于传入连接的*新*文件描述符。)
11. **Le socket d'écoute (listening socket) sert-il à échanger des données ? / 监听 socket 用于交换数据吗？**
    * Non, il ne sert qu'à accepter les connexions. (不，仅用于接受连接。)
12. **Comment envoyer des données sur un socket TCP ? / 如何在 TCP socket 上发送数据？**
    * `write()` ou `send()`.
13. **Comment recevoir des données ? / 如何接收数据？**
    * `read()` ou `recv()`.
14. **Que se passe-t-il si on fait `read()` sur un socket vide ? / 如果在空 socket 上 `read()` 会发生什么？**
    * Il bloque (attend des données) sauf si mode non-bloquant. (阻塞（等待数据），除非是非阻塞模式。)
15. **Que retourne `read()` si la connexion est fermée par l'autre bout ? / 如果对端关闭连接，`read()` 返回什么？**
    * 0 (EOF).
16. **Que fait `getaddrinfo()` ? / `getaddrinfo()` 做什么？**
    * Résout un nom d'hôte/service en structures d'adresses utilisables par `socket()`. (将主机名/服务解析为可供 `socket()` 使用的地址结构。)
17. **Quelle est la différence entre `close()` et `shutdown()` ? / `close()` 和 `shutdown()` 有什么区别？**
    * `close` ferme le descripteur (libère ressources). `shutdown` peut fermer une seule direction (ex: fin d'écriture). (`close` 关闭描述符（释放资源）。`shutdown` 可关闭单方向（如：写入结束）。)
18. **Pourquoi utiliser `shutdown(SHUT_WR)` ? / 为什么使用 `shutdown(SHUT_WR)`？**
    * Pour dire "j'ai fini d'envoyer", tout en continuant à recevoir la réponse (EOF envoyé à l'autre). (告知“发送完毕”并继续接收响应（向对方发送 EOF）。)
19. **Que signifient les fonctions `htons` / `ntohs` ? / 函数 `htons` / `ntohs` 是什么意思？**
    * Host TO Network Short / Network TO Host Short. Conversion boutisme (Endianness). (主机转网络短整型 / 网络转主机短整型。字节序转换。)
20. **Quel est le boutisme (Endianness) standard du réseau ? / 网络的标准字节序是什么？**
    * Big Endian (Gros-boutiste).
21. **Peut-on `bind` un port < 1024 en utilisateur normal ? / 普通用户可以 `bind` 小于 1024 的端口吗？**
    * Non, réservé à root (Ports privilégiés). (不能，保留给 root（特权端口）。)
22. **Que se passe-t-il si deux processus tentent de `bind` le même port ? / 如果两个进程尝试 `bind` 同一端口会发生什么？**
    * Erreur `EADDRINUSE` (Address already in use). (地址已被使用。)
23. **Qu'est-ce que l'adresse `0.0.0.0` (INADDR_ANY) ? / 地址 `0.0.0.0` (INADDR_ANY) 是什么？**
    * Toutes les interfaces locales (écouter sur toutes les IP de la machine). (所有本地接口（监听机器的所有 IP）。)
24. **Socket bloquant vs non-bloquant ? / 阻塞 vs 非阻塞 Socket？**
    * Bloquant : le programme attend. Non-bloquant : la fonction retourne erreur `EAGAIN` si pas prêt. (阻塞：程序等待。非阻塞：未就绪则返回错误 `EAGAIN`。)
25. **À quoi sert `select()` ou `poll()` ? / `select()` 或 `poll()` 有什么用？**
    * Surveiller plusieurs sockets à la fois (Multiplexing I/O) pour savoir qui est prêt à lire/écrire. (同时监控多个 socket（I/O 多路复用），得知谁准备好读/写。)
26. **Qu'est-ce qu'un socket "Unix domain" (`AF_UNIX`) ? / 什么是 "Unix domain" socket (`AF_UNIX`)？**
    * Socket local (fichier sur disque) pour communication inter-processus efficace (pas de réseau). (本地 socket（磁盘文件），用于高效进程间通信（无网络）。)
27. **Que contient `struct sockaddr_in` ? / `struct sockaddr_in` 包含什么？**
    * Famille (AF_INET), Port, Adresse IPv4.
28. **Pourquoi la programmation réseau est-elle sujette aux erreurs ? / 为什么网络编程易出错？**
    * Latence, coupures, timeouts, octets fragmentés... (延迟，断开，超时，字节碎片...)
29. **TCP garantit-il que `write(100)` sera lu en un seul `read(100)` ? / TCP 保证 `write(100)`会被一次 `read(100)` 读取吗？**
    * Non, c'est un flux (stream). On peut lire 50 puis 50. (不，它是流。可能读到 50 再 50。)
30. **Comment délimiter des messages en TCP ? / 如何在 TCP 中界定消息？**
    * Utiliser une longueur fixe, un délimiteur (ex: `\n`) ou un en-tête de taille. (固定长度，分隔符（如 `\n`）或长度头。)
