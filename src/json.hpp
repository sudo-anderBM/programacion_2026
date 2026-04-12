// JSON support for chatbot_terminal
//
// This project uses a minimal JSON parser built-in to main.cpp.
// If you prefer to use nlohmann/json (header-only library), follow these steps:
//
// 1. Download json.hpp from: https://github.com/nlohmann/json/releases
// 2. Place it in the project root directory or src/ directory
// 3. Add #include "json.hpp" at the top of main.cpp
// 4. Replace the custom JSON class with nlohmann::json usage
//
// The current implementation (without external JSON library) supports:
// - String escaping and unescaping
// - Extracting values from JSON strings
// - Parsing API responses from OpenAI-compatible endpoints
//
// This approach avoids the need for external dependencies while maintaining
// compatibility with DeepSeek and Kimi APIs.
