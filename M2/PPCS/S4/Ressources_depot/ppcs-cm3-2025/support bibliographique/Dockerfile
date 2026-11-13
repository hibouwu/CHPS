FROM debian:trixie-slim
# an image with OpenMPI4.1, used without root privileges for sshd
# XMP and telegraf
# ------------------------------------------------------------
# Do basic install
# ------------------------------------------------------------
RUN apt-get update \
    && mkdir -p /usr/share/man/man1 \
    && apt-get install -y --no-install-recommends gcc ssh wget vim curl net-tools bison flex openjdk-21-jdk-headless autoconf make \
    && apt-get install -y libtool m4 automake bzip2 libxml2 libxml2-dev gfortran g++ iputils-ping pkg-config colordiff \
    && apt-get install -y nano git sudo lsof gawk emacs jq neowofetch \
    && apt-get install -y libtdl* astyle cmake gdb strace binutils-dev dnsutils \
    && apt-get install -y netcat-traditional libgomp1 googletest supervisor munge libmunge2 libmunge-dev mariadb-server libmariadb-dev gnupg psmisc bash-completion libhttp-parser-dev libjson-c-dev libntirpc-dev libpmix-dev libpmix2 libpmi2-0-dev dbus \
    && adduser --uid 1001 --home /home/mpiuser --shell /bin/bash \
       --disabled-password --gecos '' mpiuser \
    && passwd -d mpiuser \
    && apt-get install -y openssh-server \
    && mkdir -p /run/sshd /home/mpiuser/.ssh /home/mpiuser/.ssh-source \
    && echo "StrictHostKeyChecking no" > /home/mpiuser/.ssh/config \
    && chown -R mpiuser /home/mpiuser \
    && sed -i s/#PermitRootLogin.*/PermitRootLogin\ no/ /etc/ssh/sshd_config \
    && sed -i s/#PubkeyAuthentication.*/PubkeyAuthentication\ no/ /etc/ssh/sshd_config \
    && sed -i s/.*UsePAM.*/UsePAM\ no/ /etc/ssh/sshd_config \
    && sed -i s/#PasswordAuthentication.*/PasswordAuthentication\ yes/ /etc/ssh/sshd_config \
    && sed -i s/#PermitEmptyPasswords.*/PermitEmptyPasswords\ yes/ /etc/ssh/sshd_config \
    && sed -i s/#ChallengeResponse.*/ChallengeResponseAuthentication\ no/ /etc/ssh/sshd_config \
    && sed -i s/#PermitUserEnvironment.*/PermitUserEnvironment\ yes/ /etc/ssh/sshd_config \
	&& adduser mpiuser sudo \
	&& apt-get clean \
	&& rm -rf /var/lib/apt/lists/*

ENV PREFIX=/usr/local \
    DEBCONF_NOWARNINGS=yes \
    OPENMPI_VERSION=4.1.8 \
    LD_LIBRARY_PATH=/usr/local/lib \
    USE_SLURMDBD=true \
    CLUSTER_NAME=linux \
    CONTROL_MACHINE=slurmctld \
    SLURMCTLD_PORT=6817 \
    SLURMD_PORT=6818 \
    ACCOUNTING_STORAGE_HOST=slurmdbd \
    ACCOUNTING_STORAGE_PORT=6819 \
    PARTITION_NAME=docker

# ------------------------------------------------------------
# Install OpenMPI 4.1
# https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.8.tar.gz
# ------------------------------------------------------------

# OpenMPI v4.1
RUN repo="https://download.open-mpi.org/release/open-mpi/v4.1" \
    && curl --location --silent --show-error --output openmpi.tar.gz \
      "${repo}/openmpi-${OPENMPI_VERSION}.tar.gz" \
    && tar xzf openmpi.tar.gz -C /tmp/ \
    && cd /tmp/openmpi-${OPENMPI_VERSION} \
	&& env CFLAGS="-O2 -std=gnu99 -fopenmp" \
    && ./configure --prefix=${PREFIX} --with-pmi=/usr --with-pmi-libdir=/usr/lib/x86_64-linux-gnu \
    && make \
    && make install \
    && ldconfig \
    && cd / \
    && rm -rf /tmp/openmpi-${OPENMPI_VERSION} /home/mpiuser/openmpi.tar.gz

# ------------------------------------------------------------
# Add some parameters for MPI, mpishare - a folder shared through the nodes
# ------------------------------------------------------------
RUN mkdir -p /usr/local/var/mpishare

RUN chown -R 1001:1001 /usr/local/var/mpishare

RUN echo "mpiuser ALL=(ALL) NOPASSWD:ALL\n" >> /etc/sudoers

RUN rm -fr /home/mpiuser/.openmpi && mkdir -p /home/mpiuser/.openmpi
RUN cd /home/mpiuser/.openmpi \
	&& echo "btl = tcp,self \n" \
	"btl_tcp_if_include = eth0 \n" \
	"plm_rsh_no_tree_spawn = 1 \n" >> default-mca-params.conf

RUN chown -R 1001:1001 /home/mpiuser/.openmpi

RUN echo "rmaps_base_oversubscribe = 1\n" >> /usr/local/etc/openmpi-mca-params.conf
RUN echo "rmaps_base_inherit = 1\n" >> /usr/local/etc/openmpi-mca-params.conf


# ------------------------------------------------------------
# Start mpi python install / user mpiuser
# ------------------------------------------------------------
RUN apt-get update \
    && apt-get install -y --no-install-recommends python3-minimal python3-pip python3-fissix \
    && apt-get clean && apt-get purge && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
# Installer l'outil pour créer des environnements virtuels
RUN apt-get update && apt-get install -y python3-venv



RUN mkdir -p /opt/venv
RUN chown -R mpiuser:mpiuser /opt/venv
# in order to have python related to mpiuser account
USER mpiuser
# Créer et activer l'environnement virtuel (dans le même RUN)

RUN python3 -m venv /opt/venv

ENV PATH="/opt/venv/bin:$PATH"
RUN pip install setuptools --break-system-packages \
    && pip install mpi4py --break-system-packages --no-cache-dir --force-reinstall \
    && pip install 2to3
USER root





# ------------------------------------------------------------
# Load omni-compiler 1.3.4 from a public repo
# ------------------------------------------------------------
RUN mkdir -p /home/mpiuser/YMLEnvironment
WORKDIR /home/mpiuser/YMLEnvironment
RUN wget --no-check-certificate --content-disposition https://omni-compiler.org/download/stable/omnicompiler-1.3.4.tar.bz2 \
    && bunzip2 omnicompiler-1.3.4.tar.bz2 \
	&& tar xvf omnicompiler-1.3.4.tar \
	&& rm /home/mpiuser/YMLEnvironment/omnicompiler-1.3.4.tar

# ------------------------------------------------------------
# Install omnicompiler-1.3.4 : requested javac
# ------------------------------------------------------------

WORKDIR /home/mpiuser/YMLEnvironment/omnicompiler-1.3.4
RUN cd /home/mpiuser/YMLEnvironment/omnicompiler-1.3.4 \
	&& export FCFLAGS="-w -fallow-argument-mismatch -O2" \
	&& export FFLAGS="-w -fallow-argument-mismatch -O2" \
	&& export MPI_FCFLAGS="-fopenmp -fallow-argument-mismatch -O2" \
	&& export CPPFLAGS="-fallow-argument-mismatch -DOMNI_CPU_X86_64 -DOMNI_OS_LINUX -DGNU_SOURCE -D_REENTRANT" \
	&& ./configure --prefix=${PREFIX} --with-libxml2=/usr \
	&& make && make install && make clean && ldconfig

# ------------------------------------------------------------
# Install test-spawn-xmp
# ------------------------------------------------------------
USER mpiuser
COPY test-spawn-xmp /home/mpiuser/YMLEnvironment/test-spawn-xmp
USER root
RUN chown -R mpiuser:mpiuser /home/mpiuser/YMLEnvironment

# ------------------------------------------------------------
# The .ssh-source dir contains RSA keys - put in place with docker-compose
# ------------------------------------------------------------


RUN touch /home/mpiuser/.ssh-source/authorized_keys
RUN touch /home/mpiuser/.ssh-source/id_rsa


# ------------------------------------------------------------
# Do SSHd parameter to enable slurm to run it
# ------------------------------------------------------------

RUN sed -i s/#UsePrivilegeSeparation.*/UsePrivilegeSeparation\ no/ /etc/ssh/sshd_config
RUN mkdir -p /home/mpiuser/ssh
RUN ssh-keygen -q -N "" -t rsa -b 4096 -f /home/mpiuser/ssh/ssh_host_rsa_key \
	&& ssh-keygen -q -N "" -t ecdsa -f /home/mpiuser/ssh/ssh_host_ecdsa_key \
	&& ssh-keygen -q -N "" -t ed25519 -f /home/mpiuser/ssh/ssh_host_ed25519_key

RUN cp /etc/ssh/sshd_config /home/mpiuser/ssh/

RUN sed -i s/#HostKey\ \\/etc\\/ssh/HostKey\ \\/home\\/mpiuser\\/ssh/ /home/mpiuser/ssh/sshd_config
RUN sed -i s/#PidFile\ \\/var\\/run/PidFile\ \\/home\\/mpiuser\\/ssh/ /home/mpiuser/ssh/sshd_config
RUN sed -i s/#LogLevel.*/LogLevel\ DEBUG3/ /home/mpiuser/ssh/sshd_config
RUN sed -i s/PubkeyAuthentication\ no/PubkeyAuthentication\ yes/ /home/mpiuser/ssh/sshd_config

RUN chown -R mpiuser:mpiuser /home/mpiuser/ssh


ARG SLURM_TAG=slurm-23-02-6-1
ARG JOBS=4
ARG GOSU_VERSION=1.17


RUN set -ex \
    && wget -O /usr/local/bin/gosu "https://github.com/tianon/gosu/releases/download/$GOSU_VERSION/gosu-amd64" \
    && wget -O /usr/local/bin/gosu.asc "https://github.com/tianon/gosu/releases/download/$GOSU_VERSION/gosu-amd64.asc" \
    && export GNUPGHOME="$(mktemp -d)" \
    && gpg --batch --keyserver hkps://keys.openpgp.org --recv-keys B42F6819007F00F88E364FD4036A9C25BF357DD4 \
    && gpg --batch --verify /usr/local/bin/gosu.asc /usr/local/bin/gosu \
    && rm -rf "${GNUPGHOME}" /usr/local/bin/gosu.asc \
    && chmod +x /usr/local/bin/gosu \
    && gosu nobody true

RUN set -x \
    && git clone -b ${SLURM_TAG} --single-branch --depth=1 https://github.com/SchedMD/slurm.git \
    && cd slurm \
    && ./configure --enable-debug --prefix=/usr --sysconfdir=/etc/slurm \
        --with-mysql_config=/usr/bin  --libdir=/usr/lib64 \
    && make install \
    && install -D -m644 etc/cgroup.conf.example /etc/slurm/cgroup.conf.example \
    && install -D -m644 etc/slurm.conf.example /etc/slurm/slurm.conf.example \
    && install -D -m644 etc/slurmdbd.conf.example /etc/slurm/slurmdbd.conf.example \
    && install -D -m644 contribs/slurm_completion_help/slurm_completion.sh /etc/profile.d/slurm_completion.sh \
    && cd .. \
    && rm -rf slurm \
    && groupadd -r --gid=990 slurm \
    && useradd -r -g slurm --uid=990 slurm \
    && mkdir -p /etc/sysconfig/slurm \
        /var/spool/slurmd \
        /var/run/slurmd \
        /var/run/slurmdbd \
        /var/lib/slurmd \
        /var/log/slurm \
        /data \
    && touch /var/lib/slurmd/node_state \
        /var/lib/slurmd/front_end_state \
        /var/lib/slurmd/job_state \
        /var/lib/slurmd/resv_state \
        /var/lib/slurmd/trigger_state \
        /var/lib/slurmd/assoc_mgr_state \
        /var/lib/slurmd/assoc_usage \
        /var/lib/slurmd/qos_usage \
        /var/lib/slurmd/fed_mgr_state \
    && chown -R slurm:slurm /var/*/slurm*

# RUN /usr/sbin/create-munge-key
RUN dd if=/dev/urandom bs=1 count=1024 > /etc/munge/munge.key
RUN chown munge: /etc/munge/munge.key
RUN chmod 400 /etc/munge/munge.key
RUN mkdir -p /var/run/munge
RUN chown -R munge: /etc/munge/ /var/log/munge/ /var/lib/munge/ /run/munge/
RUN chmod 0700 /etc/munge/ /var/log/munge/ /var/lib/munge/
RUN chmod 755 /run/munge


# ------------------------------------------------------------
# Install telegraf
# ------------------------------------------------------------

RUN apt-get update && apt-get install -y --no-install-recommends gpgv ca-certificates apt-transport-https gnupg lsb-release
# RUN wget -qO- https://repos.influxdata.com/influxdb.key | apt-key add -
RUN wget -qO- https://repos.influxdata.com/influxdb.key | gpg --dearmor | sudo tee /etc/apt/trusted.gpg.d/influxdb.gpg > /dev/null
RUN export DISTRIB_ID=$(lsb_release -si); export DISTRIB_CODENAME=$(lsb_release -sc) \
&& echo "deb [signed-by=/etc/apt/trusted.gpg.d/influxdb.gpg] https://repos.influxdata.com/${DISTRIB_ID,,} ${DISTRIB_CODENAME} stable" | sudo tee /etc/apt/sources.list.d/influxdb.list > /dev/null
RUN curl -fsSL https://repos.influxdata.com/influxdata-archive_compat.key -o /etc/apt/keyrings/influxdata-archive_compat.key
RUN echo "deb [signed-by=/etc/apt/keyrings/influxdata-archive_compat.key] https://repos.influxdata.com/debian stable main" | tee /etc/apt/sources.list.d/influxdata.list

RUN apt-get update && apt-get install -y --no-install-recommends telegraf && apt-get clean && apt-get purge && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*


# ------------------------------------------------------------
# The .ssh-source dir contains RSA keys - put in place with docker-compose
# ------------------------------------------------------------


RUN touch /home/mpiuser/.ssh-source/authorized_keys
RUN touch /home/mpiuser/.ssh-source/id_rsa


# ------------------------------------------------------------
# supervisord to run entrypoint
# ------------------------------------------------------------
COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf

# ------------------------------------------------------------
# telegraf to run entrypoint
# ------------------------------------------------------------
COPY telegraf.conf /etc/telegraf/telegraf.conf

EXPOSE 22 80 8125

WORKDIR /home/mpiuser
# trixie force le ssl pour mysql
RUN echo "[client]\nssl=0" > /etc/my.cnf
COPY slurm.conf /etc/slurm/slurm.conf
COPY slurmdbd.conf /etc/slurm/slurmdbd.conf
COPY cgroup.conf /etc/slurm/cgroup.conf
RUN set -x \
    && chown slurm:slurm /etc/slurm/slurmdbd.conf \
    && chmod 600 /etc/slurm/slurmdbd.conf

COPY docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh


CMD cp -R /home/mpiuser/.ssh-source/* /home/mpiuser/.ssh \
	&& chmod 700 /home/mpiuser/.ssh/authorized_keys \
	&& chmod 700 /home/mpiuser/.ssh/id_rsa \
	&& chown -R mpiuser:mpiuser /home/mpiuser/.ssh \

	&& exec /usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf
#	&& exec /usr/sbin/sshd -D -f /home/mpiuser/ssh/sshd_config -E /tmp/sshd.log
# do not detach (-D), log to stderr (-e)
# CMD ["/usr/sbin/sshd", "-D", "-e"]
