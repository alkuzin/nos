# Simple OS documentation

<img src="../res/simple-os-doc-banner.png">

## Contents

1. [Introduction](#1-introduction)
2. [Installation](#2-installation)

## 1. Introduction
Test OS project for x86_32 platform

## 2. Installation
First clone this repository:
```console
https://github.com/alkuzin/simple-os.git
```
Then move to the `simple-os/` directory:
```console
cd simple-os/
```

To build kernel as `.bin` run:

```console
make all
```

To build kernel as `.iso` run:

```console
make build-iso
```
To run OS on QEMU use this:
 ```console
make init
```

To return everything to original state:
```console
make fclean
```