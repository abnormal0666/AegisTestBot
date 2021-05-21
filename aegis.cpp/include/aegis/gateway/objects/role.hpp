//
// role.hpp
// ********
//
// Copyright (c) 2020 Sharon Fox (sharon at xandium dot io)
//
// Distributed under the MIT License. (See accompanying file LICENSE)
//

#pragma once

#include "aegis/config.hpp"
#include "aegis/snowflake.hpp"
#include "aegis/permission.hpp"
#include <nlohmann/json.hpp>

namespace aegis
{

namespace gateway
{

namespace objects
{

struct role;

/// \cond TEMPLATES
void from_json(const nlohmann::json& j, role& m);
void to_json(nlohmann::json& j, const role& m);
/// \endcond

/// Stores info pertaining to guild roles
struct role
{
    role(const std::string & _json, aegis::core * bot) noexcept
    {
        from_json(nlohmann::json::parse(_json), *this);
    }

    role(const nlohmann::json & _json, aegis::core * bot) noexcept
    {
        from_json(_json, *this);
    }

    role(aegis::core * bot) noexcept {}

    role() noexcept {}

    /// Builds a mention for this user
    /**
     * @returns string of role mention
     */
    std::string get_mention() const noexcept
    {
        return fmt::format("<@&{}>", id);
    }

    uint32_t color = 0; /**< RGB color value */
    snowflake id; /**< Snowflake ID of this role */
    snowflake role_id; //<deprecated use role::id instead
    std::string name; /**< Name of this role */
    aegis::permission _permission; /**< Permissions given by this role */
    uint16_t position = 0; /**< Sorting position of the role */
    bool hoist = false; /**< Whether this role should be displayed separately in the sidebar */
    bool managed = false; /**< Whether this role is managed */
    bool mentionable = false; /**< Whether this role should be mentionable */
};

/// \cond TEMPLATES
inline void from_json(const nlohmann::json& j, role& m)
{
    if (j.count("color") && !j["color"].is_null())
        m.color = j["color"];
    if (j.count("id") && !j["id"].is_null())
        m.id = m.role_id = j["id"];
    if (j.count("name") && !j["name"].is_null())
        m.name = j["name"].get<std::string>();
    if (j.count("permissions") && !j["permissions"].is_null())
        m._permission = j["permissions"];
    if (j.count("position") && !j["position"].is_null())
        m.position = j["position"];
    if (j.count("hoist") && !j["hoist"].is_null())
        m.hoist = j["hoist"];
    if (j.count("mentionable") && !j["mentionable"].is_null())
        m.mentionable = j["mentionable"];
}

inline void to_json(nlohmann::json& j, const role& m)
{
    j["color"] = m.color;
    j["id"] = std::to_string(m.id);
    j["name"] = m.name;
    j["permissions"] = m._permission;
    j["position"] = m.position;
    j["hoist"] = m.hoist;
    j["mentionable"] = m.mentionable;
}
/// \endcond

}

}

}
