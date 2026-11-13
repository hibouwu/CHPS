#/bin/sh
## script pour installer golang et clang-format
sudo apt update
sudo apt-get install clang-format -y
sudo wget https://golang.org/dl/go1.25.5.linux-amd64.tar.gz
sudo tar -C /usr/local -xzf go1.25.5.linux-amd64.tar.gz
sudo rm ./go1.25.5.linux-amd64.tar.gz
cd ~
echo "export PATH=/usr/local/go/bin:${PATH}" | sudo tee -a $HOME/.profile
exit 0