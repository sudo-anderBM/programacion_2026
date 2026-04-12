#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <curl/curl.h>

#ifdef _WIN32
#include <windows.h>
#endif


//  JSON helpers

class JSON {
public:
    static std::string escape(const std::string& str) {
        std::string r;
        for (char c : str) {
            switch (c) {
                case '"':  r += "\\\""; break;
                case '\\': r += "\\\\"; break;
                case '\b': r += "\\b";  break;
                case '\f': r += "\\f";  break;
                case '\n': r += "\\n";  break;
                case '\r': r += "\\r";  break;
                case '\t': r += "\\t";  break;
                default:
                    if (static_cast<unsigned char>(c) < 32) {
                        char buf[7];
                        snprintf(buf, sizeof(buf), "\\u%04x", (unsigned char)c);
                        r += buf;
                    } else r += c;
            }
        }
        return r;
    }

    static std::string unescape(const std::string& s) {
        std::string r;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '\\' && i + 1 < s.size()) {
                switch (s[++i]) {
                    case '"':  r += '"';  break;
                    case '\\': r += '\\'; break;
                    case '/':  r += '/';  break;
                    case 'b':  r += '\b'; break;
                    case 'f':  r += '\f'; break;
                    case 'n':  r += '\n'; break;
                    case 'r':  r += '\r'; break;
                    case 't':  r += '\t'; break;
                    default:   r += s[i];
                }
            } else r += s[i];
        }
        return r;
    }

    static std::string extractString(const std::string& json, const std::string& key) {
        for (auto sep : { std::string("\":\""), std::string("\": \"") }) {
            std::string search = "\"" + key + sep;
            size_t pos = json.find(search);
            if (pos == std::string::npos) continue;
            pos += search.size();
            size_t end = pos;
            while (end < json.size() && !(json[end] == '"' && json[end-1] != '\\')) ++end;
            if (end < json.size()) return unescape(json.substr(pos, end - pos));
        }
        return "";
    }

    static bool hasErrorObject(const std::string& json) {
        size_t pos = json.find("\"error\"");
        if (pos == std::string::npos) return false;
        pos = json.find(':', pos);
        if (pos == std::string::npos) return false;
        while (++pos < json.size() && (json[pos] == ' ' || json[pos] == '\t'));
        return pos < json.size() && json[pos] == '{';
    }

    static std::string extractFirstArrayElement(const std::string& json, const std::string& key) {
        size_t pos = json.find("\"" + key + "\":");
        if (pos == std::string::npos) return "";
        pos = json.find('[', pos);
        if (pos == std::string::npos) return "";
        pos = json.find('{', pos);
        if (pos == std::string::npos) return "";
        int depth = 1; size_t end = pos + 1;
        while (end < json.size() && depth > 0) {
            if (json[end] == '{') ++depth;
            else if (json[end] == '}') --depth;
            ++end;
        }
        return json.substr(pos, end - pos);
    }

    static std::string extractNestedString(const std::string& json,
                                            const std::string& objKey,
                                            const std::string& fieldKey) {
        size_t pos = json.find("\"" + objKey + "\":");
        if (pos == std::string::npos) return "";
        pos = json.find('{', pos);
        if (pos == std::string::npos) return "";
        int depth = 1; size_t end = pos + 1;
        while (end < json.size() && depth > 0) {
            if (json[end] == '{') ++depth;
            else if (json[end] == '}') --depth;
            ++end;
        }
        return extractString(json.substr(pos, end - pos), fieldKey);
    }
};


//  CURL


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* out) {
    out->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// ─────────────────────────────────────────────
//  .env loader
// ─────────────────────────────────────────────
class EnvLoader {
public:
    static void load(const std::string& file) {
        std::ifstream f(file);
        if (!f.is_open()) return;
        std::string line;
        while (std::getline(f, line)) {
            if (line.empty() || line[0] == '#') continue;
            size_t pos = line.find('=');
            if (pos == std::string::npos) continue;
            std::string key = line.substr(0, pos);
            std::string val = line.substr(pos + 1);
            if (val.size() >= 2 && val.front() == '"' && val.back() == '"')
                val = val.substr(1, val.size() - 2);
#ifdef _WIN32
            SetEnvironmentVariableA(key.c_str(), val.c_str());
#else
            setenv(key.c_str(), val.c_str(), 1);
#endif
        }
    }
    static std::string get(const std::string& key, const std::string& def = "") {
        const char* v = std::getenv(key.c_str());
        return v ? std::string(v) : def;
    }
};


//  API Client


struct Message { std::string role, content; };

class APIClient {
public:
    enum Provider { OPENAI, GEMINI };

    struct Config {
        Provider    provider = OPENAI;
        std::string model    = "gpt-4o-mini";
        std::string apiKey;
        std::string baseUrl;
        std::string prompt;
    };

    static Config parseArgs(int argc, char* argv[]) {
        Config cfg;
        for (int i = 1; i < argc; ++i) {
            std::string a = argv[i];
            if (a == "--provider" && i+1 < argc) {
                std::string p = argv[++i];
                if (p == "gemini") cfg.provider = GEMINI;
                else               cfg.provider = OPENAI;
            } else if (a == "--model"  && i+1 < argc) cfg.model  = argv[++i];
              else if (a == "--prompt" && i+1 < argc) cfg.prompt = argv[++i];
        }
        return cfg;
    }

    static void autoDetect(Config& cfg) {
        if (cfg.model.rfind("gemini", 0) == 0) cfg.provider = GEMINI;
    }

    static void loadCredentials(Config& cfg) {
        if (cfg.provider == GEMINI) {
            cfg.apiKey  = EnvLoader::get("GEMINI_API_KEY",
                          EnvLoader::get("GOOGLE_API_KEY"));
            cfg.baseUrl = EnvLoader::get("GEMINI_BASE_URL",
                          "https://generativelanguage.googleapis.com/v1beta/openai");
        } else {
            cfg.apiKey  = EnvLoader::get("OPENAI_API_KEY");
            cfg.baseUrl = EnvLoader::get("OPENAI_BASE_URL", "https://api.openai.com/v1");
        }
    }

    static std::string providerName(Provider p) {
        return p == GEMINI ? "Gemini" : "OpenAI";
    }

    static std::string buildPayload(const Config& cfg, const std::vector<Message>& history) {
        std::string json = "{\"model\":\"" + cfg.model + "\",\"messages\":[";
        for (size_t i = 0; i < history.size(); ++i) {
            if (i) json += ",";
            json += "{\"role\":\"" + history[i].role + "\","
                    "\"content\":\"" + JSON::escape(history[i].content) + "\"}";
        }
        json += "],\"temperature\":0.7}";
        return json;
    }

    static std::string sendRequest(const Config& cfg, const std::vector<Message>& history) {
        if (cfg.apiKey.empty()) {
            std::cerr << "[Error] API key no encontrada para "
                      << providerName(cfg.provider) << ".\n";
            return "";
        }

        CURL* curl = curl_easy_init();
        if (!curl) { std::cerr << "[Error] No se pudo inicializar CURL.\n"; return ""; }

        std::string payload = buildPayload(cfg, history);
        std::string url     = cfg.baseUrl + "/chat/completions";
        std::string auth    = "Authorization: Bearer " + cfg.apiKey;
        std::string raw;

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth.c_str());

        curl_easy_setopt(curl, CURLOPT_URL,           url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,    headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &raw);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT,       30L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "[Error CURL] " << curl_easy_strerror(res) << "\n";
            return "";
        }
        return raw;
    }

    static std::string parseResponse(const std::string& raw) {
        if (raw.empty()) return "";

        if (JSON::hasErrorObject(raw)) {
            std::string msg = JSON::extractNestedString(raw, "error", "message");
            std::cerr << "[API Error] " << (msg.empty() ? raw.substr(0,300) : msg) << "\n";
            return "";
        }

        std::string choice = JSON::extractFirstArrayElement(raw, "choices");
        if (choice.empty()) {
            std::cerr << "[Error] Respuesta inesperada:\n" << raw.substr(0, 500) << "\n";
            return "";
        }

        std::string content = JSON::extractNestedString(choice, "message", "content");
        if (content.empty())
            std::cerr << "[Error] No se pudo extraer contenido.\nRaw: " << raw.substr(0,500) << "\n";
        return content;
    }
};



//  main


int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    EnvLoader::load(".env");

    APIClient::Config cfg = APIClient::parseArgs(argc, argv);
    APIClient::autoDetect(cfg);
    APIClient::loadCredentials(cfg);

    // ── Modo single-prompt ─────────────────────
    if (!cfg.prompt.empty()) {
        std::cout << "Enviando a " << APIClient::providerName(cfg.provider)
                  << " (" << cfg.model << ")...\n";
        std::vector<Message> h = {{"user", cfg.prompt}};
        std::string raw     = APIClient::sendRequest(cfg, h);
        std::string content = APIClient::parseResponse(raw);
        if (!content.empty()) std::cout << "\nRespuesta:\n" << content << "\n";
        return 0;
    }

    // ── Modo interactivo ───────────────────────
    std::cout << "=== " << APIClient::providerName(cfg.provider) << " Chat Terminal ===\n";
    std::cout << "Modelo  : " << cfg.model   << "\n";
    std::cout << "URL     : " << cfg.baseUrl << "\n";
    std::cout << "API Key : " << (cfg.apiKey.empty() ? "NO ENCONTRADA" : "cargada") << "\n";
    std::cout << std::string(45, '-') << "\n";
    std::cout << "Comandos: 'salir' / 'exit' / 'limpiar'\n\n";

    std::vector<Message> history;
    std::string line;

    while (true) {
        std::cout << "Tu: ";
        if (!std::getline(std::cin, line)) break;

        if (line == "salir" || line == "exit") { std::cout << "Hasta luego!\n"; break; }
        if (line == "limpiar") { history.clear(); std::cout << "[Historial limpiado]\n\n"; continue; }
        if (line.empty()) continue;

        history.push_back({"user", line});
        std::string raw     = APIClient::sendRequest(cfg, history);
        std::string content = APIClient::parseResponse(raw);

        if (!content.empty()) {
            history.push_back({"assistant", content});
            std::cout << "\n" << APIClient::providerName(cfg.provider) << ": " << content << "\n\n";
        }
    }
    return 0;
}