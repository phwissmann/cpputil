# Check http://releases.llvm.org/download.html#8.0.0 for the latest available binaries
FROM conanio/gcc10

USER root
RUN apt-get update
RUN apt-get install gdb gdbserver -y

RUN apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash develop
RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers


EXPOSE 2000

RUN mkdir /mnt/src
RUN chmod -R a+rwx /mnt/src

RUN mkdir /mnt/conan
RUN chmod -R a+rwx /mnt/conan

RUN mkdir /mnt/build
RUN chmod -R a+rwx /mnt/build


WORKDIR /mnt

CMD ["/bin/bash"]

