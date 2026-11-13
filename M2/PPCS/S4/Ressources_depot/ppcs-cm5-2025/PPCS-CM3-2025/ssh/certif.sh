#/bin/sh
mkdir /home/coder/.ssh
chmod 700 /home/coder/.ssh
cp -R /home/coder/.ssh-source/* /home/coder/.ssh \
        && chmod 700 /home/coder/.ssh/authorized_keys \
        && chmod 700 /home/coder/.ssh/id_rsa \
        && chown -R 1001:1001 /home/coder/.ssh
exit 0
