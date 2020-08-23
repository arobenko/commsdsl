//
// Copyright 2019 - 2020 (C). Alex Robenko. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "License.h"

#include <fstream>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>

#include "Generator.h"
#include "common.h"

namespace bf = boost::filesystem;

namespace commsdsl2comms
{

bool License::write(Generator& generator)
{
    License obj(generator);
    return
        obj.writeTxt();
}

bool License::writeTxt() const
{
    static const std::string LicenseFile("LICENSE.txt");
    auto filePath = m_generator.startLicenseWrite(LicenseFile);

    if (filePath.empty()) {
        return true;
    }

    std::ofstream stream(filePath);
    if (!stream) {
        m_generator.logger().error("Failed to open \"" + filePath + "\" for writing.");
        return false;
    }

    static const std::string Template = 
        "This code has been generated by the commsdsl2comms[1] application has no license,\n"
        "the vendor is free to pick any as long as it's compatibile with the license(s) of the\n"
        "used componets provided by the comms_champion[2] project.\n\n"
        "- The protocol definition uses the COMMS library[3], which is provided under the\n"
        "  MPL-2.0[4] licence. It allows usage in any closed source projects as long as\n"
        "  modifications to the COMMS library[3] itself remain open source.\n"
        "- The CommsChampion Tools[5] use open source Qt5[6] libraries, hence are licensed under the\n"
        "  GPLv3[7]. It means that any relevant plugin code must remain open source and is not\n"
        "  really available to be used in the closed source commercial products.\n\n"
        "[1]: https://github.com/commschamp/commsdsl\n"
        "[2]: https://github.com/commschamp/comms_champion\n"
        "[3]: https://github.com/commschamp/comms_champion#comms-library\n"
        "[4]: https://www.mozilla.org/en-US/MPL/2.0/\n"
        "[5]: https://github.com/commschamp/comms_champion#commschampion-tools\n"
        "[6]: https://www.qt.io/\n"
        "[7]: https://www.gnu.org/licenses/gpl-3.0.en.html\n"
        "\n"
        "#^#APPEND#$#\n"
        "\n";

    common::ReplacementMap replacements;
    replacements.insert(std::make_pair("APPEND", m_generator.getExtraAppendForFile(LicenseFile)));

    stream << common::processTemplate(Template, replacements);

    stream.flush();
    if (!stream.good()) {
        m_generator.logger().error("Failed to write \"" + filePath + "\".");
        return false;
    }
    return true;
}

} // namespace commsdsl2comms
