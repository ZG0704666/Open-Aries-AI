#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cctype>

namespace aries {

struct SecurityConfig {
    bool allowExecute = false;
    bool allowFileWrite = false;
    bool allowFileDelete = false;
    bool allowFileRun = false;
    bool requireHighRiskConfirmation = true;
    bool loadedFromFile = false;
};

class SecurityConfigLoader {
public:
    static SecurityConfig loadFromFileAndEnv(const std::string& path = "aries_config.json") {
        SecurityConfig config;
        std::ifstream file(path);
        if (file.is_open()) {
            std::stringstream ss;
            ss << file.rdbuf();
            std::string content = ss.str();
            file.close();

            config.allowExecute = readBool(content, "allowExecute", config.allowExecute);
            config.allowFileWrite = readBool(content, "allowFileWrite", config.allowFileWrite);
            config.allowFileDelete = readBool(content, "allowFileDelete", config.allowFileDelete);
            config.allowFileRun = readBool(content, "allowFileRun", config.allowFileRun);
            config.requireHighRiskConfirmation =
                readBool(content, "requireHighRiskConfirmation", config.requireHighRiskConfirmation);
            config.loadedFromFile = true;
        }

        applyEnvOverride("ARIES_ALLOW_EXECUTE", config.allowExecute);
        applyEnvOverride("ARIES_ALLOW_FILE_WRITE", config.allowFileWrite);
        applyEnvOverride("ARIES_ALLOW_FILE_DELETE", config.allowFileDelete);
        applyEnvOverride("ARIES_ALLOW_FILE_RUN", config.allowFileRun);
        applyEnvOverride("ARIES_REQUIRE_HIGH_RISK_CONFIRMATION", config.requireHighRiskConfirmation);

        return config;
    }

private:
    static std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        return s;
    }

    static bool parseBool(const std::string& raw, bool defaultValue) {
        std::string v = toLower(raw);
        if (v == "1" || v == "true" || v == "yes" || v == "on") return true;
        if (v == "0" || v == "false" || v == "no" || v == "off") return false;
        return defaultValue;
    }

    static bool readBool(const std::string& json, const std::string& key, bool defaultValue) {
        std::string marker = "\"" + key + "\"";
        size_t pos = json.find(marker);
        if (pos == std::string::npos) return defaultValue;
        pos = json.find(':', pos);
        if (pos == std::string::npos) return defaultValue;
        pos++;

        while (pos < json.size() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) {
            pos++;
        }
        if (pos >= json.size()) return defaultValue;

        if (json.compare(pos, 4, "true") == 0) return true;
        if (json.compare(pos, 5, "false") == 0) return false;
        return defaultValue;
    }

    static void applyEnvOverride(const char* envKey, bool& target) {
        const char* raw = std::getenv(envKey);
        if (!raw) return;
        target = parseBool(raw, target);
    }
};

} // namespace aries
