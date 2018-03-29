#include "NamespaceImpl.h"

#include <type_traits>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "common.h"
#include "ProtocolImpl.h"

namespace bbmp
{

namespace
{

static const XmlWrap::NamesList ChildrenNames = {
    common::fieldsStr(),
    common::messagesStr(),
    common::messageStr(),
    common::framesStr(),
    common::frameStr(),
};

bool updateStringProperty(const XmlWrap::PropsMap& map, const std::string& name, std::string& prop)
{
    auto iter = map.find(name);
    if (iter == map.end()) {
        prop.clear();
        return true;
    }

    prop = iter->second;
    return true;
}

} // namespace

NamespaceImpl::NamespaceImpl(::xmlNodePtr node, ProtocolImpl& protocol)
  : m_node(node),
    m_protocol(protocol)
{
}

bool NamespaceImpl::parse()
{
    if (m_node == nullptr) {
        // default namespace
        return true;
    }

    static const XmlWrap::NamesList Names = {
        common::nameStr(),
        common::descriptionStr()
    };

    m_props = XmlWrap::parseNodeProps(m_node);
    if (!XmlWrap::parseChildrenAsProps(m_node, Names, m_protocol.logger(), m_props)) {
        return false;
    }

    if ((!updateStringProperty(m_props, common::nameStr(), m_name)) ||
        (!updateStringProperty(m_props, common::descriptionStr(), m_description))) {
        return false;
    }

    m_unknownAttrs = XmlWrap::getUnknownProps(m_node, Names);

    m_unknownChildren = XmlWrap::getUnknownChildrenContents(m_node, ChildrenNames);

    auto children = XmlWrap::getChildren(m_node, ChildrenNames);
    for (auto* c : children) {
        if (!processChild(c)) {
            return false;
        }
    }
    return true;
}

bool NamespaceImpl::processChild(::xmlNodePtr node)
{
    using ProcessFunc = bool (NamespaceImpl::*)(::xmlNodePtr node);
    static const std::map<std::string, ProcessFunc> ParseFuncMap = {
        std::make_pair(common::fieldsStr(), &NamespaceImpl::processMultipleFields),
        std::make_pair(common::messageStr(), &NamespaceImpl::processMessage),
        std::make_pair(common::messagesStr(), &NamespaceImpl::processMultipleMessages),
        std::make_pair(common::frameStr(), &NamespaceImpl::processFrame),
        std::make_pair(common::framesStr(), &NamespaceImpl::processMultipleFrames),
    };

    std::string cName(reinterpret_cast<const char*>(node->name));
    auto iter = ParseFuncMap.find(cName);
    if (iter == ParseFuncMap.end()) {
        return false;
    }

    auto func = iter->second;
    return (this->*func)(node);
}

bool NamespaceImpl::merge(NamespaceImpl& other)
{
    assert(m_name == other.m_name);
    if (m_description.empty()) {
        m_description = std::move(other.m_description);
    }

    for (auto& f : other.m_fields) {
        auto iter = m_fields.find(f.first);
        if (iter != m_fields.end()) {
            assert(f.second);
            assert(iter->second);
            logError() << XmlWrap::logPrefix(f.second->getNode()) <<
                "Field with name \"" << f.first << "\" has been defined earlier at " <<
                XmlWrap::logPrefix(iter->second->getNode());
            return false;
        }

        m_fields.insert(std::move(f));
    }
    other.m_fields.clear();


    // TODO: merge messages and frames
    return true;
}

bool NamespaceImpl::finalise()
{
    m_fieldsList.clear();
    m_fieldsList.reserve(m_fields.size());
    for (auto& f : m_fields) {
        assert(f.second);
        m_fieldsList.push_back(Field(f.second.get()));
    }

    // TODO: finalise messages and frames
    return true;
}

const XmlWrap::NamesList& NamespaceImpl::supportedChildren()
{
    return ChildrenNames;
}

bool NamespaceImpl::processMultipleFields(::xmlNodePtr node)
{
    auto childrenNodes = XmlWrap::getChildren(node);
    for (auto* c : childrenNodes) {
        std::string cName(reinterpret_cast<const char*>(c->name));
        auto field = FieldImpl::create(cName, c, m_protocol);
        if (!field) {
            logError() << XmlWrap::logPrefix(c) << "Invalid field type \"" << cName << "\"";
            return false;
        }

        if (!field->parse()) {
            logError() << XmlWrap::logPrefix(c) << "Parsing of \"" << cName << "\" has failed.";
            return false;
        }

        auto& name = field->name();
        if (name.empty()) {
            logError() << XmlWrap::logPrefix(c) << "Field \"" << cName << "\" doesn't have any name.";
            return false;
        }

        auto iter = m_fields.find(name);
        if (iter != m_fields.end()) {
            logError() << XmlWrap::logPrefix(c) << "Field with name \"" << name << "\" has been already defined at " <<
                          iter->second->getNode()->doc->URL << ":" << iter->second->getNode()->line << '.';
            return false;
        }

        m_fields.insert(std::make_pair(name, std::move(field)));
    }

    return true;
}

bool NamespaceImpl::processMessage(::xmlNodePtr node)
{
    static_cast<void>(node);
    // TODO:
    logError() << __FUNCTION__ << ": NYI!";
    return false;
}

bool NamespaceImpl::processMultipleMessages(::xmlNodePtr node)
{
    static_cast<void>(node);
    // TODO:
    logError() << __FUNCTION__ << ": NYI!";
    return false;
}

bool NamespaceImpl::processFrame(::xmlNodePtr node)
{
    static_cast<void>(node);
    // TODO:
    logError() << __FUNCTION__ << ": NYI!";
    return false;
}

bool NamespaceImpl::processMultipleFrames(::xmlNodePtr node)
{
    static_cast<void>(node);
    // TODO:
    logError() << __FUNCTION__ << ": NYI!";
    return false;
}

LogWrapper NamespaceImpl::logError() const
{
    return bbmp::logError(m_protocol.logger());
}

LogWrapper NamespaceImpl::logWarning() const
{
    return bbmp::logWarning(m_protocol.logger());
}

} // namespace bbmp
