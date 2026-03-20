#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ─────────────────────────────────────────────
//  Clase base abstracta — Interfaz de cualquier IA
// ─────────────────────────────────────────────
class AIModel {
protected:
    std::string api_key;
    std::string model_name;

public:
    AIModel(const std::string& key, const std::string& model)
        : api_key(key), model_name(model) {}

    virtual ~AIModel() = default;

    // Métodos virtuales puros — polimorfismo
    virtual std::string sendMessage(const std::string& prompt) = 0;
    virtual std::string getModelName() const = 0;
    virtual void printInfo() const = 0;
};

// ─────────────────────────────────────────────
//  Callback para capturar respuesta de cURL
// ─────────────────────────────────────────────
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// ─────────────────────────────────────────────
//  Clase concreta — Claude (Anthropic)
// ─────────────────────────────────────────────
class ClaudeModel : public AIModel {
private:
    const std::string API_URL = "https://api.anthropic.com/v1/messages";
    int max_tokens;

    std::string makeRequest(const std::string& body) {
        CURL* curl = curl_easy_init();
        std::string response;

        if (!curl) return "{\"error\": \"cURL init failed\"}";

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("x-api-key: " + api_key).c_str());
        headers = curl_slist_append(headers, "anthropic-version: 2023-06-01");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        return response;
    }

public:
    ClaudeModel(const std::string& key,
                const std::string& model = "claude-sonnet-4-6",
                int tokens = 1024)
        : AIModel(key, model), max_tokens(tokens) {}

    // ── Implementación del método virtual ──
    std::string sendMessage(const std::string& prompt) override {
        json body = {
            {"model", model_name},
            {"max_tokens", max_tokens},
            {"messages", json::array({
                {{"role", "user"}, {"content", prompt}}
            })}
        };

        std::string raw = makeRequest(body.dump());

        try {
            json res = json::parse(raw);
            return res["content"][0]["text"].get<std::string>();
        } catch (...) {
            return "Error al parsear respuesta: " + raw;
        }
    }

    std::string getModelName() const override {
        return model_name;
    }

    void printInfo() const override {
        std::cout << "=== Claude (Anthropic) ===" << std::endl;
        std::cout << "Modelo   : " << model_name << std::endl;
        std::cout << "Max tokens: " << max_tokens << std::endl;
    }
};

// ─────────────────────────────────────────────
//  Clase concreta extra — permite extender a OpenAI u otro modelo
//  (demuestra polimorfismo con múltiples implementaciones)
// ─────────────────────────────────────────────
class MockModel : public AIModel {
public:
    MockModel() : AIModel("no-key", "mock-model") {}

    std::string sendMessage(const std::string& prompt) override {
        return "[MockModel] Recibí: " + prompt;
    }

    std::string getModelName() const override {
        return "Mock AI (sin conexión)";
    }

    void printInfo() const override {
        std::cout << "=== Mock Model (testing) ===" << std::endl;
    }
};

// ─────────────────────────────────────────────
//  Función que usa polimorfismo — acepta cualquier AIModel
// ─────────────────────────────────────────────
void chat(AIModel& model) {
    model.printInfo();
    std::cout << std::endl;

    std::string input;
    while (true) {
        std::cout << "Tú: ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "q") break;

        std::string response = model.sendMessage(input);
        std::cout << "\nClaude: " << response << "\n" << std::endl;
    }
}

// ─────────────────────────────────────────────
//  Main
// ─────────────────────────────────────────────
int main() {
    std::string api_key = "TU_API_KEY_AQUI";  // <-- Cambia esto

    // Polimorfismo: el puntero base apunta a la clase derivada
    std::unique_ptr<AIModel> model = std::make_unique<ClaudeModel>(api_key);

    chat(*model);

    return 0;
}
