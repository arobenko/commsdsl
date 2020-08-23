# Overview
This project is a member of [CommsChampion Ecosystem](https://commschamp.github.io).
It provides a code generator that produces C++11 code of a binary communication protocol,
defined using [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) 
schema files. 

# What's Inside
- **commsdsl2comms** - A code generator, that produces C++11 code for binary
protocol definition out of [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) 
schema files. The generated outcome is actually a CMake project that can be used to
build and install multiple targets. For details on how to use the tool, please read the 
[commsdsl2comms Manual](https://github.com/commschamp/commsdsl/doc/Manual_commsdsl2comms.md) 
documentation page. For details on the generated CMake project please read the
[Generated CMake Project Walkthrough](https://github.com/commschamp/commsdsl/doc/GeneratedProjectWalkthrough.md)
documentation page.
- **libcommsdsl** - A C++11 library for parsing of 
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification) schema files.
It can be used to implement independent code generators, which can produce
protocol definition code in other programming languages, bindings to the C++
classes generated by the **commsdsl2comms**, extra testing, etc... 
NOTE, that at this moment, the library is not documented. Please
[get in touch](#contact-information) in case you need it. I'll let you know
when it's going to be ready.

# License
Code generated by **commsdsl2comms** has no license, the vendor is free to
pick any as long as it's compatibile with the license(s) of the
used componets provided by the 
[comms_champion](https://github.com/commschamp/comms_champion) project:

- The protocol definition uses the 
  [COMMS Library](https://github.com/commschamp/comms_champion#comms-library),
  which is provided under the [MPL-2.0](https://www.mozilla.org/en-US/MPL/2.0/) licence.
  It allows usage in any closed source projects as long as modifications to the 
  [COMMS Library](https://github.com/commschamp/comms_champion#comms-library) itself remain
  open source.
- The [CommsChampion Tools](https://github.com/commschamp/comms_champion#commschampion-tools)
  use open source [Qt5](https://www.qt.io/) libraries, hence are licensed under the 
  [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html). It means that any relevant plugin
  code must remain open source and is not really available to be used in the closed source
  commercial products.

The code of this project (libraries and tools it contains) 
is licensed under [Apache v2.0](https://www.apache.org/licenses/LICENSE-2.0) license.

# Examples
There are multiple available examples of protocol definitions that use 
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification) schema files
and **commsdsl2comms** code generator to generate relevant code.

#### Synthetic Demo Protocols
- [cc.demo1.commsdsl](https://github.com/commschamp/cc.demo1.commsdsl) - Demo 
protocol to demonstrate definition of various fields as well as simple protocol framing.
- [cc.demo2.commsdsl](https://github.com/commschamp/cc.demo2.commsdsl) - Demo 
protocol to demonstrate protocol versioning, where every message reports protocol
version in its transport frame.
- [cc.demo3.commsdsl](https://github.com/commschamp/cc.demo3.commsdsl) - Demo 
protocol to demonstrate protocol versioning, where one "connect" message reports protocol
version for all the subsequent messages.

#### Real Life Open Protocols
- [cc.mqtt311.commsdsl](https://github.com/commschamp/cc.mqtt311.commsdsl) - 
Defines [MQTT v3.1.1](http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.pdf)
protocol, where message ID shares
the same byte with extra flags, that may define existence of the fields in
message payload as well as influence how message needs to be processed. The protocol
definition also contains snippets of custom code that are injected by the
**commsdsl2comms** into the generated one.
- [cc.mqtt5.commsdsl](https://github.com/commschamp/cc.mqtt5.commsdsl) - 
Defines [MQTT v5](http://docs.oasis-open.org/mqtt/mqtt/v5.0/cs02/mqtt-v5.0-cs02.html) 
protocol. Similar to v3.1.1, but also adds a heterogeneous list of 
various properties.
- [cc.mqttsn.commsdsl](https://github.com/commschamp/cc.mqttsn.commsdsl) - 
Defines [MQTT-SN](http://mqtt.org/2013/12/mqtt-for-sensor-networks-mqtt-sn) 
protocol, where field of remaining length of the message can 
have either 1 or 3 bytes length, depending on the value it contains.
- [cc.ublox.commsdsl](https://github.com/commschamp/cc.ublox.commsdsl) - 
Defines **UBX** protocol used by various
[u-blox GPS receivers](https://www.u-blox.com/en/position-time). The protocol
itself is quite complex with hundreds of messages. It uses custom checksum
calculation algorithms and injects multiple code snippets to fix incorrect
or incomplete functionality available by default.

#### Tutorial
The [cc_tutorial](https://github.com/commschamp/cc_tutorial/) project contains a 
tutorial on how to use 
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification) to define the binary protocol,
**commsdsl2comms** to generate code, and 
[COMMS Library](https://github.com/commschamp/comms_champion#comms-library) to customize and 
integrate the protocol definition with the business logic of the application.

# How to Build
Detailed instructions on how to build and install all the components can be
found in [doc/BUILD.md](doc/BUILD.md) file.

# Other Documentation
Please check the [doc](doc) folder for the available additional documentation.

# Versioning
This project will use [Semantic Versioning](https://semver.org/), where
**MAJOR** number will be equal to the latest **DSL** version 
(The first number of [CommsDSL](https://github.com/commschamp/CommsDSL-Specification)
version) it supports. The **MINOR** number will indicate various improvements
in the code of this repository, and **PATCH** number will indicate various bug fixes.

# Supported Compilers
This project (the code generator and [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) 
parsing library) is implemented using C++14 programming language. As the result,
the supported compilers are:
- **GCC**: >=5
- **Clang**: >=3.9
- **MSVC**: >= 2015

The **generated** project however contains C++11 valid code and supports a bit earlier
versions of the compilers:
- **GCC**: >=4.8
- **Clang**: >=3.8
- **MSVC**: >= 2015

# Branching Model
This repository will follow the 
[Successful Git Branching Model](http://nvie.com/posts/a-successful-git-branching-model/).

The **master** branch will always point to the latest release, the
development is performed on **develop** branch. As the result it is safe
to just clone the sources of this repository and use it without
any extra manipulations of looking for the latest stable version among the tags and
checking it out.

# Contact Information
For bug reports, feature requests, or any other question you may open an issue
here in **github** or e-mail me directly to: **arobenko@gmail.com**. I usually
respond within 24 hours.

