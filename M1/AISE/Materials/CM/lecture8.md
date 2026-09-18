# lecture 8

## Au-delà d'une seule machine / Beyond a single node

- On parlait d'architectures parallèles mais les idées valent aussi pour le séquentiel (un seul CPU/coeur). 并行架构的概念同样适用于单处理器单核心的顺序架构。
- Jusqu'ici on restait sur une seule machine : rôle de l'OS et des abstractions pour exploiter le matériel (processus, threads, etc.). 之前只关注单机，操作系统提供抽象来利用底层硬件（进程、线程等）。
- Les unités d'exécution peuvent communiquer entre elles et introduire de la concurrence. 执行单元间能通信，会带来并发问题。
- Limite d'une seule machine : en HPC, un calcul trop gros ou trop long pousse à répartir données et charge sur plusieurs machines via le réseau. 当计算太大或太慢时，需要在多台机器上分配数据和工作负载，通过网络通信完成。
- Mémoire distribuée vs mémoire partagée : chaque machine a sa propre mémoire; pour partager il faut des communications explicites (envoyer/recevoir entre A, B, ou A vers plusieurs machines). 分布式内存需要显式收发数据，而共享内存中通信是隐式的。

## Réseau : rappel modèle OSI

### Exemple : accéder à « uvsq.fr »

- Côté logiciel : résoudre où se trouve `uvsq.fr`, demander et rapatrier la page. 软件层面先定位服务器，再请求并获取页面。
- Côté matériel : la machine utilise une carte réseau connectée à un équipement (routeur Wi-Fi ou Ethernet), qui relaye vers d'autres équipements jusqu'au serveur contenant la page. 硬件层面通过网卡连接路由器等设备，一跳一跳到达存放网页的服务器。
- Schéma mental : ordi → équipements réseau → Internet → équipements réseau → serveur. 思维示意：电脑 → 网络设备 → 互联网 → 网络设备 → 服务器。

### Couche matérielle / physique (couche 1)

- Inclut les câbles, cartes réseau et équipements physiques permettant l'interconnexion. 物理层涵盖电缆、网卡、交换/路由设备等用来互联机器的硬件。

### Couche liaison de données (couche 2)

- Transforme les requêtes en signaux électriques/optique modulés qui traversent chaque équipement du lien. 将请求转换为电信号/光信号在链路设备间传输。
- Gère la communication entre machines directement connectées (même réseau local). 负责同一局域网内机器间的通信。
- Adressage physique via adresses MAC pour décider par quel port sortir et à qui renvoyer la réponse. 通过 MAC 进行物理寻址，决定出口端口和响应的目的主机。
- Protocoles : Ethernet (filaire), Wi-Fi (sans fil). 协议：以太网（有线）、Wi-Fi（无线）。
- Exercice : `ip a` affiche les interfaces réseau de la machine et leurs adresses MAC (ex. interface Wi-Fi). 练习：`ip a` 可查看本机网络接口及其 MAC 地址（如 Wi-Fi 接口）。
- Structure d'une MAC : la première moitié identifie le constructeur, la seconde varie pour distinguer chaque équipement produit. MAC 前半部分是厂商标识，后半部分区分同厂商不同设备。

### Couche réseau (couche 3)

- Besoin quand on sort du réseau local : l'adresse MAC seule ne suffit plus. 离开局域网时仅靠 MAC 不够。
- Fournit l'adressage logique (IP) pour atteindre des machines sur d'autres réseaux. 提供逻辑寻址（IP）以到达其他网络的机器。
- Adresse IP du serveur cible permet de l'identifier et de la joindre (ex. `uvsq.fr` résolu en IP). 服务器的 IP 用于识别和访问，例如域名解析得到 IP。
- Acheminement/routage : chaque routeur lit l'IP destination et choisit la prochaine étape vers le réseau cible. 路由器根据目标 IP 选择下一跳，把包转发到目标网络。
- Format IPv4 : quatre nombres entre 0 et 255 (ex. Google a une IP de ce type). IPv4 由四个 0-255 的数字组成。
- Stock limité d'adresses uniques en IPv4 ; l'explosion du nombre d'équipements rend l'assignation unique/persistante impossible. IPv4 唯一地址数量有限，设备爆炸式增长导致无法给每个设备分配唯一公网地址。
- Solution courante : NAT (Network Address Translation) : le réseau local utilise des IP privées valables en interne ; la passerelle/routeur possède une IP locale et une IP publique pour parler à l'extérieur. 常见方案是 NAT：局域网用私有 IP，仅在内部有效；网关/路由器拥有本地 IP 与公网 IP，用于与外部通信。
- NAT en pratique : la requête sort vers la passerelle (IP locale), qui remplace l'IP source par son IP publique avant d'aller sur Internet ; le retour inverse la traduction pour atteindre la bonne machine interne. NAT 实际流程：请求先到网关（本地 IP），出网前被换成网关的公网 IP；返回时再翻译到对应的内网主机。
- Vu de l'extérieur, toutes les requêtes du LAN semblent venir d'une seule IP publique. 对外看似局域网所有请求都来自同一个公网地址。
- Plusieurs routes possibles entre deux réseaux : le routage choisit le chemin (éviter congestion, utiliser liens disponibles) et peut changer l'étape suivante pour optimiser. 两网络间可能多条路径，路由按需选路避免拥塞、利用可用链路。
- Adressage logique peut changer/être traduit (IP dynamiques/NAT), alors que l'adressage physique sert à distribuer les trames une fois dans le LAN cible. 逻辑地址可变化或被转换（动态 IP/NAT），物理地址用于在目标局域网内分发帧到具体机器。

- Exercice : `ping universite-paris-saclay.fr` envoie des paquets ICMP au serveur et affiche le temps aller-retour. 练习：`ping universite-paris-saclay.fr` 向服务器发送 ICMP 包并显示往返时间。

### Couche transport (couche 4)

- Gère la communication entre applications sur des machines différentes (contenu utile du “paquet”). 负责不同机器上应用间的通信，定义“包里”有哪些应用数据。
- Protocoles principaux : TCP (fiable, orienté connexion) et UDP (simple, non connecté). 主要协议：TCP（可靠、面向连接）与 UDP（简单、无连接）。
- TCP : établit une session (handshake), attend les accusés de réception, retransmet en cas de perte, contrôle flux/congestion pour assurer la livraison fiable. TCP 建立握手会话，确认接收，丢包重传，并做流量/拥塞控制以保证可靠传输。
- UDP : pas de session ni de vérification/retransmission ; plus léger, accepte des pertes (ex. streaming vidéo, temps réel). UDP 无会话/确认/重传，更轻量，可容忍丢包（如流媒体、实时场景）。
- Numéros de ports (0-65535) distinguent plusieurs flux/applications sur une même machine. 端口号（0-65535）用来区分同一机器上的多个通信流/应用。
- Exemple : le client propose un port local, le serveur répond et fixe son port côté serveur pour poursuivre l'échange. 例如客户端使用本地端口发起，服务器回应并指定自己的服务器端口继续通信。

### Couche session (couche 5)

- Gère l'ouverture, la gestion et la fermeture des sessions entre applications. 负责应用间会话的建立、管理与关闭。
- Assure la synchronisation et le contrôle du dialogue entre les applications. 确保应用间对话的同步与控制。
- Exemple : dans une session FTP, la couche session gère l'authentification, le maintien de la connexion et la reprise après une interruption. 例如在 FTP 会话中，session 层负责认证、连接维护和中断恢复。

### Couche présentation (couche 6)

- Traduit les données entre le format utilisé par l'application et le format standard de transmission. 负责应用使用的数据格式与传输标准格式之间的转换。
- Gère la compression, le chiffrement et la conversion de données. 负责数据压缩、加密与转换。
- Exemple : lors d'une connexion HTTPS, la couche présentation gère le chiffrement SSL/TLS pour sécuriser les données échangées. 例如在 HTTPS 连接中，présentation 层负责 SSL/TLS 加密以保护交换的数据。

### Couche application (couche 7)

- Regroupe les protocoles applicatifs : HTTP (web), FTP (fichiers), SSH, etc. 应用层协议：HTTP（网页）、FTP（文件）、SSH 等。
- Exemple HTTP : le navigateur envoie une requête `GET / HTTP/1.1` pour la page racine de `google.com`. 浏览器发出 `GET / HTTP/1.1` 请求以获取主页。
- La couche transport établit d'abord la connexion (ex. TCP) en choisissant des ports (client local, serveur écoute typiquement sur 80/443 pour HTTP/HTTPS). 传输层先用端口建立连接（客户端本地端口，服务器常用 80/443）。
- Une fois la connexion en place, la requête applicative part et le serveur renvoie la réponse (HTML demandé). 连接建立后发送应用请求，服务器返回所需的 HTML 内容。
- TLS chiffre le contenu applicatif (ex. HTTPS) : un observateur peut voir l'adresse contactée mais pas le contenu échangé. TLS 用于加密应用内容（如 HTTPS），旁观者能看到访问的地址但看不到具体内容。
- Capture réseau (ex. Wireshark) : on voit les couches empilées d'un paquet (application chiffrée TLS, transport TCP, réseau IPv4, liaison avec adresses physiques) et le début de l'échange client ↔ serveur. 抓包可见分层：应用层密文、传输层 TCP、网络层 IPv4、链路层物理地址，展示客户端与服务器交换的起点。

### Empilement et acheminement d'une requête HTTP (vue synthétique)

- Couche applicative : on ne voit qu'une requête (ex. GET page racine) et une réponse (code retour + HTML). 应用层只看到请求与响应（返回码 + HTML）。
- Couche transport (TCP) : handshake en 3 temps (SYN → SYN-ACK → ACK) pour ouvrir la connexion avec ports client/serveur ; données segmentées avec numéros de séquence et acquittements ; retransmission si perte ; contrôle de flux (fenêtre) et de congestion ; fermeture via FIN/ACK. 传输层 TCP：三次握手（SYN → SYN-ACK → ACK）建立连接并确定端口；数据分段附序号与确认；丢包重传；滑动窗口流量与拥塞控制；FIN/ACK 关闭连接。
- Couche réseau : chaque segment TCP est encapsulé dans un paquet IP avec IP source (client) et IP destination (serveur) qui traverse passerelle puis routeurs jusqu'au réseau cible. 网络层给每个 TCP 段加上源/目的 IP，经网关和各路由器到达目标网络。
- Couche liaison : sur chaque lien, le paquet IP est encapsulé dans une trame (Ethernet/Wi-Fi) avec adresses MAC source/destination du saut courant ; chaque équipement décapsule/re-encapsule pour le prochain saut. 链路层在每一跳用 MAC 封装成帧，设备逐跳解封再封装转发。
- À chaque nœud (routeur/commutateur), on descend jusqu'à la couche nécessaire pour décider du prochain saut, puis on remonte pour réémettre. 每个节点按需下探到对应层决定下一跳，再向上封装发送。

### Trame complète d'une requête HTTP chiffrée (ex. HTTPS)

- Application : requête `GET / HTTP/1.1` + en-têtes (Host, User-Agent, etc.) puis réponse (code 200, corps HTML). 应用层是 GET 和返回码+HTML。
- Présentation : chiffrement TLS encapsule la requête/réponse en données opaques ; handshake TLS (certificat, échange de clés) précède l'envoi du contenu. 表示层由 TLS 加密，请求/响应成为密文，先进行证书与密钥交换握手。
- Session : maintient le contexte de session TLS/HTTP (état de chiffrement, dialogue). 会话层维护 TLS/HTTP 的会话状态。
- Transport : segments TCP numérotés avec flags (SYN, ACK, PSH pour pousser des données, FIN pour fermer) ; ports typiques 443 (serveur) et port éphémère côté client. 传输层 TCP 段含标志位，服务器端口 443，客户端临时端口。
- Réseau : IP source/destination (peut être traduite par NAT) + TTL décrémenté à chaque routeur ; ICMP utilisé pour signaler des erreurs éventuelles. 网络层含源/目的 IP（NAT 可改写）、TTL 每跳减 1，ICMP 报错。
- Liaison : trame Ethernet/Wi-Fi avec MAC source/destination du saut ; FCS pour détecter erreurs de transmission locale. 链路层帧含本跳 MAC，带 FCS 校验。
- Physique : bits/symboles sur câble cuivre/fibre ou ondes radio. 物理层为比特在铜缆/光纤/无线信道上传输。

### DNS : résoudre une URL en adresse IP

- DNS maintient des tables nom de domaine → adresse(s) IP ; un même nom peut renvoyer plusieurs IP pour répartir la charge. DNS 维护域名到多条 IP 的映射，便于负载均衡。
- Avant l'échange HTTP, le client envoie une requête DNS (souvent UDP/53, parfois TCP) et reçoit l'IP (IPv4 et/ou IPv6). 在 HTTP 前先发 DNS 查询（多用 UDP/53），得到目标的 IPv4/IPv6。
- Les traces Wireshark montrent la requête DNS qui précède l'ouverture TCP/TLS/HTTP ; la réponse permet de démarrer la connexion. 抓包可见 DNS 先于 TCP/TLS/HTTP，解析结果用于后续连接。

### Sockets : abstraction OS pour le réseau

- Le système d'exploitation expose des sockets représentant un flux réseau lié à un port local. OS 提供 socket 抽象一个绑定本地端口的网络流。
- Un socket choisit le protocole de transport (TCP, UDP, …) ; l'application (HTTP, DNS, etc.) s'implémente au-dessus. Socket 可绑定 TCP/UDP 等传输协议，上层应用协议由开发者实现。
- Sous Unix, un socket est manipulé via un descripteur de fichier : on peut l'ouvrir, le fermer, lire/écrire comme un fichier. 在类 Unix 系统中，socket 通过文件描述符操作，可打开/关闭，读写类似文件。
- États typiques côté serveur TCP : création `socket()`, association à un port `bind()`, mise en écoute `listen()` pour attendre les connexions entrantes. 服务器侧常见状态：`socket()` 创建，`bind()` 绑定端口，`listen()` 进入监听。
- Côté client : création `socket()` puis `connect()` pour initier la connexion. 客户端：`socket()` 后 `connect()` 发起连接。
- Lorsqu'une demande arrive, le serveur appelle `accept()` : cela crée un nouveau socket dédié à cette connexion, tandis que le socket initial reste en écoute pour d'autres clients. 有连接到来时服务器调用 `accept()`，生成专用的新 socket，初始监听 socket 继续等待其他客户端。
- Une fois connectés, client et serveur utilisent le descripteur retourné pour échanger avec `read`/`write` (ou `recv`/`send`). 连接建立后，双方用文件描述符通过 `read`/`write`（或 `recv`/`send`）进行数据交换。
- Fin de communication : chaque pair appelle `close()` sur son descripteur pour signaler la fin d'envoi ; l'autre extrémité reçoit EOF et ferme à son tour. 结束通信时双方 `close()` 描述符，另一端读到 EOF 后也关闭。
- Démo locale : serveur ouvert sur `localhost:8080` écrit un message après `accept()`, le client lit puis affiche, puis chacun `close()`. 本地示例：服务器在 `localhost:8080` 接收后写消息，客户端读取打印，双方关闭。
- Variante messagerie ping-pong : client initie en envoyant un message, serveur répond, puis alternance d'envois/lectures jusqu'à fermeture. 消息往返示例：客户端先发，服务器回，然后轮流收发直至关闭。
- Résolution d'adresse avec `getaddrinfo()` : on fournit l'hôte (ex. `localhost`) et le port (ex. `"8080"`) plus une structure `hints` (famille IPv4/IPv6, type `SOCK_STREAM` pour TCP). 函数 `getaddrinfo()` 接收主机、端口和 hints（IPv4/IPv6，`SOCK_STREAM` 表示 TCP）。
- Itération des résultats `struct addrinfo` : on essaie `socket()` sur chaque entrée jusqu'à succès, puis côté serveur on `bind()`/`listen()` dessus. 逐个结果调用 `socket()`，服务器随后 `bind()`/`listen()`。
- Acceptation : `accept()` retourne un nouveau descripteur dédié à la session, distinct du socket d'écoute. `accept()` 返回的新描述符只用于该会话，监听 socket 继续等待。
- Flux de données : après acceptation/connexion, `write`/`read` (ou `send`/`recv`) font transiter les octets applicatifs ; en TCP l'ordre est garanti. 连接建立后用 `write`/`read` 传输应用字节，TCP 保序。
- Fermeture propre : côté initiateur on peut `shutdown(sock, SHUT_WR)` pour signaler "plus d'envoi" tout en continuant à lire, puis `close()` ; l'autre bout voit EOF et peut répondre/fermer. 规范关闭可先 `shutdown` 写端再 `close`，对端读到 EOF 后也关闭。
- Variante chat ping-pong détaillée : client lit au clavier → envoie, serveur lit → affiche → tape sa réponse → envoie, etc., bouclant jusqu'à saisie vide ou interruption pour tester l'échange bidirectionnel. 聊天演示：客户端输入并发送，服务器读取显示后回发，再反复，直到空输入或中断结束。
