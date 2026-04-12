# chatbot_terminal

Una aplicación de terminal en C++17 para enviar prompts a modelos de lenguaje (DeepSeek y Kimi) mediante APIs REST y recibir respuestas en tiempo real.

## Características

- ✅ Soporte para **DeepSeek** y **Kimi (Moonshot AI)**
- ✅ Modo interactivo (diálogo continuo)
- ✅ Modo prompt único
- ✅ Carga automática de variables desde `.env`
- ✅ Soporte UTF-8 en Windows
- ✅ C++17 estándar
- ✅ Sin dependencias externas excepto libcurl

## Requisitos Previos

### Linux/macOS
```bash
# Debian/Ubuntu
sudo apt-get install libcurl4-openssl-dev build-essential

# macOS (con Homebrew)
brew install curl
```

### Windows (MSYS2 UCRT64)
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-curl
```

## Configuración

1. **Copia el archivo de variables de entorno:**
```bash
cp .env.example .env
```

2. **Obtén tus claves API:**
   - **DeepSeek**: https://platform.deepseek.com/api_keys
   - **Kimi**: https://console.moonshot.cn/api-keys

3. **Edita `.env` con tus credenciales:**
```env
DEEPSEEK_API_KEY=sk_live_xxxxxxxxxxxxx
KIMI_API_KEY=sk-xxxxxxxxxxxxx
```

## Compilación

### Linux/macOS
```bash
clang++ -std=c++17 src/main.cpp -lcurl -o chatbot_terminal

# O con g++
g++ -std=c++17 src/main.cpp -lcurl -o chatbot_terminal

# O usando Makefile
make build
```

### Windows (MSYS2 UCRT64)
```bash
g++ -std=c++17 src/main.cpp -lcurl -o chatbot_terminal.exe

# O usando Makefile
mingw32-make build
```

## Uso

### Modo Prompt Único

**DeepSeek:**
```bash
./chatbot_terminal --provider deepseek --model deepseek-chat --prompt "Escribe un haiku sobre programación"
```

**Kimi:**
```bash
./chatbot_terminal --provider kimi --model moonshot-v1-8k --prompt "Explica qué es un puntero en C++"
```

**Auto-detect (recomienda usar modelo con su proveedor):**
```bash
./chatbot_terminal --prompt "¿Cuál es la capital de Francia?"
# Si el modelo es moonshot-*, usa Kimi; si no, usa DeepSeek
```

### Modo Interactivo

**DeepSeek:**
```bash
./chatbot_terminal --provider deepseek --model deepseek-chat
```

**Kimi:**
```bash
./chatbot_terminal --provider kimi --model moonshot-v1-8k
```

**Valores por defecto (DeepSeek + deepseek-chat):**
```bash
./chatbot_terminal
```

Para salir del modo interactivo, escribe `quit` o `exit`.

### Argumentos CLI

| Argumento | Valores | Default |
|-----------|---------|---------|
| `--provider` | `deepseek`, `kimi`, `auto` | `auto` |
| `--model` | Nombre del modelo | `deepseek-chat` |
| `--prompt` | Texto del prompt | (vacío = modo interactivo) |

## Modelos Disponibles

### DeepSeek
- `deepseek-chat` - Chat rápido y económico
- `deepseek-reasoner` - Modelo de razonamiento (más lento, más preciso)

### Kimi
- `moonshot-v1-8k` - Contexto de 8K tokens
- `moonshot-v1-32k` - Contexto de 32K tokens
- `moonshot-v1-128k` - Contexto de 128K tokens

## Estructura del Proyecto

```
chatbot_terminal/
├── src/
│   ├── main.cpp      # Código fuente principal
│   └── json.hpp      # Notas sobre JSON (modo sin dependencias)
├── .env.example      # Plantilla de variables de entorno
├── .env              # Variables de entorno (crear desde .env.example)
├── Makefile          # Reglas de compilación
└── README.md         # Este archivo
```

## Detalles Técnicos

- **Lenguaje**: C++17 (estándar ISO)
- **HTTP Client**: libcurl
- **JSON Parsing**: Implementación personalizada (sin dependencias externas)
- **UTF-8 Windows**: `SetConsoleOutputCP(65001)`
- **Timeout**: 30 segundos por solicitud

## Lógica de Selección de Proveedor (--provider auto)

Si usas `--provider auto` o no especificas proveedor:
1. Si el modelo contiene `moonshot` → Usa **Kimi**
2. En cualquier otro caso → Usa **DeepSeek**

Ejemplo:
```bash
./chatbot_terminal --model moonshot-v1-8k --prompt "Hola"
# Automáticamente usa Kimi

./chatbot_terminal --model deepseek-chat --prompt "Hola"
# Automáticamente usa DeepSeek
```

## Ejemplos Prácticos

### Análisis de código
```bash
./chatbot_terminal --provider deepseek --model deepseek-chat --prompt "Analiza este código C++: int x = 5; cout << x;"
```

### Razonamiento profundo
```bash
./chatbot_terminal --provider deepseek --model deepseek-reasoner --prompt "¿Cuál es el límite de x^2 cuando x tiende a infinito?"
```

### Contexto grande
```bash
./chatbot_terminal --provider kimi --model moonshot-v1-128k --prompt "Resume este documento de 100KB..."
```

### Conversación interactiva
```bash
./chatbot_terminal --provider kimi --model moonshot-v1-8k
# Luego escribes múltiples prompts uno a uno
```

## Solución de Problemas

### "Error: API key not found"
- Asegúrate de crear el archivo `.env` desde `.env.example`
- Verifica que las claves API sean válidas
- Usa `export DEEPSEEK_API_KEY=...` (Linux/macOS) o `set DEEPSEEK_API_KEY=...` (Windows CMD)

### "Error: CURL request failed"
- Verifica conexión a Internet
- Asegúrate de que libcurl esté correctamente instalado
- Intenta aumentar el timeout si es muy lento

### "Invalid response format"
- Verifica que la API key sea correcta
- Revisa que el modelo exista en el proveedor
- Comprueba los errores en la consola

## Variables de Entorno

| Variable | Descripción |
|----------|-------------|
| `DEEPSEEK_API_KEY` | Clave API de DeepSeek |
| `DEEPSEEK_BASE_URL` | URL base de DeepSeek (opcional, por defecto: https://api.deepseek.com/v1) |
| `KIMI_API_KEY` | Clave API de Kimi |

## Licencia

Este proyecto es de código abierto.

## Contributing

Las contribuciones son bienvenidas. Por favor:
1. Fork el proyecto
2. Crea una rama para tu feature
3. Realiza tus cambios
4. Envía un pull request

---

**Última actualización:** 2026-03-26
